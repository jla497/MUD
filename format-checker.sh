#!/bin/bash
./format-checker-util 1 Client/ Logging/ MudGameEngine/ MudServer/ Networking/ > output.xml

if test $(cat output.xml | grep -c "<replacement ") -gt 0
	then
	echo "code not formatted. Rejecting merge request..."
	exit
fi
echo "passed format checker..."
