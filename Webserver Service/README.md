## A WEBSERVER?

Well yes. It turns out we can make our ESP32 function as a web server, where it can serve webpages in response to certain commands. Pretty interesting! I know. But how does this actually work?

## Working Principle

How are able to get the webpages we request for over the inernet? That's a good starting point. 

Whenever you get onto you a browser and type a web address say (www.google.com), your browser sends a "GET" request to a web server over the internet. Here is where web servers come in. Basically, this server is like a middleman between us and information we want. It receives the request, process it and then sends a response back: often in the form of an HTML page.

Ever come across the classic 404 Error display? Yeah, that's what one gets when the content they asked for is not found. The communication happens using the HTTP protocol, which defines how messages are ordered and transmitted between clients and servers. 

## How this fits into the ESP32

In the same way big websites use web servers to respond to requests, the ESP32 can also run a mini web server. It can either:

- Host its own Wi-Fi network (Access Point Mode), or

- Join your home Wi-Fi network (Station Mode)

Once it's networked, any device on that network (like your phone or laptop) can connect to the ESP32’s IP address and send HTTP requests. The ESP32 will handle them and respond accordingly. It might be returning a webpage that shows live sensor data or toggles an LED.

To try this out, we would toggle an LED from a web page using the ESP32. 

## Summary of what's going on in the code
In my practices, I use the Wokwi Simulator in VS code, so some lines of code would be required as compared to using the components in-person. 

By including the **#include <WebServer.h>** library, we are ready to setup our mini webserver on the ESP32. We first create an object of the library names **server** which sets up the webserver on the ESP32 to listen on port 80: the standard port for HTTP communication. This allows the ESP32 to handle web requests from devices like phones and computers.

I had the ESP32 connect to the Guest Wi-Fi network in the simulator, and once connected, it is assigned an IP address by the network's DHCP server. This IP address is much like the "name" other devices on the network would use to reach and communicate with the ESP32.

Using the **server.on()** function, routes (specific URL paths like /ledon) are defined. These routes are mapped to functions like Homapage() which controls the logic. These functions tells the ESP32 what to do when those routes are visited.

It can be seen that, my code has a line which has **Serial.println("Open http://localhost:8180")**. The "localhost" is specific to the Wokwi simulation. It forwards traffic from the simulated environment to my browswer. Since the simution runs in a sandboxed environment, port forwarding is neccessary to "bridge" my computer and the simulation.

This port forwarding can be achieved by including this line of code in the Wokwi.toml when using VS code.

#Forward http://localhost:8180 to port 80 on the simulated ESP32:

[[net.forward]]
from = "localhost:8180"
to = "target:80"
