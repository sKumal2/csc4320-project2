// workload.cpp - job workload formulas (spec Section 2).
#include "workload.hpp"

// TODO: payload, units, and result formulas from Section 2.
long long compute_result([[maybe_unused]] int job_id, [[maybe_unused]] int seed) {
	long long payload = (37LL * job_id + 11LL * seed) % 1000;
	int units = 1 + ((job_id + seed) % 5);

	long long result = payload * units + job_id;

	return result;
}

// TODO: units * delay_ms.
int job_delay_ms([[maybe_unused]] int job_id, [[maybe_unused]] const Config& cfg) {
	int units = 1 + ((job_id + cfg.seed) % 5);

	return units * cfg.delay_ms;
}
