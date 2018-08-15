// port: 12002

const http = require('http')

console.log('Running on port 12002')

//create a server object:
http.createServer(function (req, res) {
  res.write('"0.0.1"') //write a response to the client
  res.end() //end the response
}).listen(12002) //the server object listens on port 8080
