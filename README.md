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
