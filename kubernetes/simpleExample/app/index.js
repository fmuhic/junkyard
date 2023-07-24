const express = require('express');
const fs = require('fs');
const bodyParser = require('body-parser')

const app = express();
app.use(bodyParser.json());

const port = 8080;
const serverId = process.env.SERVER_ID || "DEFAULT_SERVER";
const contentFile = process.env.CONTENT_FILE

app.get('/', (req, res) => {
    res.send(`Welcome from server ${serverId}`);
})

app.get('/health', (req, res) => {
    res.sendStatus(200);
})

app.get('/error', (req, res) => {
    process.exit(1);
})

app.get('/content', (req, res) => {
    try {
        const content = fs.readFileSync(contentFile, 'utf-8');
        res.json({
            lines:content.split(/\r?\n/).filter(l => l != "") 
        });
    } catch (err) {
        res.json({ lines: [] });
    }
})

app.post('/content', (req, res) => {
    try {
        const line = req.body.line + "\n";
        fs.writeFileSync(contentFile, line, { flag: 'a+' });
        res.sendStatus(201);
    } catch (err) {
        res.sendStatus(500);
    }
})


app.listen(port, () => {
    console.log(`App listening on port ${port}`);
})

