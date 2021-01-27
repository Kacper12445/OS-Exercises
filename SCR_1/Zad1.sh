#!/bin/bash

export LC_ALL=C
dzien=$(date +%u)

nazwadnia=$(date +%A)

if (( $dzien < 6 ));
then
	echo "$nazwadnia jest dniem roboczym"
else
	echo "$nazwadnia jest dniem weekendu"

fi
