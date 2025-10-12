# hbchat
Chatting application for 3DS (and Wii coming soon!)

## If you would like to commit
Please help me add accounts, mod tools, security fixes, and things, I am dying from toxic people online...


## Extra clients and other things
_**There's a web client now!**_

Enjoy chatting with 3DS users and other web users on **THE WEB CLIENT**

Link:
[hbchat Web Client](http://104.236.25.60/)

Domain Link:
http://hbchat.jumpingcrab.com/
(Best name someone could get for a free domain tbh)


# How to use 
Download the .3dsx or .cia from the latest release and put it in your 3ds folder on your SD Card, then launch the app from the Homebrew Launcher.

Press A to change your username and B to send a message

There is profanity censoring.


## How to Host Your Own hbchat Server
First things first, you're going to need Node.JS, go ahead and install it, then come back

There are a few risks in hosting a server:
1. If you are hosting the server on YOUR network (not a VPS) and you share your router's IP with the public, you could be DDoSed (would make your router unusable and can lead to other problems.)
2. Your computer could be exposed to large amounts of stress (this is not common at all depending on how many people are using your server)
3. Bandwith (Though hbchat should be decent at relatively low bandwith, it's still a possibility that it could use an absolute boatload of it.)

With that out of the way, here is how to host a server.

Step 1: Downloading the Code

All you have to do is clone or download this repository. Pretty simple.

Step 2: Running the Code
Go into the server folder, then open a terminal and run the following:

`node server.js`

Boom! You're running a hbchat server!


## Notes for people running servers
Although there is a risk in sharing your public IP, I do think that if shared with a discord server or something, it'd be fine, though I still don't reccommend it.

I would reccomend just renting some cheap VPS if you really wanna host a server, some are as low as $5 per month or something like that lol.

Just don't buy a sketchy VPS and make sure it allows you basically full access as hbchat uses raw TCP packets which are blocked by some services (e.g. Render, anything with a free tier basically.)

