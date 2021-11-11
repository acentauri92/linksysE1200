#!/bin/ash

echo 1 > /sys/class/gpio/gpio6/value


echo "Content-type: text/html"
echo ""

echo "<html><head><title>LED STATUS</title></head><body>"
echo "<h1>LED OFF</h1>"

echo "</body></html>"
