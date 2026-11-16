// config.cpp - configuration loading and mode selection.
#include "config.hpp"

#include <stdexcept>

// TODO: read the six key=value lines from `path`.
//       - ignore blank lines and lines starting with #
//       - reject missing, unknown, duplicate, non-integer, out-of-range values
//       - this must finish BEFORE any thread starts
//       For now this returns the public values.
Config load_config([[maybe_unused]] const std::string& path) {
	return Config{};
}

Mode parse_mode(int argc, char* argv[]) {
	for (int i = 1; i + 1 < argc; ++i) {
		std::string arg = argv[i];
		if (arg == "--mode") {
			std::string value = argv[i + 1];
			if (value == "cv") return Mode::CV;
			if (value == "sem") return Mode::SEM;
			throw std::invalid_argument("mode must be cv or sem");
		}
	}
	throw std::invalid_argument("missing --mode cv|sem");
}
