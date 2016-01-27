CPP_FLAGS = -O2 -Wall -std=c++11
DEBUG_FLAGS += -g
PROG = markov
SRC = main.cpp markov_chain.cpp
INC = markov_chain.h

.PHONY: all
all: $(PROG)

.PHONY: debug
debug:
	g++-4.9 $(CPP_FLAGS) $(DEBUG_FLAGS) $(SRC) -o $(PROG)

.PHONY: clean
clean:
	rm $(PROG)

$(PROG): $(SRC) $(INC)
	g++-4.9 $(CPP_FLAGS) $(SRC) -o $(PROG)
