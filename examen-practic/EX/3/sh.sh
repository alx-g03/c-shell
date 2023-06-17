#!/bin/bash

filename=$1

if [[ ! -f $filename ]]; then
    echo "parametru invalid" >&2
    exit 1
fi

awk '{print NF}' $filename
