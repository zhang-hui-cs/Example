const fs = require('fs');
const { Console } = require('console');

const output = fs.createWriteStream('./stdout.log');
const errorOutput = fs.createWriteStream('./stderr.log');

// custom simple logger
const logger = new Console({
  stdout: output,
  stderr: errorOutput
});
// use it like console
const count = 5;
logger.log('count: %d', count);
// in stdout.log: count 5
logger.error('this is error msg');