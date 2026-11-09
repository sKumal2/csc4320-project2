# Build settings: C++20 is REQUIRED (std::counting_semaphore, std::barrier, etc.)
CXX      ?= g++
CXXFLAGS := -std=c++20 -Wall -Wextra -pedantic -pthread -O2
BIN      := bin

.PHONY: all envtest smoketest clean

all: envtest

envtest: $(BIN)/EnvironmentTest
	./$(BIN)/EnvironmentTest

$(BIN)/EnvironmentTest: src/EnvironmentTest.cpp | $(BIN)
	$(CXX) $(CXXFLAGS) $< -o $@

smoketest: $(BIN)/SmokeTest
	./$(BIN)/SmokeTest

$(BIN)/SmokeTest: src/SmokeTest.cpp | $(BIN)
	$(CXX) $(CXXFLAGS) $< -o $@

$(BIN):
	mkdir -p $(BIN)

clean:
	rm -rf $(BIN)
