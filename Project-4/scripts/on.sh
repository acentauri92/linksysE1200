#!/bin/ash

echo "Switching LED on ..." > /dev/console

echo 0 > /sys/class/gpio/gpio6/value


echo "Content-type: text/html"
echo ""

echo "<html><head><title>LED STATUS</title></head><body>"

echo "<h1>LED ON</h1>"

echo "</body></html>"
