#!/bin/sh

set -e

srcdir=`dirname "$0"`
test -z "$srcdir" && srcdir=.

ORIGDIR=`pwd`
cd "$srcdir"

cd "$srcdir/src/xlat/" && ./gen.sh && cd -

autoreconf --force --verbose --install
cd "$ORIGDIR"

if test -z "$NOCONFIGURE"; then
    "$srcdir"/configure "$@"
fi
