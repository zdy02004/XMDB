#!/bin/sh
set -x       

ipcs -m | awk '{if(NR>3)print $2}' |
while read s
do
    ipcrm -m $s
done
