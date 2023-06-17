#!/bin/bash

if [[ ! -d $1 ]]; then
    echo "parametru invalid" >&2
    exit 1
fi

dirname=$1
cd $dirname

for file in *.txt; do
    echo -n $file' ' 
    awk '{ sum += $2 } END { print sum }' FS=, $file
done
