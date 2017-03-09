#!/bin/bash

set -e
set -v

git clone https://github.com/smackers/smack.git -b develop --depth=1
cd smack/bin
./build.sh


