#!/bin/bash

if [[ ! -d $1 ]]; then
    echo "parametru invalid" >&2
    exit 1
fi

dirname=$1
cd $dirname

for file in *.txt; do
    if [[ $(head -n 1 $file) == *"IN"* ]]; then
        echo $file
    fi
done
