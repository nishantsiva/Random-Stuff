sudo ip neigh flush all
sudo arp
sudo ifconfig wlan0 192.16.1.58/24 up  
sudo arp -i wlan0 -s 192.16.1.135 b8:ee:65:7e:0d:b9


