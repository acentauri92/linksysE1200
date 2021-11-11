#!/bin/ash

echo "Exporting GPIO pin 6 ..." > /dev/console

echo 6 >/sys/class/gpio/export

echo out >/sys/class/gpio/gpio6/direction
