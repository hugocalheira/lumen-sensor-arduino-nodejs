require('dotenv').config()
const { WS_IP, argv } = process.env
const path = argv[2]

const express = require('express')
const app = express()
let port;
const WebSocket = require('ws')
ws = new WebSocket(`ws://${WS_IP}:81`); 

app.use(express.static(__dirname + '/../public'))
const http = require('http').Server(app)

const io = require('socket.io')(http)

app.get('/', (req, res) => res.sendFile('index.html'))

if (path) {
    const {SerialPort, ReadlineParser} = require('serialport')
    port = new SerialPort(
        { 
            path,
            baudRate: 115200,
        }
    )
    const parser = port.pipe(new ReadlineParser({ delimiter: '\r\n' }))
    
    port.on('open', () => console.log(`Reading port ${path}`))
    parser.on('data', data => {
        try {
            const parsedData = JSON.parse(data)
            io.emit('JSON_DATA', parsedData)
        } catch (err) {
            console.log(data)
        }
    })
} else {
    ws.on('message', function message(data) {
        try {
            const parsedData = JSON.parse(data.toString('utf-8'))
            // console.log('>>', parsedData);
            io.emit('JSON_DATA', parsedData)
        } catch (err) {
            console.log('x', data.toString('utf-8'))
        }
    });
}


io.on('connection', socket => {
    console.log('New connection:', socket.id)

    socket.on('disconnect', () => {
        console.log(`Connection ${socket.id} closed`);
    });

    socket.on('LIGHT', data => {
        if (port?.write) {
            port.write(data.toString())
        } else {
            ws.send(data.toString())
        }
    })
})

http.listen(3000, () => console.log('Server listening on http://localhost:3000'))
