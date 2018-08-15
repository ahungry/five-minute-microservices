#!/bin/bash

# -*- mode: shell -*-

set -x

sbcl --eval '(push #P"'$(pwd)'" ql:*local-project-directories*)' \
     --eval '(ql:quickload :5m-ms)' \
     --eval '(5m-ms:main)'
