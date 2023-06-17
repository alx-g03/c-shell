#!/bin/bash

if [[ ! -d $1 ]]; then
    echo "parametru invalid" >&2
    exit 1
fi

dirname=$1
cd $dirname
inventar="depozit.csv"

shift

for file in $@; do
    if [[ ! -f $file ]]; then
        echo "parametru invalid" >&2
        exit 1
    fi
    
    tip_transport=$(head -n 1 $file)
    
    tail -n +2 $file | while IFS=',' read -r produs cantitate; do
        grep -q "^$produs," $inventar
        if [ $? -eq 0 ]; then
            if [ $tip_transport == "IN" ]; then
                awk -F',' -v produs="$produs" -v cantitate="$cantitate" 'BEGIN { OFS = "," } $1 == produs { $2 += cantitate } 1' $inventar >"$inventar.tmp"
                mv "$inventar.tmp" $inventar
            elif [ $tip_transport == "OUT" ]; then
               awk -F',' -v produs="$produs" -v cantitate="$cantitate" 'BEGIN { OFS = "," } $1 == produs { $2 -= cantitate } 1' $inventar >"$inventar.tmp"
               mv "$inventar.tmp" $inventar
            fi
        else
            if [ $tip_transport == "IN" ]; then
                echo "$produs,$cantitate" >>$inventar
            elif [ $tip_transport == "OUT" ]; then
                echo "$produs,-$cantitate" >>$inventar
            fi
        fi
    done
done
