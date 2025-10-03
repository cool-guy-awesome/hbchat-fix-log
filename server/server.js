const net = require('net');

const { Profanity } = require('@2toad/profanity');

const clients = [];
const profanity = new Profanity({ wholeWord: false });

const server = net.createServer((socket) => {
    console.log('Client connected');
    
    // Add client to list
    clients.push(socket);

    socket.on('data', (data) => {
        console.log('Received:', profanity.censor(data.toString()));
        
        // Send to all connected clients
        clients.forEach((client) => {
            client.write(profanity.censor(data.toString()));
        });
    });

    // Remove client on disconnect
    socket.on('end', () => {
        const index = clients.indexOf(socket);
        if (index !== -1) {
            clients.splice(index, 1);
        }
    });
});

server.listen(3071, '0.0.0.0', () => {
    console.log('Running hbchat server v0.0.1 on port 3071.');
});