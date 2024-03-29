const express = require('express');
const fs = require('fs');
const bodyParser = require('body-parser')
const axios = require('axios');

const app = express();
app.use(bodyParser.json());
const port = 8080;

app.get('/', (req, res) => {
    res.send(`Welcome to user api`);
})

app.get('/health', (req, res) => {
    res.sendStatus(200);
})

app.get('/error', (req, res) => {
    process.exit(1);
})

app.post('/signup', async (req, res) => {
    const email = req.body.email;
    const password = req.body.password;

    if (!email || email.trim().length == 0) {
        return res.status(422).json({ message: `Invalid email: ${email}` });
    }

    if (!password || password.trim().length == 0) {
        return res.status(422).json({ message: `Invalid password: ${password}` });
    }

    try {
        // Most common way to load balance is to use builtin kubernets core dns resolver
        // "default" is a kubernets namespace
        // await axios.get(`http://auth-api-service.default/token/create/` + password);
        
        // This env is automatically injected by kubernetes: AUTH_SERVICE_SERVICE_HOST
        await axios.get(`http://${process.env.AUTH_API_SERVICE_SERVICE_HOST}/token/create/` + password);
        res.status(201).json({ message: 'User created!' });
    } catch (err) {
        console.log(err);
        res.status(500).json({ message: 'Unable to create new user.' });
    }
})

app.post('/login', async (req, res) => {
    const email = req.body.email;
    const password = req.body.password;

    if (!email || email.trim().length == 0) {
        return res.status(422).json({ message: `Invalid email: ${email}` });
    }

    if (!password || password.trim().length == 0) {
        return res.status(422).json({ message: `Invalid password: ${password}` });
    }

    try {
        const authResponse = await axios.get(`http://${process.env.AUTH_API_SERVICE_SERVICE_HOST}/token/get/` + password);
        res.status(201).json({
            username: email,
            token: authResponse.data.token
        });
    } catch (err) {
        console.log(err);
        res.status(500).json({ message: 'Unable to verify user.' });
    }
})

app.listen(port);
