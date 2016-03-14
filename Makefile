CXX := g++
CXXFLAGS := -std=c++11 -c -g
LD := g++
LDFLAGS := 

EXE := tbasic
OBJ = obj/editor.o obj/main.o obj/utilities.o obj/tokenizer.o obj/parser.o
TESTS := test_tokenizer

.PHONY: all clean tests

all: $(EXE)

clean:
	rm -f $(OBJ)
	rm -f $(EXE)
	rm -f $(TESTS)

tests: $(TESTS)

$(EXE): obj/ $(OBJ)
	$(LD) $(LDFLAGS) $(OBJ) -o $@

obj/:
	mkdir $@



# Source files and stuff

obj/%.o: src/%.cc src/%.h
	$(CXX) $(CXXFLAGS) $< -o $@

obj/%.o: src/%.cc
	$(CXX) $(CXXFLAGS) $< -o $@

# Building tests and stuff
obj/tokenizer01.o: tests/tokenizer01.cc src/tokenizer.h
	$(CXX) $(CXXFLAGS) $< -Isrc/ -o $@

test_tokenizer: obj/tokenizer01.o obj/tokenizer.o
	$(LD) $(LDFLAGS) $^ -o $@
