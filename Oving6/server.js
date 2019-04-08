const http = require('http');
const crypto = require('crypto');
const static = require('node-static');
const file = new static.Server('./');
const server = http.createServer((req, res) => {
    req.addListener('end', () => file.serve(req, res)).resume();
});

const port = 3210;
server.listen(port, () => console.log(`Server running at http://localhost:${port}`));

server.on('upgrade', function (req, socket) {
    if (req.headers['upgrade'] !== 'websocket') {
        socket.end('HTTP/1.1 400 Bad Request');
        return;
    }

    const acceptKey = req.headers['sec-websocket-key'];
     const hash = generateAcceptValue(acceptKey);
    const responseHeaders = [ 'HTTP/1.1 101 Web Socket Protocol Handshake', 'Upgrade: WebSocket', 'Connection: Upgrade', `Sec-WebSocket-Accept: ${hash}` ];
    console.log(responseHeaders);
    const open = 'open';
     socket.write(responseHeaders.join('\r\n') + '\r\n\r\n');
    // socket.write(open);
    const protocol = req.headers['sec-websocket-protocol'];

    const protocols = !protocol ? [] : protocol.split(',').map(s => s.trim());

    if (protocols.includes('json')) {
        responseHeaders.push(`Sec-WebSocket-Protocol: json`);
    }

});
function generateAcceptValue (acceptKey) {
    return crypto.createHash('sha1')
        .update(acceptKey + "258EAFA5-E914-47DA-95CA-C5AB0DC85B11", 'binary')
        .digest('base64');
}