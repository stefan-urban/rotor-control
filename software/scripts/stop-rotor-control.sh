#!/bin/sh

printf "Kill all rotor control processes: "

killall -q rotor-control > /dev/null &
killall -q rotctld > /dev/null &

printf "... Done!\n"
