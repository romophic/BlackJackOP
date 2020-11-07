SRCPATH=src/
BUILDPATH=build/
CC=clang++
FLAG=-std=c++17 -O3 -g -pthread
INCLUDE=-I /usr/local/include
MAIN=$(SRCPATH)main.cpp
EXE=$(BUILDPATH)main

$(EXE): $(MAIN) $(OBJ)
	-mkdir build
	$(CC) $(FLAG) $(INCLUDE) $(MAIN) -o $(EXE)

run:
	make
	$(EXE)

clean:
	rm -rf $(BUILDPATH)*
