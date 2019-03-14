# Benchmarks

<!-- markdown-toc start - Don't edit this section. Run M-x markdown-toc-refresh-toc -->
**Table of Contents**

- [Benchmarks](#benchmarks)
- [v0.0.1](#v001)
    - [node](#node)
    - [common lisp](#common-lisp)
    - [C](#c)
    - [PHP](#php)
    - [Guile Scheme](#guile-scheme)
    - [Erlang](#erlang)
    - [Elixir](#elixir)
    - [Nginx FastCGIWrap (around a tiny C sample)](#nginx-fastcgiwrap-around-a-tiny-c-sample)
    - [Nginx libfcgi (around a tiny C sample)](#nginx-libfcgi-around-a-tiny-c-sample)

<!-- markdown-toc end -->


Take these with a grain of salt.

Other notes and findings:

Nodejs (express, native etc. - anything that uses the built in TCP)
runs into a socket expiration problem after a few siege cycles.
Apparently with too much concurrency, it never reclaims the used
sockets or something.

# v0.0.1

## node

```sh
make -C node/vanilla start

siege -r100 -c10 http://localhost:12002

Transactions:                   1000 hits
Availability:                 100.00 %
Elapsed time:                   0.21 secs
Data transferred:               0.01 MB
Response time:                  0.00 secs
Transaction rate:            4761.90 trans/sec
Throughput:                     0.03 MB/sec
Concurrency:                    9.57
Successful transactions:        1000
Failed transactions:               0
Longest transaction:            0.01
Shortest transaction:           0.00

siege -r100 -c100 http://localhost:12002

Transactions:                  10000 hits
Availability:                 100.00 %
Elapsed time:                   1.32 secs
Data transferred:               0.07 MB
Response time:                  0.01 secs
Transaction rate:            7575.76 trans/sec
Throughput:                     0.05 MB/sec
Concurrency:                   97.61
Successful transactions:       10000
Failed transactions:               0
Longest transaction:            0.02
Shortest transaction:           0.00

```

## common lisp

```sh
make -C common-lisp/vanilla start

siege -r100 -c10 http://localhost:12000

Transactions:                   1000 hits
Availability:                 100.00 %
Elapsed time:                   0.08 secs
Data transferred:               0.01 MB
Response time:                  0.00 secs
Transaction rate:           12500.00 trans/sec
Throughput:                     0.08 MB/sec
Concurrency:                    9.62
Successful transactions:        1000
Failed transactions:               0
Longest transaction:            0.01
Shortest transaction:           0.00

siege -r100 -c100 http://localhost:12000

Transactions:                  10000 hits
Availability:                 100.00 %
Elapsed time:                   0.80 secs
Data transferred:               0.07 MB
Response time:                  0.01 secs
Transaction rate:           12500.00 trans/sec
Throughput:                     0.08 MB/sec
Concurrency:                   94.22
Successful transactions:       10000
Failed transactions:               0
Longest transaction:            0.05
Shortest transaction:           0.00

```

## C

```sh
make -C c/vanilla start

siege -r100 -c10 http://localhost:12003

Transactions:                   1000 hits
Availability:                 100.00 %
Elapsed time:                   0.06 secs
Data transferred:               0.01 MB
Response time:                  0.00 secs
Transaction rate:           16666.67 trans/sec
Throughput:                     0.11 MB/sec
Concurrency:                    9.83
Successful transactions:        1000
Failed transactions:               0
Longest transaction:            0.01
Shortest transaction:           0.00

siege -r100 -c100 http://localhost:12003

Transactions:                  10000 hits
Availability:                 100.00 %
Elapsed time:                   2.36 secs
Data transferred:               0.07 MB
Response time:                  0.01 secs
Transaction rate:            4237.29 trans/sec
Throughput:                     0.03 MB/sec
Concurrency:                   54.30
Successful transactions:       10000
Failed transactions:               0
Longest transaction:            1.24
Shortest transaction:           0.00

```

## PHP

```sh
make -C php/vanilla start

siege -r100 -c10 http://127.0.0.1:12001

Transactions:                   1000 hits
Availability:                 100.00 %
Elapsed time:                   0.25 secs
Data transferred:               0.01 MB
Response time:                  0.00 secs
Transaction rate:            4000.00 trans/sec
Throughput:                     0.03 MB/sec
Concurrency:                    9.84
Successful transactions:        1000
Failed transactions:               0
Longest transaction:            0.01
Shortest transaction:           0.00

siege -r100 -c100 http://127.0.0.1:12001

Transactions:                  10000 hits
Availability:                 100.00 %
Elapsed time:                   2.41 secs
Data transferred:               0.07 MB
Response time:                  0.02 secs
Transaction rate:            4149.38 trans/sec
Throughput:                     0.03 MB/sec
Concurrency:                   97.87
Successful transactions:       10000
Failed transactions:               0
Longest transaction:            0.05
Shortest transaction:           0.00

```

## Guile Scheme

```sh
make -C scheme/vanilla start

siege -r100 -c10 http://127.0.0.1:8080

Transactions:                   1000 hits
Availability:                 100.00 %
Elapsed time:                   0.13 secs
Data transferred:               0.01 MB
Response time:                  0.00 secs
Transaction rate:            7692.31 trans/sec
Throughput:                     0.05 MB/sec
Concurrency:                    9.54
Successful transactions:        1000
Failed transactions:               0
Longest transaction:            0.01
Shortest transaction:           0.00

siege -r100 -c100 http://127.0.0.1:8080

Transactions:                  10000 hits
Availability:                 100.00 %
Elapsed time:                   1.33 secs
Data transferred:               0.07 MB
Response time:                  0.01 secs
Transaction rate:            7518.80 trans/sec
Throughput:                     0.05 MB/sec
Concurrency:                   98.69
Successful transactions:       10000
Failed transactions:               0
Longest transaction:            0.03
Shortest transaction:           0.00

```

## Erlang

Erlang numbers using their pre-built web server "inets" performed
around 3500 trans/sec for both 100/10 and 100/100.

```sh
make -C erlang/vanilla start

siege -r100 -c10 http://127.0.0.1:4040

Transactions:                   1000 hits
Availability:                 100.00 %
Elapsed time:                   1.07 secs
Data transferred:               0.01 MB
Response time:                  0.00 secs
Transaction rate:             934.58 trans/sec
Throughput:                     0.01 MB/sec
Concurrency:                    2.52
Successful transactions:        1000
Failed transactions:               0
Longest transaction:            1.02
Shortest transaction:           0.00

siege -r100 -c100 http://127.0.0.1:4040

Transactions:                  10000 hits
Availability:                 100.00 %
Elapsed time:                  27.34 secs
Data transferred:               0.07 MB
Response time:                  0.04 secs
Transaction rate:             365.76 trans/sec
Throughput:                     0.00 MB/sec
Concurrency:                   14.31
Successful transactions:       10000
Failed transactions:               0
Longest transaction:           27.29
Shortest transaction:           0.00

```

## Elixir

Using Phoenix framework (Cowboy) with Elixir benched using 100/100 at 4700/rps.
At 10/100 it was 4100/rps.

This leads me to believe the simple server implementation has some
glaring oversight contributing to slowness (likely a similar problem
exists on the Erlang based one).

```sh
make -C elixir/vanilla/kv start

siege -r100 -c10 http://127.0.0.1:4040

Transactions:                   1000 hits
Availability:                 100.00 %
Elapsed time:                   1.06 secs
Data transferred:               0.01 MB
Response time:                  0.00 secs
Transaction rate:             943.40 trans/sec
Throughput:                     0.01 MB/sec
Concurrency:                    2.86
Successful transactions:        1000
Failed transactions:               0
Longest transaction:            1.03
Shortest transaction:           0.00

siege -r100 -c100 http://127.0.0.1:4040

Transactions:                  10000 hits
Availability:                 100.00 %
Elapsed time:                  14.23 secs
Data transferred:               0.07 MB
Response time:                  0.03 secs
Transaction rate:             702.74 trans/sec
Throughput:                     0.00 MB/sec
Concurrency:                   21.28
Successful transactions:       10000
Failed transactions:               0
Longest transaction:           14.18
Shortest transaction:           0.00
```

## Nginx FastCGIWrap (around a tiny C sample)

```sh
siege -r100 -c10 http://localhost/a.cgi

Transactions:                   1000 hits
Availability:                 100.00 %
Elapsed time:                   0.69 secs
Data transferred:               0.00 MB
Response time:                  0.01 secs
Transaction rate:            1449.28 trans/sec
Throughput:                     0.00 MB/sec
Concurrency:                    9.80
Successful transactions:        1000
Failed transactions:               0
Longest transaction:            0.02
Shortest transaction:           0.00

siege -r100 -c100 http://localhost/a.cgi

Transactions:                  10000 hits
Availability:                 100.00 %
Elapsed time:                   6.96 secs
Data transferred:               0.00 MB
Response time:                  0.07 secs
Transaction rate:            1436.78 trans/sec
Throughput:                     0.00 MB/sec
Concurrency:                   99.41
Successful transactions:       10000
Failed transactions:               0
Longest transaction:            0.10
Shortest transaction:           0.03
```

## Nginx libfcgi (around a tiny C sample)

```sh
siege -r100 -c10 http://localhost/blub

Transactions:                   1000 hits
Availability:                 100.00 %
Elapsed time:                   0.09 secs
Data transferred:               0.01 MB
Response time:                  0.00 secs
Transaction rate:           11111.11 trans/sec
Throughput:                     0.07 MB/sec
Concurrency:                    9.11
Successful transactions:        1000
Failed transactions:               0
Longest transaction:            0.01
Shortest transaction:           0.00

siege -r100 -c100 http://localhost/blub

Transactions:                  10000 hits
Availability:                 100.00 %
Elapsed time:                   0.95 secs
Data transferred:               0.07 MB
Response time:                  0.01 secs
Transaction rate:           10526.32 trans/sec
Throughput:                     0.07 MB/sec
Concurrency:                   98.73
Successful transactions:       10000
Failed transactions:               0
Longest transaction:            0.05
Shortest transaction:           0.00
```

## J (https://jsoftware.com)

This has no concept of concurrency (in the language I suppose), so
this is going to have terrible performance (siege segfaults with 100
concurrent hits on this test).

```sh
siege -r100 -c10 http://localhost:12321

Transactions:                    999 hits
Availability:                  99.90 %
Elapsed time:                   1.07 secs
Data transferred:               0.01 MB
Response time:                  0.00 secs
Transaction rate:             933.64 trans/sec
Throughput:                     0.01 MB/sec
Concurrency:                    4.40
Successful transactions:         999
Failed transactions:               1
Longest transaction:            1.02
Shortest transaction:           0.00

siege -r10000 -c1 http://localhost:12321

Transactions:                   9999 hits
Availability:                  99.99 %
Elapsed time:                   1.94 secs
Data transferred:               0.07 MB
Response time:                  0.00 secs
Transaction rate:            5154.12 trans/sec
Throughput:                     0.03 MB/sec
Concurrency:                    0.84
Successful transactions:        9999
Failed transactions:               1
Longest transaction:            0.01
Shortest transaction:           0.00
```

## Clojure (Luminus framework via 'lein new luminus luminus-webserver'

```sh
siege -r100 -c10 http://localhost:3000

Transactions:                   1000 hits
Availability:                 100.00 %
Elapsed time:                   0.73 secs
Data transferred:               0.00 MB
Response time:                  0.01 secs
Transaction rate:            1369.86 trans/sec
Throughput:                     0.01 MB/sec
Concurrency:                    9.66
Successful transactions:        1000
Failed transactions:               0
Longest transaction:            0.03
Shortest transaction:           0.00

siege -r100 -c100 http://localhost:3000

Transactions:                  10000 hits
Availability:                 100.00 %
Elapsed time:                   3.86 secs
Data transferred:               0.05 MB
Response time:                  0.04 secs
Transaction rate:            2590.67 trans/sec
Throughput:                     0.01 MB/sec
Concurrency:                   95.94
Successful transactions:       10000
Failed transactions:               0
Longest transaction:            0.19
Shortest transaction:           0.00

siege -r1000 -c100 http://localhost:3000

Transactions:                 100000 hits
Availability:                 100.00 %
Elapsed time:                  25.61 secs
Data transferred:               0.48 MB
Response time:                  0.03 secs
Transaction rate:            3904.72 trans/sec
Throughput:                     0.02 MB/sec
Concurrency:                   98.00
Successful transactions:      100000
Failed transactions:               0
Longest transaction:            0.09
Shortest transaction:           0.00

```
