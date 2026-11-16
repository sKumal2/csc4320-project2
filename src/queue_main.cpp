// queue_main.cpp - producer/consumer roles, lifecycle, and output
// (spec Sections 2, 4 "Shutdown in both modes", and 5).
//
// Usage (planned):  ./bin/queue --mode cv|sem  [config file]  [output folder]

#include <functional>
#include <iostream>
#include <string>
#include <system_error>
#include <thread>
#include <vector>

#include "bounded_queue.hpp"
#include "config.hpp"
#include "workload.hpp"

// ---------------------------------------------------------------------------
// Thread roles
// ---------------------------------------------------------------------------
// TODO: put each of this producer's job IDs (Section 2 ownership rule).
void producer([[maybe_unused]] BoundedQueue& queue, [[maybe_unused]] const Config& cfg,
              [[maybe_unused]] int p) {
}

// TODO: loop: get a record; on STOP, exit; otherwise process the job outside
//       the queue protection, then record DONE.
void consumer(BoundedQueue& queue, [[maybe_unused]] const Config& cfg, int c) {
	const std::string actor = "C" + std::to_string(c);
	[[maybe_unused]] Record rec = queue.get(actor);
}

// ---------------------------------------------------------------------------
// Output
// ---------------------------------------------------------------------------
// TODO: write the header line and every event, in order, to `path`.
void write_events_csv([[maybe_unused]] const std::string& path,
                      [[maybe_unused]] const std::vector<Event>& events) {
	// Header: seq,actor,event,job_id,occupancy,result
}

void print_summary(const Summary& s) {
	std::cout << "jobs="          << s.jobs          << "\n"
	          << "produced="      << s.produced      << "\n"
	          << "dequeued="      << s.dequeued      << "\n"
	          << "completed="     << s.completed     << "\n"
	          << "result_sum="    << s.result_sum    << "\n"
	          << "max_occupancy=" << s.max_occupancy << "\n"
	          << "elapsed_ms="    << s.elapsed_ms    << "\n";
}

// ---------------------------------------------------------------------------
// main: lifecycle
// ---------------------------------------------------------------------------
int main(int argc, char* argv[]) {
	Mode   mode;
	Config cfg;
	try {
		mode = parse_mode(argc, argv);
		cfg  = load_config("config/public.txt");  // TODO: take the path from argv
	} catch (const std::exception& e) {
		std::cerr << "error: " << e.what() << "\n";
		return 1;
	}

	BoundedQueue queue(mode, cfg.capacity, cfg.jobs);

	// TODO: start the elapsed-time clock here (before any worker starts).

	std::vector<std::thread> consumers;
	std::vector<std::thread> producers;
	try {
		for (int c = 0; c < cfg.consumers; ++c)
			consumers.emplace_back(consumer, std::ref(queue), std::cref(cfg), c);
		for (int p = 0; p < cfg.producers; ++p)
			producers.emplace_back(producer, std::ref(queue), std::cref(cfg), p);
	} catch (const std::system_error& e) {
		std::cerr << "thread creation failed: " << e.what() << "\n";
		// TODO: decide how to shut down threads that did start.
		for (auto& t : producers) t.join();
		for (auto& t : consumers) t.join();
		return 1;
	}

	for (auto& t : producers) t.join();

	// TODO: MAIN inserts STOP1..STOPC here.

	for (auto& t : consumers) t.join();

	// TODO: stop the clock and store elapsed_ms in the summary.

	write_events_csv("events.csv", queue.events());  // TODO: output folder option
	print_summary(queue.summary());
	return 0;
}
