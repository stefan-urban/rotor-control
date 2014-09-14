#!/bin/sh

CONFIG_FILE=/etc/rotor_control.conf
DIRECTORY=/opt/rotor-control


printf " ------------------------------------------------------------------------------------------------- \n"
printf "  Building software ..."
printf "\n"

# Build everything
cd ../src
make > /dev/null

if [ -f rotor-control ];
then
	printf "       ... Finished!\n"
else
	printf "       ... Build failed!\n"
	exit
fi

printf " ------------------------------------------------------------------------------------------------- \n"
printf "  Copy executable to /opt/rotor-control/rotor-control ...\n"

# Copy executable to new location
if [ -d $DIRECTORY ];
then 
	printf "       Directory $DIRECTORY already exists!\n"
else
	mkdir $DIRECTORY
	printf "       Directory $DIRECTORY created!\n"
fi

if [ -f $DIRECTORY/rotor-control ];
then 
	while true; do
	    read -p "       Executable already exists. Do you wish to overwrite it? (y/n) " yn
	    case $yn in
		[Yy]* )
                    cp rotor-control $DIRECTORY/
                    printf "       Executable copied!\n"
                    break;;
		[Nn]* ) break;;
		* ) echo "Please answer yes or no.";;
	    esac
	done
else
	cp rotor-control $DIRECTORY/
	printf "       Executable copied!\n"
fi



printf " ------------------------------------------------------------------------------------------------- \n"
printf "  Copy start/stop scripts to /opt/rotor-control/ ...\n"

if [ -f $DIRECTORY/start-rotor-control.sh ];
then 
	while true; do
	    read -p "       Start/Stop scripts already exist. Do you wish to overwrite them? (y/n) " yn
	    case $yn in
		[Yy]* )
                    sudo cp ../scripts/start-rotor-control.sh $DIRECTORY
                    sudo cp ../scripts/stop-rotor-control.sh $DIRECTORY
                    printf "       ... Scripts copied!\n"
                    break;;
		[Nn]* ) break;;
		* ) echo "Please answer yes or no.";;
	    esac
	done
else
	sudo cp ../scripts/start-rotor-control.sh $DIRECTORY
	sudo cp ../scripts/stop-rotor-control.sh $DIRECTORY
	printf "       ... Scripts copied!\n"
fi


printf " ------------------------------------------------------------------------------------------------- \n"
printf "  Install daemon script to /etc/init.d/rotor-control ...\n"

if [ -f $DIRECTORY/rotor-control ];
then 
	while true; do
	    read -p "       Daemon script already exists. Do you wish to overwrite it? (y/n) " yn
	    case $yn in
		[Yy]* )
                    sudo cp ../scripts/rotor-control /etc/init.d/rotor-control
                    printf "       Daemon script installed!\n"
                    break;;
		[Nn]* ) break;;
		* ) echo "Please answer yes or no.";;
	    esac
	done
else
	sudo cp ../scripts/rotor-control /etc/init.d/rotor-control
	printf "       Daemon script installed!\n"
fi




printf "       ... Finished!\n"
printf " ------------------------------------------------------------------------------------------------- \n"
printf "  Install configuration file $CONFIG_FILE ...\n"


if [ -f $CONFIG_FILE ];
then 
	while true; do
	    read -p "       Configuration file already exists. Do you wish to overwrite it? (y/n) " yn
	    case $yn in
		[Yy]* )
                    sudo cp ../docs/rotor_control.conf.sample $CONFIG_FILE
                    printf "       ... Configuration file copied!\n"
                    break;;
		[Nn]* ) break;;
		* ) echo "Please answer yes or no.";;
	    esac
	done
else
	sudo cp ../docs/rotor_control.conf.sample $CONFIG_FILE
	printf "       ... Configuration file copied!\n"
fi



printf "\n"
