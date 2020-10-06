#!/bin/bash
# Copyright (c) 2019-2020 The Hush developers
# Released under the GPLv3


#TODO: autodect version number, error handling
FILE="hush-3.5.0-linux-amd64.tar"

mkdir build
cp sapling*.params build/
cd src
cp komodod komodo-cli komodo-tx hushd hush-cli hush-tx hush-smart-chain ../build
cd ../build
tar -f $FILE -c  *
gzip $FILE

