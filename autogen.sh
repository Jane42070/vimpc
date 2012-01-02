#!/bin/sh
if test -d /usr/local/share/aclocal; then
    export ACLOCAL_FLAGS="${ACLOCAL_FLAGS} -I /usr/local/share/aclocal"
fi
touch NEWS README AUTHORS ChangeLog
autoreconf --force --install
