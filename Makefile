CXX := g++
CXXFLAGS := -std=c++11 -c -g
LD := g++
LDFLAGS := 

EXE := tbasic
OBJ = obj/editor.o obj/main.o obj/utilities.o obj/tokenizer.o
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

obj/editor.o: src/editor.cc src/editor.h
	$(CXX) $(CXXFLAGS) $< -o $@

obj/main.o: src/main.cc
	$(CXX) $(CXXFLAGS) $< -o $@

obj/utilities.o: src/utilities.cc src/utilities.h
	$(CXX) $(CXXFLAGS) $< -o $@

obj/tokenizer.o: src/tokenizer.cc src/tokenizer.h
	$(CXX) $(CXXFLAGS) $< -o $@


# Building tests and stuff
obj/tokenizer01.o: tests/tokenizer01.cc src/tokenizer.h
	$(CXX) $(CXXFLAGS) $< -Isrc/ -o $@

test_tokenizer: obj/tokenizer01.o obj/tokenizer.o
	$(LD) $(LDFLAGS) $^ -o $@
