#!/bin/bash

ip neigh flush all

ifconfig wlan0 192.168.14.16/24 up
ifconfig
arp -i wlan0 -s 192.168.14.79 9c:ad:97:95:22:77
