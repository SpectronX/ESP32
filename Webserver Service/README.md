## A WEBSERVER?

Well yes. It turns out we can make our ESP32 function as a webserver, where we can render some webpages in response to certain commands. Pretty interesting! I know. But how does this work?

## Working Principle

How are able to get the webpages we request for over the inernet? That's a good starting point. So basically webservers act as middlemen between us and information we want. Anytime you hop onto a search engine like google and ask for a particular information, you send a "GET" request through the domain to their server. The webserver takes over and searches through its database for the information you are looking for. When it's done, it sends a "POST" request through which you are able to get the information. These GET and POST are web based protocols that define how the communication between your device and the servers operate.

If we've ever come across a 404 error message, it was because the file/information we sought was not found. That's the role we are going to make our ESP32 play this time round. 

