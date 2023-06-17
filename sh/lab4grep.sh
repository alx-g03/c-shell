#!/bin/bash

if [[ ! -d $1 ]]; then
    echo "parametru invalid" >&2
    exit 1
fi

dirname=$1
cd $dirname

if [[ ! -f $2 ]]; then
    echo "parametru invalid" >&2
    exit 1
fi

filename=$2

{ head -n 1 $filename; grep -E '^[a-zA-Z ]+,[0-9]+$' $filename ; } > "tempfile.temp"
mv "tempfile.temp" $filename
