#!/bin/bash

ip neigh flush all

 ifconfig eth0 10.100.100.89/24 up
 sudo arp -i eth0 -s 10.100.100.79 64:51:06:a7:f4:f7

 ifconfig
 
 
 arp
 
