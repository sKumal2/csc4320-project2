// checker.cpp - independent trace checker (spec Section 6).
//
// Usage (planned):  ./bin/checker <config file> <events.csv>
//
// Independent: reads ONLY the saved config and events.csv. Does not include
// or call anything from src/.
// Valid trace   -> print PASS + totals, exit 0.
// Invalid trace -> print FAIL + event number (or EOF) + reason, exit nonzero.

#include <iostream>
#include <string>

struct CheckResult {
	bool        ok = true;
	std::string where;   // event seq number, or "EOF"
	std::string reason;
};

// TODO: own config parser + every check from Section 6.
CheckResult check_trace([[maybe_unused]] const std::string& config_path,
                        [[maybe_unused]] const std::string& events_path) {
	return CheckResult{false, "EOF", "checker not implemented yet"};
}

int main(int argc, char* argv[]) {
	if (argc != 3) {
		std::cerr << "usage: " << argv[0] << " <config file> <events.csv>\n";
		return 2;
	}

	CheckResult r = check_trace(argv[1], argv[2]);
	if (r.ok) {
		std::cout << "PASS\n";  // TODO: print totals
		return 0;
	}
	std::cout << "FAIL at " << r.where << ": " << r.reason << "\n";
	return 1;
}
