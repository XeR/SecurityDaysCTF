#!/bin/sh
printf '%0100d' 0 | ncat 127.0.0.1 9000
