#!/bin/sh
rm -rf docs
mkdir docs
doxygen
cd docs
git add .
