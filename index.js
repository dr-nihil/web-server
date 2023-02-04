const path = require('path');
const express = require('express');
const url = require('url');
const CheckUserService = require('./services/users.service');
const app = express();

app.use(express.static(path.join(__dirname, 'public')))

app.get("/", (req, res) => {
    res.sendFile(`${__dirname}/public/main.html`);
});

app.get("/users", (req, res) => {
    var urlParsed = url.parse(req.url, true);
    var checkUserService = new CheckUserService();

    if (urlParsed.query.username) {
        var username = urlParsed.query.username;
        if (checkUserService.check(username)) {
            res.sendFile(`${__dirname}/public/result_success.html`);
        } else {
            res.sendFile(`${__dirname}/public/result_fail.html`);
        }
    }
});

app.listen(8080, () => {
    console.log('Application listening on port 8080');
});
