// race.cpp - controlled race experiment and its mutex repair (spec Section 3).
//
// Usage (planned):  ./bin/race --mode forced|repaired
//
// Separate from the queue program: it does not use the config file or
// events.csv. Its numbered read/write trace is saved separately.

#include <iostream>
#include <string>

// TODO: two workers, shared atomic counter starting at 0, each does
//       read -> local add -> write. Force both reads before either write.
//       Expected final counter: 1. Print a numbered trace.
int run_forced() {
	return 0;
}

// TODO: same increment protected by one mutex. Expected final counter: 2.
int run_repaired() {
	return 0;
}

int main(int argc, char* argv[]) {
	std::string mode = (argc == 3 && std::string(argv[1]) == "--mode") ? argv[2] : "";

	if (mode == "forced") {
		std::cout << "final counter = " << run_forced() << "\n";
	} else if (mode == "repaired") {
		std::cout << "final counter = " << run_repaired() << "\n";
	} else {
		std::cerr << "usage: " << argv[0] << " --mode forced|repaired\n";
		return 1;
	}
	return 0;
}
