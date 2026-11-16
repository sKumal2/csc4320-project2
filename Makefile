# Build settings: C++20 is REQUIRED (std::counting_semaphore, std::barrier, etc.)
CXX      ?= g++
CXXFLAGS := -std=c++20 -Wall -Wextra -pedantic -pthread -O2
BIN      := bin

QUEUE_SRCS := src/queue_main.cpp src/bounded_queue.cpp src/config.cpp src/workload.cpp
QUEUE_HDRS := src/bounded_queue.hpp src/config.hpp src/workload.hpp

.PHONY: all queue race checker envtest smoketest clean

# Build the three assessed programs.
all: queue race checker

queue:   $(BIN)/queue
race:    $(BIN)/race
checker: $(BIN)/checker

$(BIN)/queue: $(QUEUE_SRCS) $(QUEUE_HDRS) | $(BIN)
	$(CXX) $(CXXFLAGS) $(QUEUE_SRCS) -o $@

$(BIN)/race: src/race.cpp | $(BIN)
	$(CXX) $(CXXFLAGS) $< -o $@

$(BIN)/checker: checker/checker.cpp | $(BIN)
	$(CXX) $(CXXFLAGS) $< -o $@

# Setup / Day 7 programs.
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
