#!/bin/bash
PROJECT_NAME="verifying-constant-time"
# clone ct-verif
#git clone --depth 1 https://github.com/Qthan/verifying-constant-time.git

set -x
pwd
#./z3/z3 -h
#cd $PROJECT_NAME
pwd
git submodule init tools/smack tools/bam-bam-boogieman
git submodule init tools/boogie tools/z3
git submodule update
cd bin
./provision.sh
#cd ../..
#pwd
#ls
#make ctequals
