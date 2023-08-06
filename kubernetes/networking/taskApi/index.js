const express = require('express');
const fs = require('fs');
const bodyParser = require('body-parser')
const axios = require('axios');

const app = express();
app.use(bodyParser.json());
const port = 8080;

app.get('/', (req, res) => {
    res.send(`Welcome to task api`);
})

app.get('/health', (req, res) => {
    res.sendStatus(200);
})

app.get('/error', (req, res) => {
    process.exit(1);
})

app.get('/tasks', async (req, res) => {
    const token = req.get('Token')

    try {
        let verification = await axios.get('http://auth-api-service.default/token/verify/' + token);
        res.status(200).json({ tasks: ['Task 1', 'Task 2'] });
    } catch (err) {
        console.log(err);
        res.status(500).json({ message: 'Unable to verify user.' });
    }
})

app.listen(port);
