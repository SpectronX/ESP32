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

Once it's networked, any device on that network (like your phone or laptop) can connect to the ESP32’s IP address and send HTTP requests. The ESP32 will handle them and respond accordingly. It might be returning a webpage that shows live sensor data or toggles an LED (which we would be trying)
