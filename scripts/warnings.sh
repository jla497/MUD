#!/bin/bash
BDIR="build"
DB="compile_commands.json"
DBPATH="$BDIR/$DB"
if [ ! -f $DBPATH ]; then
	echo "Error: $DBPATH does not exist. Run cmake in $BDIR/ to create it."
	exit 1
fi

cleanup() {
	rm -f $DB
	exit 0
}
# i'm pretty sure this doesn't even work
trap 'cleanup' SIGINT

if [ ! "$(readlink compile_commands.json)" = "$DBPATH" ]; then
	rm -f $DB
	ln -s $DBPATH $DB
fi
scripts/extra/run-clang-tidy.py -header-filter=.* -checks='*,-readability-*,-google-*,-llvm-*,-fuchsia-*' '^((?!google|gtest).)*$' > warnings.txt 2>&1
cleanup
