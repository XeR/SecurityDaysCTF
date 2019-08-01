#!/bin/sh
echo 'Starting task...'
socat tcp4-listen:12345,reuseaddr,fork exec:./main
