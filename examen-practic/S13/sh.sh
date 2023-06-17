#!/bin/bash

filename=$1
x=$2

if [[ ! -f $filename ]]; then
    echo "parametru invalid" >&2
    exit 1
fi

# metoda 1
while read -r line; do
    if [[ ${#line} > $x ]]; then
        echo $line
    fi
done <$filename

# metoda 2
# awk -v len=$x 'length>len' $filename
