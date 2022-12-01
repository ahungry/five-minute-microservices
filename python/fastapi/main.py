# https://fastapi.tiangolo.com/
from fastapi import FastAPI

app = FastAPI()

@app.get("/")
async def read_root():
    return {"Hello": "World"}

# RAM Usage
#   valgrind uvicorn main:app
#      in use at exit: 2,140,576 bytes in 1,986 blocks

# Performance
#   siege -r1000 -c10 http://127.0.0.1:8000 -- 2044.99 trans/sec

# 848x more ram usage, 1/3rd as fast
