# Colordance Circle

This is not an official Google project.

## Arduino

To build or upload for Arduino, you'll need the Fully Qualified Board Name
(FQBN) of the board you're building for. You can find this using the
`arduino-cli` tool. When the board is plugged in, run:

``` arduino-cli board list ```

This will print the list of possible boards - grab the FQBN for the board
you're using and set it as an environment variable:

``` export FQBN="..." ```

To compile for Arduino, go into the `arduino` directory and run `make`. To
upload, run `make upload`. By default, it will use the port `/dev/ttyACM0`,
which should work for Ubuntu. You can set the `PORT` environment variable from
the output of the arduino-cli command as above if needed.

On Mac, if you're using Homebrew, you'll need to use `gmake` instead of `make`,
since the `make` version is very old and doesn't support the multi-line bash
function used in the `Makefile`.
