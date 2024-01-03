#!/bin/sh

BOARD=nice_nano_v2
LEFT=corne_left
RIGHT=corne_right
UUID=0042-0042
ZMK_DIR=..

set -e

cd "$(dirname "$0")" || exit

cd $ZMK_DIR || exit

echo
echo "building left board's firmware..."
west build app -b $BOARD -d build/$LEFT -- -DSHIELD=$LEFT
cp build/$LEFT/zephyr/zmk.uf2 build/left.uf2

echo
echo "building right board's firmware..."
west build app -b $BOARD -d build/$RIGHT -- -DSHIELD=$RIGHT
cp build/$RIGHT/zephyr/zmk.uf2 build/right.uf2

flash() {
  echo
  echo "waiting for $1 side to be available..."
  until [ -e /dev/disk/by-uuid/$UUID ]; do
    sleep 0.5
  done

  echo "mounting $1 side..."
  mkdir -p /tmp/zmk
  sudo mount -U 0042-0042 /tmp/zmk
  echo "flashing $1 side..."
  sudo cp "build/$1.uf2" /tmp/zmk

  echo "waiting for $1 side to disconnect..."
  until [ ! -e /dev/disk/by-uuid/$UUID ]; do
    sleep 0.5
  done
}

flash left
flash right
