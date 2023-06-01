import parser from 'osu-parser';
import clipboard from 'clipboardy';

const size = [550, 400];

const genCircle = node => {
    let circle = '';
    let x = node['position'][0] * 128 / size[0], y = node['position'][1] * 128 / size[1];
    if (x > 0 && x < 128 && y > 0 && y < 128) {
        circle += node['startTime'].toFixed() + ', ';
        circle += (x).toFixed() + ', ';
        circle += (y).toFixed() + ', ';
    }
    return circle;
};

parser.parseFile('WellMeetAgain.osu', function (err, beatmap) {
    // console.log(beatmap);
    let minPos = [99999999999999999, 99999999999999999], maxPos = [0, 0];
    let out = '';
    Object.values(beatmap['hitObjects']).forEach(node => {
        if (node['position'][0] < minPos[0]) minPos[0] = node['position'][0];
        if (node['position'][1] < minPos[1]) minPos[1] = node['position'][1];
        if (node['position'][0] > maxPos[0]) maxPos[0] = node['position'][0];
        if (node['position'][1] > maxPos[1]) maxPos[1] = node['position'][1];
        if (node['objectName'] == 'circle') {
            out += genCircle(node);
        } else if (node['objectName'] == 'slider') {
            let points = Object.values(node['points']);
            out += genCircle(node);
            out += genCircle({
                startTime: node['startTime'] + node['duration'],
                position: points[points.length - 1]
            });
        }
    });
    clipboard.writeSync(out);
    console.log(minPos);
    console.log(maxPos);
});
