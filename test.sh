#!/bin/bash

set -euo pipefail

mkdir -p generic/build
pushd generic/build
cmake .. -DBUILD_SIMULATOR=false
make
./generictest
popd
