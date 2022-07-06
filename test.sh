#!/bin/bash

set -euo pipefail

mkdir -p build
pushd build
cmake .. -DBUILD_SIMULATOR=false
make
./generictest
popd
