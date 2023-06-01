#include <driver/i2s.h>

namespace audio {
int16_t samples[2205]; // 3500, 5000, 2205, 8820, 88200 samples/s
bool bStop = false, bPaused = false, playing = false;
const char* toPlay = NULL;
uint32_t dataEnd;
uint8_t vol = 32;
File stream;

String readText(File file, int n) {
  String text;
  for (int i = 0; i < n; i++) text += (char)file.read();
  return text;
}

uint32_t readNum(File file, int n) {
  uint32_t number = 0;
  for (int i = 0; i < n; i++) number |= ((uint32_t) (file.read() & 0xff)) << (i * 8);
  return number;
}

void begin() {
  i2s_config_t cfg = {
    .sample_rate = 16000,
    .bits_per_sample = I2S_BITS_PER_SAMPLE_16BIT,
    .channel_format = I2S_CHANNEL_FMT_RIGHT_LEFT,
    .intr_alloc_flags = ESP_INTR_FLAG_LEVEL3,
    .dma_buf_count = 14 * 2,
    .dma_buf_len = 1024,
    .use_apll = false,
    .tx_desc_auto_clear = true,
    .fixed_mclk = I2S_PIN_NO_CHANGE
  };
  cfg.mode = (i2s_mode_t)(I2S_MODE_MASTER | I2S_MODE_TX | I2S_MODE_DAC_BUILT_IN);
#if ESP_ARDUINO_VERSION_MAJOR >= 2
  cfg.communication_format = (i2s_comm_format_t)(I2S_COMM_FORMAT_STAND_MSB);
#else
  cfg.communication_format = (i2s_comm_format_t)(I2S_COMM_FORMAT_I2S_MSB);
#endif

  i2s_driver_install((i2s_port_t)0, &cfg, 0, NULL);
  i2s_set_dac_mode(I2S_DAC_CHANNEL_BOTH_EN);
  i2s_zero_dma_buffer((i2s_port_t)0);
}

void play(const char* filename) {
  toPlay = filename;
}

void loop() {
  if (toPlay != NULL) {
    stream = SD.open(toPlay);
    readText(stream, 4); // "RIFF"
    readNum(stream, 4); // File Size
    readText(stream, 4); // "WAVE"
    readText(stream, 4); // "fmt "
    readNum(stream, 4); // Format data length
    readNum(stream, 2); // Format type
    readNum(stream, 2); // Channel number
    i2s_set_sample_rates((i2s_port_t)0, readNum(stream, 4));
    readNum(stream, 4); // Stream speed (bytes/s)
    readNum(stream, 2); // Bytes/full sample
    readNum(stream, 2); // Bits/sample
    readText(stream, 4); // "data"
    dataEnd = readNum(stream, 4) + stream.position(); // Size of data section
    playing = true;
    toPlay = NULL;
  }
  if (bPaused) {
    return;
  }
  digitalWrite(4, LOW);
  if (bStop || stream.position() >= dataEnd) {
    bStop = false;
    playing = false;
    stream.close();
    i2s_zero_dma_buffer((i2s_port_t)0);
    return;
  }
  if (!stream || !stream.available()) return;
  const size_t sampleSize = sizeof(samples[0]) * 2;
  size_t count = stream.read((byte*)samples, min(sizeof(samples), dataEnd - stream.position())) / sampleSize;
  uint32_t* samples32 = (uint32_t*)samples;
  for (int i = 0; i < count; i++) {
    int16_t left = (samples[i * 2] >> 1) * vol >> 6;
    int16_t right = (samples[i * 2 + 1] >> 1) * vol >> 6;
    samples32[i] = (left << 16) | (right & 0xffff);
    samples32[i] += 0x80008000;
  }
  size_t nBytes;
  i2s_write((i2s_port_t)0, (const char*)samples32, sizeof(samples32[0]) * count, &nBytes, 1000);
  digitalWrite(4, HIGH);
}

void pause() {
  bPaused = true;
}

void resume() {
  bPaused = false;
}

void stop() {
  bStop = true;
}
}
