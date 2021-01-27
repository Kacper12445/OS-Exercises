#!/bin/sh

trap ' echo Jestem sygnałodporny, próbuj dalej' {1..15}


while true
do
	echo -n "$$ "
	date
	sleep 1
done
