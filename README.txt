CSC4320/6320 Project 2
======================

Language
--------
C++20 (required for std::counting_semaphore, std::barrier, etc.)

Compiler / runtime
------------------
Apple clang version 21.0.0 (clang-2100.1.1.101)
Target: arm64-apple-darwin25.6.0
Thread model: posix
InstalledDir: /Library/Developer/CommandLineTools/usr/bin

(Obtained with: clang++ --version. On this macOS machine, g++ is an alias
for the same Apple clang.)

Build flags (from Makefile):
  -std=c++20 -Wall -Wextra -pedantic -pthread -O2

Assigned seed
-------------
7  (provisional: the default seed until iCollege gives my private seed)

Build and run
-------------
  make envtest    # build and run src/EnvironmentTest.cpp (checks C++20 support)
  make clean      # remove the bin/ directory
