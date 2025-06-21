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

By including <mark>#include <WebServer.h></mark> library, we are ready to setup our mini webserver on the ESP32. We first create an object of the library names <mark>server</mark> which sets up the webserver on the ESP32 to listen on port 80: the standard port for HTTP communication.

We set up a web server on the ESP32 to listen on port 80, which is the standard port for HTTP communication. This allows the ESP32 to handle web requests from devices like phones or computers.

The ESP32 connects to a Wi-Fi network (Access Point) using its WiFi.begin() function. Once connected, it is assigned an IP address by the network's DHCP server. This IP address is used by other devices on the network to reach and communicate with the ESP32.

Using the server.on() function (from the WebServer library), we define routes — specific URL paths (like /, /ledon, /ledoff) and what the ESP32 should do when each path is visited. These routes are mapped to functions like Homepage(), ledon(), and ledoff() which control the logic (e.g., toggle an LED and respond with a webpage).

The "localhost" in the Serial.println("Open http://localhost:8180") is specific to the Wokwi simulation. It forwards traffic from your actual browser to the simulated ESP32. This is necessary because the ESP32 in Wokwi runs in a sandboxed environment — so port forwarding is used to "bridge" your computer and the simulation.

Each command that the ESP32 performs is triggered by visiting a route — and the corresponding function executes to serve a response (HTML or plain text) and optionally perform actions (e.g., turn an LED on or off).

