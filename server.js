const express = require('express');
const app = express();
const path = require('path');
const http = require('http');
const WebSocket = require('ws'); // Import the WebSocket library

// Serve static files from the 'public' directory
app.use(express.static('public'));

// Create an HTTP server
const server = http.createServer(app);

// Create a WebSocket server associated with the HTTP server
const wss = new WebSocket.Server({ server });

// Define a route to serve the HTML page
app.get('/', (req, res) => {
  res.sendFile(path.join(__dirname, 'public', 'index.html'));
});

// Handle WebSocket connections
wss.on('connection', (ws) => {
  console.log('WebSocket connected');

  // Handle messages received from the client
  ws.on('message', (message) => {
    console.log('Received WebSocket message:', message);
  });
});

// Handle POST requests to /data-receiver
app.post('/data-receiver', (req, res) => {
  let data = '';

  // Receive data
  req.on('data', chunk => {
    data += chunk;
  });

  // Process data when the request ends
  req.on('end', () => {
    console.log('Received data:', data);

    // Send a response (optional)
    res.writeHead(200, { 'Content-Type': 'text/plain' });
    res.end('Data received successfully');

    // Broadcast the received data to all WebSocket clients
    wss.clients.forEach(client => {
      if (client.readyState === WebSocket.OPEN) {
        client.send(data);
      }
    });
  });
});

const port = process.env.PORT || 3000;
server.listen(port, () => {
  console.log(`Server listening on port ${port}`);
});
