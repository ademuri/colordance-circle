#!/bin/bash

set -euo pipefail

mkdir -p build
pushd build
cmake .. -DBUILD_SIMULATOR=false -DCMAKE_BUILD_TYPE=Release
make
./generictest
popd
