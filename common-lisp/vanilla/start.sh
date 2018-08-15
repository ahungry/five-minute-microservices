#!/bin/bash

# -*- mode: shell -*-

# TODO: Don't hardcode pwd

sbcl --eval '(push #P"~/src/five-minute-microservices/common-lisp/vanilla" ql:*local-project-directories*)' \
     --eval '(ql:quickload :5m-ms)' \
     --eval '(5m-ms:main)'
