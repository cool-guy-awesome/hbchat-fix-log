const net = require('net');

const { Profanity } = require('@2toad/profanity');

const clients = [];
const profanity = new Profanity({ wholeWord: false });

const server = net.createServer((socket) => {
    console.log('Client connected');
    clients.push(socket);

    socket.on('data', (data) => {
        const jsonDat = profanity.censor(data.toString());
        console.log(`Received: ${jsonDat}`);
        clients.forEach((client) => {
            let data;
            try {
                data = JSON.parse(jsonDat);
            } catch (error) {
                console.error(`Error! ${error}`);
                return;
            }
            client.write(profanity.censor(`<${data.user.substring(0, 10)}> ${data.message.substring(0, 64)}`));
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

server.listen(3071, '127.0.0.1', () => {
    console.log('Running hbchat server v0.0.1 on port 3071.');
});