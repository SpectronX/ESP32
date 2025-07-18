## WiFi Capabilites with ESP32
Unlike Arduino, ESP32 come with some cool features like WiFi and Bluetooth capabilities which I would be exploring. 
Looking at today's world of IoT, it is without a doubt that this microcontroller can have a role to play in wireless connectivity for efficient data transfer in some levels. 

Here, I would explore the various modes in which we can setup our ESP32: as a station or an access point.

## Setting up as a STATION
In this mode, we are basically making the ESP32 behave like our phones when they connect to a WiFi Network. In this case, there's already an active network, and we're setting the ESP32 in "listening" mode to detect and connect to it: as long as we know the password or no password at all(like in this case 😄). In using VS Code, Wokwi provides a sandboxed wireless access point one can use in running their simulations with ssid = "Wokwi-GUEST" and password = "" (no password)

⚠️ Just a note: Always be cautious about which networks you connect to—especially open ones. Staying safe is always best.

The code for this kind of setup is provided in this [file](Station.ino)

## Setting up as an ACCESS POINT
In this mode, the ESP32 acts as the Wi-Fi network we would be connecting to: like a router or mobile hotspot. With this setup, a network name (SSID) and a password is defined, after which the ESP32 starts broadcasting it. Once active, any device with the correct credentials can connect to it.

Since I'm running this in a simulation environment, the access point can be created, but actually getting a device to connect to it isn't possible here. Nevertheless, it's the same code that gets the ESP32 operating in the mode in the real world with actual hardware.

The code for this setup is provided in this [file](AP.ino)
