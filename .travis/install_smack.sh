#!/bin/bash

set -x
set -e

git clone https://github.com/danielsn/smack.git -b develop --depth=1
echo "a"
cd smack/bin
pwd
./build.sh


