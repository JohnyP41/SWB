#!/bin/bash

RETCODE=1

./doexit
[[ "$?" -eq "42" ]] && RETCODE=0

if [ "$RETCODE" -eq 0 ]; then
	echo PASS
else
	echo FAIL
fi
exit $RETCODE
