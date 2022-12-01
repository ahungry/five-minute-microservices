# https://planety.github.io/prologue/
import prologue
import json

proc hello*(ctx: Context) {.async.} =
  resp($ %* {"Hello": "World"}) # $ is shorthand to stringify, %* shorthand to jsonify

let app = newApp()
app.addRoute("/", hello)
app.run()

# RAM Usage (after 10,000 requests from siege)
#   valgrind ./hw_app
#     in use at exit: 2,523 bytes in 9 blocks

# Performance
#   siege -r1000 -c10 http://127.0.0.1:8080 -- 9174.31 trans/sec
