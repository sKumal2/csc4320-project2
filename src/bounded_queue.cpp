// bounded_queue.cpp - BoundedQueue implementation for cv and sem modes.
#include "bounded_queue.hpp"

BoundedQueue::BoundedQueue(Mode mode, int capacity, int jobs)
	: mode_(mode), capacity_(capacity) {
	summary_.jobs = jobs;
	// TODO: set up the buffer and the synchronization members for mode_.
}

// TODO: separate logic per mode_. Log the event while protected.
void BoundedQueue::put([[maybe_unused]] const Record& rec,
                       [[maybe_unused]] const std::string& actor) {
}

// TODO: separate logic per mode_. Log the event while protected.
//       (Stub returns a STOP so consumers exit and the program ends.)
Record BoundedQueue::get([[maybe_unused]] const std::string& actor) {
	return Record{true, 0};
}

// TODO: log DONE and update the stats while protected.
void BoundedQueue::record_done([[maybe_unused]] const std::string& actor,
                               [[maybe_unused]] int job_id,
                               [[maybe_unused]] long long result) {
}
