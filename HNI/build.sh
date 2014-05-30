#!/bin/sh

#if [[ "$HPHP_HOME" == "" ]]; then
#  echo HPHP_HOME environment variable must be set!
#  exit 1
#fi
echo "build start..."
hphpize
cmake .
make -j5

