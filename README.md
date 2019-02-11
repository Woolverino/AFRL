WPLASH
AFRL Capstone Project
AY 2019
Written by Chandler Gach


howmanypeoplearearound is a tool by the author schollz, found at the
Github page: https://github.com/schollz/howmanypeoplearearoundself.
howmanypeoplearearound works by sniffing WiFi probe requests, and then
checks the MAC address of the request against a database. The program
returns the number of all devices probing WiFi networks with a MAC
address (non-unique portion) that matches known MAC addresses of cellular
devices.  Furthermore, the tool can be set to look for devices within a
certain distance based off of the RSSI value returned.

Our tool utilizes this tool and runs it on a loop, feeding output to
specific devices such as an LED light strip (loading display) and a digital
output (to display number of phones detected).
