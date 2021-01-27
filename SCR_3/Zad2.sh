#!/bin/bash


trap 'echo Nie tym razem' SIGUSR1 SIGALRM SIGTERM SIGUSR2
x=1;
while true 
do
    echo "Napis pojawił się po raz: $x"
    sleep 1;
    x=$[x + 1];

done
