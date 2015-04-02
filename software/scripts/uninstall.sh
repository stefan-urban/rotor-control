#!/bin/bash

CONFIG_FILE=/etc/rotor_control.conf
DAEMON_FILE=/etc/init.d/rotor-control

DIRECTORY=/opt/rotor-control/
ROTOR_CONTROL_FILE=rotor-control
START_SCRIPT_FILE=start-rotor-control.sh
STOP_SCRIPT_FILE=stop-rotor-control.sh


printf " ------------------------------------------------------------------------------------------------- \n"
printf "  Uninstalling rotor control"
printf "\n\n"

# Executeable
if [ -f $DIRECTORY$ROTOR_CONTROL_FILE ]
then
	rm $DIRECTORY$ROTOR_CONTROL_FILE
	printf "  Binary deleted\n"
else
	printf "  Binary already deleted\n"
fi

# Daemon File
if [ -f $DAEMON_FILE ]
then
	rm $DAEMON_FILE
	printf "  Daemon script deleted\n"
else
	printf "  Daemon script already deleted\n"
fi

# Start and stop files
if [ -f $DIRECTORY$START_SCRIPT_FILE ]
then
	rm $DIRECTORY$START_SCRIPT_FILE
	printf "  Start script deleted\n"
else
	printf "  Start script already deleted\n"
fi
if [ -f $DIRECTORY$STOP_SCRIPT_FILE ]
then
	rm $DIRECTORY$STOP_SCRIPT_FILE
	printf "  Stop script deleted\n"
else
	printf "  Stop script already deleted\n"
fi

if [ "$(ls -A $DIRECTORY)" ]; then
	printf "  Directory $DIRECTORY is not empty! Can not be deleted!"
	printf "\n"
else
	rmdir $DIRECTORY
	printf "  Directory $DIRECTORY deleted\n"
fi

# Configuration can be saved till next install
if [ -f $CONFIG_FILE ];
then
	printf "\n"
	while true; do
		read -p "  Also delete config file? (y/n) " yn
		case $yn in
			[Yy]* )
				rm $CONFIG_FILE
				printf "       ... Config file deleted!\n"
				break;;
			[Nn]* ) break;;
			* ) echo "  Please answer y or n.";;
		esac
	done
else
	printf "  Config file already deleted\n"
fi

