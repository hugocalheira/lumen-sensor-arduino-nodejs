const path = process.argv[2]
if (!path) {
    throw Error('A serial port path was expected to be sent via command line')
}

const express = require('express')
const app = express()

app.use(express.static(__dirname + '/../public'))
const http = require('http').Server(app)

const io = require('socket.io')(http)

app.get('/', (req, res) => res.sendFile('index.html'))

const {SerialPort, ReadlineParser} = require('serialport')
const port = new SerialPort(
    { 
        path,
        baudRate: 9600,
    }
)

const parser = port.pipe(new ReadlineParser({ delimiter: '\r\n' }))

port.on("open", () => console.log(`Reading port ${path}`))
parser.on("data", data => {
    try {
        const parsedData = JSON.parse(data)
        console.log(parsedData)
        io.emit('dadoArduino', parsedData)
    } catch (err) {
        console.log(err.message)
    }
})

io.on('connection', socket => {
    console.log('Um usuario está conectado:', socket.id)

    socket.on('disconnect', () => {
        console.log('user disconnected');
    });

    socket.on('light', (data) => {
        console.log(data.toString())
        port.write(data.toString())
    })
})

http.listen(3000, () => console.log('Server listening on port 3000'))
