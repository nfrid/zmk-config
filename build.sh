#!/bin/sh

set -e

cd "$(dirname "$0")" || exit

BOARD=nice_nano_v2
LEFT=corne_left
RIGHT=corne_right

cd .. || exit

west build app -b $BOARD -d build/$LEFT -- -DSHIELD=$LEFT
cp build/$LEFT/zephyr/zmk.uf2 build/left.uf2
west build app -b $BOARD -d build/$RIGHT -- -DSHIELD=$RIGHT
cp build/$RIGHT/zephyr/zmk.uf2 build/right.uf2
