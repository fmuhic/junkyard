const express = require('express');
const fs = require('fs');
const bodyParser = require('body-parser')

const app = express();
app.use(bodyParser.json());
const port = 80;

app.get('/', (req, res) => {
    res.send(`Welcome to user api`);
})

app.get('/health', (req, res) => {
    res.sendStatus(200);
})

app.get('/error', (req, res) => {
    process.exit(1);
})

app.get('/token/create/:password', async (req, res) => {
    const password = req.params.password;
    try {
        const token = password + '_sha256'
        return res.status(200).json({ token: token });
    } catch (err) {
        console.log(err);
        return res.status(500)
            .json({ message: 'Unable to create new user' });
    }
})

app.get('/token/get/:password', async (req, res) => {
    const password = req.params.password;
    try {
        const token = password + "_sha256"
        return res.status(200).json({ token: token });
    } catch (err) {
        console.log(err);
        return res.status(500)
            .json({ message: 'Unable to create new user' });
    }
})

app.listen(port);
