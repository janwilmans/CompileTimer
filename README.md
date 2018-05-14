# CompileTimer
Set of tests to benchmark the compile time of c++ constructs

This project is an attempt to understand what c++ construct take how much time to build (compile + link)
The tests are currently only done with VS2017/ msbuild (15.6 preview 7)

Results from  VS2017/ msbuild (15.6 preview 7):
```
10.000 empty runs: 191ns
default empty console project: 563ms
default + include "windows.h": 607ms 
default + instantiate 1000 std::vector<T>'s: 607ms
default + instantiate 10.000 std::vector<T>'s: 1064ms
default + instantiate 50.000 std::vector<T>'s: 8712ms
default + instantiate 100.000 std::vector<T>'s: 33264ms

total time: 223 seconds.
```

Results from  VS2017/ msbuild (15.8 preview 1.1):
```
10.000 empty runs: 1ns
default empty console project: 1333ms
default + include "windows.h": 1410ms 
default + instantiate 1000 std::vector<T>'s: 1502ms
default + instantiate 10.000 std::vector<T>'s: 4364ms
default + instantiate 50.000 std::vector<T>'s: 72s
default + instantiate 100.000 std::vector<T>'s: ?? 

total time: ??  too long I aborted the test.
```

Quite unexpectedly
1) compiling more vectors does not scale linearly. 
2) the recent 15.8 preview 1.1 is roughly a factor of 2 slower? (and even worse in 10k+ scenarios)

```
[==========] Running 7 tests from 7 test cases.
[----------] Global test environment set-up.
[----------] 1 test from BaselineEmptyTest
[ RUN      ] BaselineEmptyTest.BuildTimesTest
[ AVG TIME ] EMPTY_BASELINE: 191ns
[       OK ] BaselineEmptyTest.BuildTimesTest (3 ms)
[----------] 1 test from BaselineEmptyTest (3 ms total)

[----------] 1 test from BaselineSleep1msTest
[ RUN      ] BaselineSleep1msTest.BuildTimesTest
[ AVG TIME ] 20ms Baseline: 30.947ms
[       OK ] BaselineSleep1msTest.BuildTimesTest (312 ms)
[----------] 1 test from BaselineSleep1msTest (313 ms total)

[----------] 1 test from WindowsHeaderTest
[ RUN      ] WindowsHeaderTest.BuildTimesTest
[ AVG TIME ] 607.654ms
[       OK ] WindowsHeaderTest.BuildTimesTest (3053 ms)
[----------] 1 test from WindowsHeaderTest (3053 ms total)

[----------] 1 test from Vector1kTest
[ RUN      ] Vector1kTest.BuildTimesTest
[ AVG TIME ] 606.817ms
[       OK ] Vector1kTest.BuildTimesTest (3062 ms)
[----------] 1 test from Vector1kTest (3062 ms total)

[----------] 1 test from Vector10kTest
[ RUN      ] Vector10kTest.BuildTimesTest
[ AVG TIME ] 1035.09ms
[       OK ] Vector10kTest.BuildTimesTest (5323 ms)
[----------] 1 test from Vector10kTest (5323 ms total)

[----------] 1 test from Vector50kTest
[ RUN      ] Vector50kTest.BuildTimesTest
[ AVG TIME ] 8712.72ms
[       OK ] Vector50kTest.BuildTimesTest (44275 ms)
[----------] 1 test from Vector50kTest (44276 ms total)

[----------] 1 test from Vector100kTest
[ RUN      ] Vector100kTest.BuildTimesTest
[ AVG TIME ] 33264.4ms
[       OK ] Vector100kTest.BuildTimesTest (167727 ms)
[----------] 1 test from Vector100kTest (167727 ms total)

[----------] Global test environment tear-down
[==========] 7 tests from 7 test cases ran. (223762 ms total)
[  PASSED  ] 7 tests.
Press any key to continue . . .

```

```
[==========] Running 9 tests from 9 test cases.
[----------] Global test environment set-up.
[----------] 1 test from BaselineEmptyTest
[ RUN      ] BaselineEmptyTest.BuildTimesTest
[ AVG TIME ] EMPTY_BASELINE: 1ns
[       OK ] BaselineEmptyTest.BuildTimesTest (1 ms)
[----------] 1 test from BaselineEmptyTest (1 ms total)

[----------] 1 test from BaselineSleep1msTest
[ RUN      ] BaselineSleep1msTest.BuildTimesTest
[ AVG TIME ] 20ms Baseline: 20.449ms
[       OK ] BaselineSleep1msTest.BuildTimesTest (208 ms)
[----------] 1 test from BaselineSleep1msTest (208 ms total)

[----------] 1 test from EmptyProjectTest
[ RUN      ] EmptyProjectTest.BuildTimesTest
[ AVG TIME ] 1333.13ms
[       OK ] EmptyProjectTest.BuildTimesTest (6674 ms)
[----------] 1 test from EmptyProjectTest (6674 ms total)

[----------] 1 test from WindowsHeaderTest
[ RUN      ] WindowsHeaderTest.BuildTimesTest
[ AVG TIME ] 1410.95ms
[       OK ] WindowsHeaderTest.BuildTimesTest (7066 ms)
[----------] 1 test from WindowsHeaderTest (7067 ms total)

[----------] 1 test from Vector1kTest
[ RUN      ] Vector1kTest.BuildTimesTest
[ AVG TIME ] 1502.5ms
[       OK ] Vector1kTest.BuildTimesTest (7525 ms)
[----------] 1 test from Vector1kTest (7526 ms total)

[----------] 1 test from Vector10kTest
[ RUN      ] Vector10kTest.BuildTimesTest
[ AVG TIME ] 4364.34ms
[       OK ] Vector10kTest.BuildTimesTest (21855 ms)
[----------] 1 test from Vector10kTest (21856 ms total)

[----------] 1 test from Vector10kSameTest
[ RUN      ] Vector10kSameTest.BuildTimesTest
[ AVG TIME ] 4067.35ms
[       OK ] Vector10kSameTest.BuildTimesTest (20363 ms)
[----------] 1 test from Vector10kSameTest (20363 ms total)

[----------] 1 test from Vector50kTest
[ RUN      ] Vector50kTest.BuildTimesTest
[ AVG TIME ] 72024.6ms
[       OK ] Vector50kTest.BuildTimesTest (360211 ms)
[----------] 1 test from Vector50kTest (360211 ms total)

[----------] 1 test from Vector100kTest
[ RUN      ] Vector100kTest.BuildTimesTest
[ AVG TIME ] 273680ms
[       OK ] Vector100kTest.BuildTimesTest (1368639 ms)
[----------] 1 test from Vector100kTest (1368641 ms total)

[----------] Global test environment tear-down
[==========] 9 tests from 9 test cases ran. (1792552 ms total)
[  PASSED  ] 9 tests.
Press any key to continue . . .
```

