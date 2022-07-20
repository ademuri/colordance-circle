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

### Simulator

The simulator uses SDL2 to render the LEDs. To build it, first install the SDL2 development library (e.g. `sudo apt install libsdl2-dev`), then configure CMake to build it with `cmake .. -DBUILD_SIMULATOR=true`. Then, from the build dir, run it with `./lib/simulator/Simulator`.

To run the simulator with the Processing controller, from the build directory run:

```bash
${PROCESSING_HOME?}/processing-java --sketch=../controller/processing_controller --run | ./lib/simulator/Simulator
```