sudo route del default gw 192.168.3.254

sudo iptables -I POSTROUTING -o wlan0 -t nat -j MASQUERADE 

sudo iptables -t nat --append PREROUTING -i wlan0 -p tcp --dport 80 -j DNAT --to-destination 74.125.236.84:80
sudo iptables -t nat --append PREROUTING -i eth0 -p tcp --dport 80 -j DNAT --to-destination 74.125.236.84:80
sudo route add default gw 192.168.3.254

