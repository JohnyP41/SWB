#!/bin/bash

for i in `seq 1 3`; do
	echo -n "Running test #$i... ";
	cd test-$i
	make &> /dev/null
	if [ "$?" -eq "0" ]; then
		echo "PASS"
	else
		echo "FAIL"
	fi
	cd ..
done
