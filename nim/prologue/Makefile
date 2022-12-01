start: api.bin
	./api.bin

api.bin:
	nim c -d:release --gc:orc -o:api.bin api.nim

deps:
	nimble install prologue
