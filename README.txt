CSC4320/6320 Project 2 - Concurrent Job Processing
==================================================

Producers place jobs into a bounded FIFO queue and consumers remove and
process them. The queue is implemented twice: with a mutex and condition
variables (cv mode), and with semaphores and a mutex (sem mode).

Status: in progress. The file layout and build are in place; the
implementation is being written.


Environment
-----------
Operating system:  macOS 26.6.2 (Darwin 25.6.0, arm64)
Language:          C++20 (needed for std::counting_semaphore, std::barrier)
Compiler:          Apple clang version 21.0.0 (clang-2100.1.1.101)
                   Target: arm64-apple-darwin25.6.0
                   Thread model: posix
                   (from `clang++ --version`; on this machine g++ is an
                   alias for the same Apple clang)
Build flags:       -std=c++20 -Wall -Wextra -pedantic -pthread -O2


Assigned seed
-------------
7  (provisional: the default seed until iCollege gives my individual seed)


File layout
-----------
src/
  config.hpp / config.cpp        Config, Mode, load_config(), parse_mode()
  workload.hpp / workload.cpp    compute_result(), job_delay_ms()
  bounded_queue.hpp / .cpp       Record, Event, Summary, class BoundedQueue
                                 (put / get / record_done for cv and sem)
  queue_main.cpp                 producer(), consumer(), CSV output,
                                 summary, main() lifecycle
  race.cpp                       controlled race experiment and mutex repair
  EnvironmentTest.cpp            C++20 toolchain check
  SmokeTest.cpp                  Day 7 thread smoke test

checker/
  checker.cpp                    independent trace checker (reads only a
                                 config file and events.csv; does not use
                                 any code from src/)

config/       saved valid and invalid test configurations
traces/       raw traces by mode and test case (cv/, sem/)
evidence/     design, smoke test, race outputs, investigations
Makefile      build targets (see below)


Build
-----
  make all          build bin/queue, bin/race, and bin/checker
  make queue        build only the queue program
  make race         build only the race program
  make checker      build only the checker
  make envtest      build and run the C++20 environment check
  make smoketest    build and run the thread smoke test
  make clean        remove the bin/ directory

All executables are written to bin/. No prebuilt files are needed.


Run
---
Queue program (mode is chosen on the command line, not in the config file):
  ./bin/queue --mode cv
  ./bin/queue --mode sem

Race experiment:
  ./bin/race --mode forced      # lost update, final counter 1
  ./bin/race --mode repaired    # mutex repair, final counter 2

Checker:
  ./bin/checker <config file> <events.csv>
  Prints PASS with totals and exits 0 for a valid trace.
  Prints FAIL with an event number (or EOF) and a reason, and exits
  nonzero, for an invalid trace.


Known limitations
-----------------
- The config file path and output folder are not yet command-line options.
