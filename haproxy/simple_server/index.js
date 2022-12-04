const express = require('express')
const app = express()
const port = 8080
const serverId = process.env.SERVER_ID || "DEFAULT_SERVER"

app.get('/', (req, res) => {
    res.send(`Welcome from server ${serverId}`)
})

app.get('/app1', (req, res) => {
    res.send(`Welcome from first application from server ${serverId}`)
})

app.get('/app2', (req, res) => {
    res.send(`Welcome from second application from server ${serverId}`)
})

app.get('/admin', (req, res) => {
    res.send(`Welcome from restricted admin area from server ${serverId}`)
})

app.listen(port, () => {
    console.log(`App listening on port ${port}`)
})
