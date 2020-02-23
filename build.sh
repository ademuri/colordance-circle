#!/bin/bash

set -euo pipefail

platformio ci --board teensy31 --lib=generic arduino/direct  --project-option="lib_deps=FastLED" --project-option="build_flags=-DWS2812_PIN=0" --exclude=lib/generic/build --exclude=lib/generic/simulator
