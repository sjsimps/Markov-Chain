CPP_FLAGS = -Wall -std=c++11
DEBUG_FLAGS += -g -O0
PROG = markov

SRC =  Markov_Utility/markov_chain_builder.cpp
SRC += Markov_Utility/csv_parser.cpp
SRC += Markov_Utility/main.cpp

INC =  Markov_Chain/markov_chain.h
INC += Markov_Utility/markov_chain_builder.h
INC += Markov_Utility/csv_parser.h

.PHONY: all
all: $(PROG)

.PHONY: debug
debug:
	g++-4.9 $(CPP_FLAGS) $(DEBUG_FLAGS) $(SRC) -o $(PROG)

.PHONY: clean
clean:
	rm $(PROG)

$(PROG): $(SRC) $(INC)
	g++-4.9 -O2 $(CPP_FLAGS) $(SRC) -o $(PROG)
