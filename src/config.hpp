// config.hpp - queue program configuration (spec Section 1).
#pragma once

#include <string>

enum class Mode { CV, SEM };

struct Config {
	int seed      = 7;  // 0-9999
	int jobs      = 6;  // 0-10000
	int producers = 2;  // 1-8
	int consumers = 2;  // 1-8
	int capacity  = 2;  // 1-64
	int delay_ms  = 0;  // 0-10
};

// Reads the six key=value lines from `path`.
// Throws std::runtime_error with a clear message on any invalid input.
Config load_config(const std::string& path);

// Reads "--mode cv|sem" from the command line. Throws std::invalid_argument.
Mode parse_mode(int argc, char* argv[]);
