FLAG=-std=c++17 -O3 -g -pthread
INCLUDE=-I /usr/local/include

build/main: src/main.cpp
	clang++ src/main.cpp -o build/main $(FLAG) $(INCLUDE)

clean:
	rm -rf build/*
