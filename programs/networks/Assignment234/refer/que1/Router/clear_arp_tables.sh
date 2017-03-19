#!/bin/bash

sudo ip neigh flush all
sudo iptables --flush

sudo ifconfig eth0 10.100.100.79/24 up
sudo ifconfig wlan0 192.168.14.79/24 up
ifconfig
