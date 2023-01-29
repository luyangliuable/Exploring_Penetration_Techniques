#!/bin/bash 

gcc -fno-stack-protector -z execstack -g $1
