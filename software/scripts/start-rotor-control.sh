#!/bin/sh

DEVICE_FILE="/dev/rotor_control"


#
# Start rotor control application
#
printf "Starting rotor-control: "
/opt/rotor-control/rotor-control -s on &

printf "... OK!\n"


#
# Start hamlib service
#

printf "Waiting to pseudoterminal file: "

# Wait for pseudoterminal device
while : ; do
	if [ -e "$DEVICE_FILE" ]
	then
		printf "... OK!\n"
		break;
	else
		printf "."
	fi

	sleep 1
done


printf "Starting hamlib: ... OK!"
rotctld -m 602 -r $DEVICE_FILE &

printf "\n"
