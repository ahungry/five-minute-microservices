# Benchmarks

<!-- markdown-toc start - Don't edit this section. Run M-x markdown-toc-refresh-toc -->
**Table of Contents**

- [Benchmarks](#benchmarks)
- [v0.0.1](#v001)
    - [node](#node)
    - [common lisp](#common-lisp)
    - [C](#c)
    - [PHP](#php)

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
```

## common lisp

```sh
make -C common-lisp/vanilla start

siege -r100 -c10 http://localhost:12000

Transactions:                   1000 hits
Availability:                 100.00 %
Elapsed time:                   0.22 secs
Data transferred:               0.01 MB
Response time:                  0.00 secs
Transaction rate:            4545.45 trans/sec
Throughput:                     0.03 MB/sec
Concurrency:                    9.68
Successful transactions:        1000
Failed transactions:               0
Longest transaction:            0.01
Shortest transaction:           0.00
```

## C

```sh
make -C c/vanilla start

siege -r100 -c10 http://localhost:12003

Transactions:                   1000 hits
Availability:                 100.00 %
Elapsed time:                   0.07 secs
Data transferred:               0.01 MB
Response time:                  0.00 secs
Transaction rate:           14285.71 trans/sec
Throughput:                     0.10 MB/sec
Concurrency:                    9.43
Successful transactions:        1000
Failed transactions:               0
Longest transaction:            0.01
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
```
