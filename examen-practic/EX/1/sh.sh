#!/bin/bash

filename=$1

if [[ ! -f $filename ]]; then
    echo "parametru invalid" >&2
    exit 1
fi

grep -E -v -c '^[1-9][0-9][0-9][0-9][0-9][0-9][0-9][0-9][0-9][0-9][0-9][0-9][0-9]$' $filename
