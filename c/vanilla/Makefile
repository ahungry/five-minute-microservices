# -*- mode: makefile; -*-

CC?= gcc

CFLAGS = -Wall -c -std=gnu99 -I/usr/local/include
LDFLAGS = -L/usr/local/lib -Wl,-rpath=/usr/local/lib -pthread

EXE = bin/5m-ms

all: $(EXE)

$(EXE): main.o
	$(CC) $(LDFLAGS) $< -o $@

main.o: main.c
	$(CC) $(CFLAGS) $< -o $@

clean:
	-rm *.o
	-rm $(EXE)

start: all
	./bin/5m-ms 12003

docker-build:
	docker build -t 5m-ms-c-vanilla .

docker-run:
	docker run --rm -it -p 3005:12003 5m-ms-c-vanilla
