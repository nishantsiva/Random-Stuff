
sudo echo 1 > /proc/sys/net/ipv4/ip_forward 
sudo iptables -I FORWARD -i wlan0 -o eth0 -j ACCEPT
sudo iptables -I FORWARD -o wlan0 -i eth0 -j ACCEPT

