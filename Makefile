FLAG=-std=c++17 -O3 -g -pthread

build/main: src/main.cpp
	-mkdir build
	clang++ src/main.cpp -o build/main $(FLAG) $(INCLUDE)

run:
	make
	./build/main

clean:
	rm -rf build/*
