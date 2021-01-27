#!/bin/bash


find -ctime -$2 -a \( -name "*$1" \) -exec tar -rvf $3.tar "{}" \;





