#!/bin/bash

filename=$1

if [[ ! -f $filename ]]; then
    echo "parametru invalid" >&2
    exit 1
fi

while IFS=' ' read -r victorie egal infrangere; do
    echo $((3*$victorie+$egal))
done <$filename
