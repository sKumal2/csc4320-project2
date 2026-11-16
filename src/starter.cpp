// Multithreaded application starter code.
// Uses the public configuration from the revised Project 2 spec (Section 1).
// NOTE: the final queue program must READ these values from a config file;
// they are hard-coded here only as a starting point.

#include <iostream>
#include <mutex>
#include <string>
#include <system_error>
#include <thread>
#include <vector>

// Public configuration (Section 1). Allowed ranges are in the comments.
struct Config {
	int seed      = 7;  // 0-9999
	int jobs      = 6;  // 0-10000
	int producers = 2;  // 1-8
	int consumers = 2;  // 1-8
	int capacity  = 2;  // 1-64
	int delay_ms  = 0;  // 0-10
};

std::mutex print_mutex;  // keeps lines from different threads from mixing

void worker(const std::string& actor) {
	std::lock_guard<std::mutex> lock(print_mutex);
	std::cout << "Thread " << actor << " is running.\n";
}

int main() {
	const Config cfg;

	std::cout << "seed=" << cfg.seed << " jobs=" << cfg.jobs
	          << " producers=" << cfg.producers << " consumers=" << cfg.consumers
	          << " capacity=" << cfg.capacity << " delay_ms=" << cfg.delay_ms << "\n";

	std::vector<std::thread> threads;
	try {
		// Actor names follow the spec: P0..P(P-1) and C0..C(C-1).
		for (int c = 0; c < cfg.consumers; ++c)
			threads.emplace_back(worker, "C" + std::to_string(c));
		for (int p = 0; p < cfg.producers; ++p)
			threads.emplace_back(worker, "P" + std::to_string(p));
	} catch (const std::system_error& e) {
		std::cerr << "thread creation failed: " << e.what() << "\n";
		for (auto& t : threads) t.join();
		return 1;
	}

	for (auto& t : threads) t.join();

	std::cout << "All threads completed.\n";
	return 0;
}

