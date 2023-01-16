#!/bin/bash

su root

sysctl -w kernel.randomize_va_space=0
exit
