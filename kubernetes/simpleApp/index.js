const express = require('express');
const fs = require('fs');
const bodyParser = require('body-parser')

const app = express();
app.use(bodyParser.json());

const port = 8080;
const serverId = process.env.SERVER_ID || "DEFAULT_SERVER";

app.get('/', (req, res) => {
    res.send(`Welcome from server ${serverId}`);
})

app.get('/error', (req, res) => {
    process.exit(1);
})

app.get('/content', (req, res) => {
    let lines = []; 
    try {
        const content = fs.readFileSync('/data/file.txt', 'utf-8');
        lines = content.split(/\r?\n/).filter(l => l != "")
    } catch (err) {
        console.error(err);
    }

    res.json({
        lines: lines
    })
})

app.post('/content', (req, res) => {
    try {
        const line = req.body.line + "\n";
        fs.writeFileSync('/data/file.txt', line, { flag: 'a+' });
        res.sendStatus(201);
    } catch (err) {
        console.error(err);
        res.sendStatus(500);
    }
})


app.listen(port, () => {
    console.log(`App listening on port ${port}`);
})

