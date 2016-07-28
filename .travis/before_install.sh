#!/bin/bash

# Do pre-install commands
echo "OS-name: $TRAVIS_OS_NAME"

function fdict_osx {
    brew update
    cpp --help 
    man cpp
    {
      echo CPP = cpp -E -xc
    } > setup.make
}

function fdict_linux {
    sudo apt-get install -qq gfortran
}

case "$TRAVIS_OS_NAME" in
   osx)
    fdict_osx
    ;;
   *)
    fdict_linux
    ;;
esac

