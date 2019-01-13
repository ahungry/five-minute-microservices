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

<!-- markdown-toc end -->


Take these with a grain of salt.

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

Transactions:                   8314 hits
Availability:                  88.94 %
Elapsed time:                   4.34 secs
Data transferred:               0.06 MB
Response time:                  0.02 secs
Transaction rate:            1915.67 trans/sec
Throughput:                     0.01 MB/sec
Concurrency:                   39.73
Successful transactions:        8314
Failed transactions:            1034
Longest transaction:            3.49
Shortest transaction:           0.00

```
