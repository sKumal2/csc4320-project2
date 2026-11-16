// workload.hpp - job workload formulas (spec Section 2).
#pragma once

#include "config.hpp"

// result = payload * units + j
long long compute_result(int job_id, int seed);

// How long a consumer sleeps while processing a job (units * delay_ms).
int job_delay_ms(int job_id, const Config& cfg);
