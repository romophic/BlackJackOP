SRCPATH=src/
BUILDPATH=build/
CC=clang++
FLAG=-std=c++17 -O3 -g -pthread
MAIN=$(SRCPATH)main.cpp
EXE=$(BUILDPATH)main

$(EXE): $(MAIN) $(OBJ)
	-mkdir build
	$(CC) $(FLAG) $(MAIN) -o $(EXE)

run:
	make
	$(EXE)

clean:
	rm -rf $(BUILDPATH)*
