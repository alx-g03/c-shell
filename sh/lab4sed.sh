#!/bin/bash

dirname=$1
filename=$2
oldname=$3
newname=$4

cd $dirname
sed -i "s/$oldname/$newname/" $filename
