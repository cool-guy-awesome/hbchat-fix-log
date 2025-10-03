# hbchat
Chatting application for 3DS (and Wii coming soon!)

## Doesn't Work?
You need to make sure you're connecting to a server (There are currently none as of writing this)

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

