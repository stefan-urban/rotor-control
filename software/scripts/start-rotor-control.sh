#!/bin/bash

DEVICE_FILE="/dev/rotor_control"


#
# Start rotor control application
#
printf "Starting rotor-control: "
/opt/rotor-control/rotor-control -s on &

printf "... "
printf '\e[32m%-6s\e[m\n' "OK"


#
# Start hamlib service
#

printf "Waiting to pseudoterminal file: "

# Wait for pseudoterminal device
i="0"

while [ $i -lt 2 ] ; do
	if [ -e "$DEVICE_FILE" ]
	then
		i="10"
		printf "... "
		printf '\e[32m%-6s\e[m\n' "OK"
		break;
	else
		printf "."
	fi

	i=$((i+1))
	sleep 1
done

if [ $i != "10" ]
then
	printf '\e[31m%-6s\e[m\n' " Failed"
	exit
fi

# Set permissions for dialout group
chown root:dialout $DEVICE_FILE
chmod 660 $DEVICE_FILE


printf "Starting hamlib: ... "
rotctld --model=602 --rot-file=$DEVICE_FILE --serial-speed=115200 &
printf '\e[32m%-6s\e[m\n' "OK"

