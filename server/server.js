const net = require('net');
const { Profanity } = require('@2toad/profanity');

const clients = [];
const bannedIPs = new Set(); // IPs go here
const profanity = new Profanity({ wholeWord: false });

const server = net.createServer((socket) => {
    const clientIp = socket.remoteAddress;

    if (bannedIPs.has(clientIp)) {
        socket.end('You are banned.\n');
        return;
    }

    console.log('Client connected:', clientIp);
    clients.push(socket);

    socket.on('data', (data) => {
        const msg = profanity.censor(data.toString());
        console.log('Received:', msg);
        clients.forEach((client) => {
            if (!client.destroyed) {
                try {
                    client.write(msg);
                } catch (err) {
                    console.warn('Write failed:', err.message);
                }
            }
        });
    });

    socket.on('end', () => {
        const index = clients.indexOf(socket);
        if (index !== -1) {
            clients.splice(index, 1);
        }
    });

    socket.on('error', (err) => {
        console.warn('Client connection error:', err.message);
        const index = clients.indexOf(socket);
        if (index !== -1) {
            clients.splice(index, 1);
        }
    });
});

server.listen(3071, '0.0.0.0', () => {
    console.log('Running hbchat server v0.0.1 on port 3071.');
});