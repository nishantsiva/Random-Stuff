sudo ip neigh flush all
sudo arp
sudo iptables --flush

sudo arp -i eth0 -s 10.100.100.134 f0:4d:a2:a5:8a:ab
sudo arp -i wlan0 -s 192.16.1.58 24:0a:64:00:cs

sudo route del default gw 192.168.3.254

sudo iptables -I POSTROUTING -o wlan0 -t nat -j MASQUERADE 

sudo iptables -t nat --append PREROUTING -i wlan0 -p tcp --dport 80 -j DNAT --to-destination 74.125.236.84:80
sudo iptables -t nat --append PREROUTING -i eth0 -p tcp --dport 80 -j DNAT --to-destination 74.125.236.84:80
sudo route add default gw 192.168.3.254

