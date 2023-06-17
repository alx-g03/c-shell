#!/bin/bash

filename=$1

if [[ ! -f $filename ]]; then
    echo "parametru invalid" >&2
    exit 1
fi

sed -i "s/un/1/" $filename
sed -i "s/doi/2/" $filename
sed -i "s/trei/3/" $filename
