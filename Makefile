CXX := g++
CXXFLAGS := -std=c++11 -c -g
LD := g++
LDFLAGS := 

EXE := tbasic
OBJ = obj/editor.o obj/main.o obj/utilities.o

.PHONY: all clean

all: $(EXE)

clean:
	rm -f $(OBJ) $(EXE)

$(EXE): obj/ $(OBJ)
	$(LD) $(LDFLAGS) $(OBJ) -o $@

obj/:
	mkdir $@



# Source files and stuff

obj/editor.o: src/editor.cc src/editor.h
	$(CXX) $(CXXFLAGS) $< -o $@

obj/main.o: src/main.cc
	$(CXX) $(CXXFLAGS) $< -o $@

obj/utilities.o: src/utilities.cc src/utilities.h
	$(CXX) $(CXXFLAGS) $< -o $@
