#!/bin/bash

echo -e "updating distro"
sudo apt update && sudo upgrade

echo -e "installing c and c++ headers"
sudo apt install -y gcc-multilib

echo -e "install barium deps"
sudo apt install -y cmake flex lld llvm
wget http://ftp.gnu.org/gnu/bison/bison-3.5.tar.gz
tar -zxvf bison-3.5.tar.gz
cd bison-3.5 && ./configure && make && sudo make install 
