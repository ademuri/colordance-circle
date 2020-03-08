#!/bin/bash

set -euo pipefail
export FQBN="Candy Kingdom Firefly:samd:rfboard" 
cd arduino
make build/arduino-cli
build/arduino-cli --config-file arduino-cli.yaml core install "Candy Kingdom Firefly:samd"
make
