#!/bin/bash

set -euo pipefail

pushd "$(git rev-parse --show-toplevel)"/.git/hooks
ln -s ../../.githooks/pre-commit pre-commit
popd
