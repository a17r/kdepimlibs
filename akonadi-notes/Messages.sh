#! /bin/sh
$XGETTEXT `find . src -name "*.cpp" -o -name "*.h" | grep -v "/tests"` -o $podir/akonadinotes.pot
$XGETTEXT *.cpp -o $podir/akonadinotes.pot