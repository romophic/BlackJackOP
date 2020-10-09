SRCPATH=src/
BUILDPATH=build/
CC=clang++
FLAG=-std=c++17 -O3
MAIN=$(SRCPATH)main.cpp
SRC=$(SRCPATH)deck.cpp
EXE=$(BUILDPATH)main
OBJ=$(BUILDPATH)deck

$(EXE): $(MAIN) $(OBJ)
	$(CC) $(FLAG) $(OBJ) $(MAIN) -o $(EXE)

$(OBJ): $(SRC)
	$(CC) $(FLAG) -c $(SRC) -o $(OBJ)

run:
	$(EXE)

clean:
	rm -rf $(BUILDPATH)*