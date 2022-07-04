# Colordance Circle

An art project that uses arrays of colored lights around a circle to create
kaleidoscopic colored shadows.

"This is not an officially supported Google product"

## Building

This project uses two build systems, PlatformIO and CMake. PIO is for code which
runs on embedded devices - these run the actual hardware. CMake is for running
tests on standard PCs.

To build with PlatformIO, run `pio run -e <env>`, where `<env>` is one defined
in [platformio.ini](platformio.ini) (e.g. `teensy`).

To run the tests:

```
mkdir -p build
cd build
cmake .. -DBUILD_SIMULATOR=false
make && ./generictest
```