namespace pokemon {
const char* mainScript = R"(
  wait scene 1
  wait 1000ms
  spawn Mom at 101, 114.0625
  move Mom to 101, 116
  say "MOM: $name, we're here, honey!"
  say "It must be tiring riding with our things in the moving truck."
  wait player May
  move May -> 11, 13
  move May -> 9, 3
  say May "Dima should finish this game!"
  say May "Nobody loves me :("
)";
}
