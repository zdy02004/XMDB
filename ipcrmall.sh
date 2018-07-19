#!/bin/sh
set -x       
ipcs | grep `whoami` | grep 0x0000 | awk '{if (NF > 5 ) print "ipcrm -m "$2}' | sh
