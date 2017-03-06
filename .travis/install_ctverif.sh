#!/bin/bash
PROJECT_NAME="verifying-constant-time"
# clone ct-verif
#git clone --depth 1 https://github.com/Qthan/verifying-constant-time.git

pwd
#./z3/z3 -h
#cd $PROJECT_NAME
pwd
echo "a"
git submodule init tools/smack tools/bam-bam-boogieman
echo "b"
git submodule init tools/boogie tools/z3
echo "c"
git submodule update
echo "d"
cd bin
./provision.sh
#cd ../..
#pwd
#ls
#make ctequals
