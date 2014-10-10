// HTTP Portion
// var http = require('http');
// var fs = require('fs');
// var httpServer = http.createServer(requestHandler);
// httpServer.listen(3000);

// Socket.io server
// var io = require('socket.io').listen(httpServer);

var playersActive = [];

// WebSocketServer
var WebSocketServer = require('ws').Server
  , wss = new WebSocketServer({port: 3000});

console.log("Listening on 3000");

wss.on('connection', function(ws) {

	console.log("New Connection!");

    ws.on('message', function(message) {
        console.log('From Arduino: %s', message);
        playersActive.push(message);
        // for(int i=0; i<playersActive.length; 
    });
});