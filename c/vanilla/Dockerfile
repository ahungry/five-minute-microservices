# -*- mode: dockerfile -*-
FROM alpine:3.10.1

RUN apk add --update gcc make libc-dev

COPY . /app

WORKDIR /app

RUN make all

ENTRYPOINT ./bin/5m-ms 12003
