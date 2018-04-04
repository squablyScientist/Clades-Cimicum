#!/bin/zsh

tail $1 -n3 | head -n1 | tail -c 13 | head -c 12

