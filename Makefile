# Makefile pour le projet Blockchain avec Automate Cellulaire

CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2
LDFLAGS = -lssl -lcrypto

# Dossier source
SRCDIR = src

# Fichiers sources
SOURCES = $(SRCDIR)/CellularAutomaton.cpp $(SRCDIR)/Block.cpp $(SRCDIR)/Blockchain.cpp
OBJECTS = CellularAutomaton.o Block.o Blockchain.o

# Exécutables
MAIN = main
TEST = test

.PHONY: all clean run_main run_test

all: $(MAIN) $(TEST)

$(MAIN): $(OBJECTS) main.o
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

$(TEST): $(OBJECTS) test.o
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

# Règles de compilation
CellularAutomaton.o: $(SRCDIR)/CellularAutomaton.cpp $(SRCDIR)/CellularAutomaton.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

Block.o: $(SRCDIR)/Block.cpp $(SRCDIR)/Block.h $(SRCDIR)/CellularAutomaton.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

Blockchain.o: $(SRCDIR)/Blockchain.cpp $(SRCDIR)/Blockchain.h $(SRCDIR)/Block.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

main.o: $(SRCDIR)/main.cpp $(SRCDIR)/Blockchain.h $(SRCDIR)/CellularAutomaton.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

test.o: $(SRCDIR)/test.cpp $(SRCDIR)/CellularAutomaton.h $(SRCDIR)/Block.h $(SRCDIR)/Blockchain.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

run_main: $(MAIN)
	./$(MAIN)

run_test: $(TEST)
	./$(TEST)

clean:
	rm -f $(OBJECTS) main.o test.o $(MAIN) $(TEST)