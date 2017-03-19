#!/bin/bash
sudo ip neigh flush all
sudo arp
sudo ifconfig eth0 10.100.100.134/24 up
sudo arp -i eth0 -s 10.100.100.135 28:d2:44:8a:fb:e9


