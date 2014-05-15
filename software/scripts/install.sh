#!/bin/sh


printf " ------------------------------------------------------------------------------------------------- \n"
printf "  Building software!"
printf "\n"

# Build everything
cd ../src
make > /dev/null

printf "       ... Finished!\n"

printf " ------------------------------------------------------------------------------------------------- \n"
printf "  Copy executable to new location!\n"

# Copy executable to new location
DIRECTORY=/opt/rotor-control
if [ -d $DIRECTORY ];
then 
	printf "       Directory $DIRECTORY already exists!\n"
else
	mkdir $DIRECTORY
	printf "       Directory $DIRECTORY created!\n"
fi

if [ -d $DIRECTORY ];
then 
	while true; do
	    read -p "       Executable already exists. Do you wish to overwrite it? (y/n) " yn
	    case $yn in
		[Yy]* ) break;;
		[Nn]* ) exit;;
		* ) echo "Please answer yes or no.";;
	    esac
	done
else
	mkdir $DIRECTORY
fi

cp rotor-control $DIRECTORY/
printf "       Executable copied!\n"


printf " ------------------------------------------------------------------------------------------------- \n"
printf "  Copy start/stop scripts to new location!\n"

sudo cp ../scripts/start-rotor-control.sh $DIRECTORY
sudo cp ../scripts/stop-rotor-control.sh $DIRECTORY

printf "       ... Finished!\n"

printf " ------------------------------------------------------------------------------------------------- \n"
printf "  Install rotor-control daemon!\n"

sudo cp ../scripts/rotor-control /etc/init.d/rotor-control

printf "       ... Finished!"
printf " ------------------------------------------------------------------------------------------------- \n"
printf "  Install configuration file!\n"

sudo cp ../docs/rotor_control.conf.sample /etc/rotor_control.conf.sample

printf "       ... Finished!"

printf "\n\n"
