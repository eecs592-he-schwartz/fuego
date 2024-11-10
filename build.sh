#!/usr/bin/env bash

if [[ ! -v BOOST_LIBDIR ]]; then
    export BOOST_LIBDIR='/usr/lib/x86_64-linux-gnu/' # this is just where boost is on debian
    echo "[warning] Using BOOST_LIBDIR='$BOOST_LIBDIR'
    You will likely need to set this explicitly to wherever your boost libraries are
    I tried to automate this with cmake but gave up"
fi

bash ./setup-build.sh
./configure --with-boost-libdir="$BOOST_LIBDIR"
make
