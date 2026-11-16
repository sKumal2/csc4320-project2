// bounded_queue.hpp - bounded FIFO queue shared by producers and consumers
// (spec Sections 4-5). One class, two synchronization modes (cv / sem).
#pragma once

#include <string>
#include <vector>

#include "config.hpp"

struct Record {
	bool is_stop = false;  // true for STOP1..STOPC
	int  id      = 0;      // real job ID, or STOP number (1..C)
};

// One row of events.csv: seq,actor,event,job_id,occupancy,result
struct Event {
	long        seq = 0;
	std::string actor;      // P0.., C0.., MAIN
	std::string event;      // ENQ, DEQ, DONE, STOP_ENQ, STOP_GET
	std::string job_id;     // "5" or "STOP2"
	int         occupancy = 0;
	std::string result;     // "-" or the computed integer
};

struct Summary {
	int       jobs          = 0;
	int       produced      = 0;
	int       dequeued      = 0;
	int       completed     = 0;
	long long result_sum    = 0;
	int       max_occupancy = 0;
	long long elapsed_ms    = 0;
};

class BoundedQueue {
public:
	BoundedQueue(Mode mode, int capacity, int jobs);

	// Insert at the tail, blocking while the queue is full. Logs ENQ/STOP_ENQ.
	void put(const Record& rec, const std::string& actor);

	// Remove the head record, blocking while empty. Logs DEQ/STOP_GET.
	Record get(const std::string& actor);

	// Log DONE for a finished job and update the stats.
	void record_done(const std::string& actor, int job_id, long long result);

	// Call only after all threads are joined.
	const std::vector<Event>& events() const { return log_; }
	Summary& summary() { return summary_; }

private:
	[[maybe_unused]] Mode mode_;
	[[maybe_unused]] int  capacity_;

	// TODO: buffer storage + head / tail / count
	// TODO: the queue mutex
	// TODO: cv mode members
	// TODO: sem mode members

	std::vector<Event> log_;
	Summary            summary_;
};
