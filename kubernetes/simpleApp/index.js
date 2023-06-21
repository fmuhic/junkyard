const express = require('express')
const app = express()
const port = 8080
const serverId = process.env.SERVER_ID || "DEFAULT_SERVER"

app.get('/', (req, res) => {
    res.send(`Welcome from server ${serverId}`);
})

app.get('/error', (req, res) => {
    process.exit(1);
})

app.listen(port, () => {
    console.log(`App listening on port ${port}`);
})

