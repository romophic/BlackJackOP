SRCPATH=src/
BUILDPATH=build/
CC=clang++
FLAG=-std=c++17 -O3
MAIN=$(SRCPATH)main.cpp
EXE=$(BUILDPATH)main

$(EXE): $(MAIN) $(OBJ)
	-mkdir build
	$(CC) $(FLAG) $(MAIN) -o $(EXE)

run:
	$(EXE)

clean:
	rm -rf $(BUILDPATH)*
