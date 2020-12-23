FLAG=-std=c++17 -O3 -g -pthread
INCLUDE=-I /usr/local/include

build/main: src/main.cpp
	-make build
	clang++ src/main.cpp -o build/main $(FLAG) $(INCLUDE)

run:
	make
	./build/main

clean:
	rm -rf build/*
