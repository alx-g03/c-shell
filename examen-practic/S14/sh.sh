#!/bin/bash

filename=$1

if [[ ! -f $filename ]]; then
    echo "parametru invalid" >&2
    exit 1
fi

awk '($6-$2)/($4-$2)==($5-$1)/($3-$1) {print NR}' $filename
