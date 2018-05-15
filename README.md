# CompileTimer
Set of tests to benchmark the compile time of c++ constructs

This project is an attempt to understand what c++ construct take how much time to build (compile + link)
The tests are currently only done with VS2017/ msbuild (15.6 preview 7)

To repeat these results use this version:
https://github.com/janwilmans/CompileTimer/tree/82ec3a6233d12bfcc25dbff42bab90edc3dd856a

Results from VS2017/ msbuild (15.6 preview 7):
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

Results from VS2017/ msbuild (15.8 preview 1.1):
```
10.000 empty runs: 1ns
default empty console project: 1333ms
default + include "windows.h": 1410ms 
default + instantiate 1000 std::vector<T>'s: 1502ms
default + instantiate 10.000 std::vector<T>'s: 4364ms
default + instantiate 50.000 std::vector<T>'s: 72 seconds! 
default + instantiate 100.000 std::vector<T>'s: 273 seconds! 

total time: 1792 seconds!!? 
```

Quite unexpectedly
1) compiling more vectors does not scale linearly. 
2) the recent 15.8 preview 1.1 is roughly a factor of 2 slower? (and even worse in 10k+ scenarios)
3) a tracker.exe process sometimes stays alive after the test is finished. (keeping the gen/ directory locked and failing a re-run of the test)


 * Detailed results from VS2017/ msbuild (15.6 preview 7):
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

* Detailed results from VS2017/ msbuild (15.8 preview 1.1):

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

 * Detailed results from VS2017/ msbuild (15.3.3 professional):
 
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
[ AVG TIME ] 20ms Baseline: 19.921ms
[       OK ] BaselineSleep1msTest.BuildTimesTest (204 ms)
[----------] 1 test from BaselineSleep1msTest (204 ms total)

[----------] 1 test from EmptyProjectTest
[ RUN      ] EmptyProjectTest.BuildTimesTest
[ AVG TIME ] 1008.09ms
[       OK ] EmptyProjectTest.BuildTimesTest (5114 ms)
[----------] 1 test from EmptyProjectTest (5114 ms total)

[----------] 1 test from WindowsHeaderTest
[ RUN      ] WindowsHeaderTest.BuildTimesTest
[ AVG TIME ] 1086.44ms
[       OK ] WindowsHeaderTest.BuildTimesTest (5504 ms)
[----------] 1 test from WindowsHeaderTest (5504 ms total)

[----------] 1 test from Vector1kTest
[ RUN      ] Vector1kTest.BuildTimesTest
[ AVG TIME ] 1082.99ms
[       OK ] Vector1kTest.BuildTimesTest (5492 ms)
[----------] 1 test from Vector1kTest (5492 ms total)

[----------] 1 test from Vector10kTest
[ RUN      ] Vector10kTest.BuildTimesTest
[ AVG TIME ] 1586.81ms
[       OK ] Vector10kTest.BuildTimesTest (8037 ms)
[----------] 1 test from Vector10kTest (8039 ms total)

[----------] 1 test from Vector10kSameTest
[ RUN      ] Vector10kSameTest.BuildTimesTest
[ AVG TIME ] 1598.39ms
[       OK ] Vector10kSameTest.BuildTimesTest (8079 ms)
[----------] 1 test from Vector10kSameTest (8081 ms total)

[----------] 1 test from Vector50kTest
[ RUN      ] Vector50kTest.BuildTimesTest
[ AVG TIME ] 10467.9ms
[       OK ] Vector50kTest.BuildTimesTest (52490 ms)
[----------] 1 test from Vector50kTest (52491 ms total)

[----------] 1 test from Vector100kTest
[ RUN      ] Vector100kTest.BuildTimesTest
[ AVG TIME ] 37735.5ms
[       OK ] Vector100kTest.BuildTimesTest (188991 ms)
[----------] 1 test from Vector100kTest (188993 ms total)

[----------] Global test environment tear-down
[==========] 9 tests from 9 test cases ran. (273931 ms total)
[  PASSED  ] 9 tests.
Press any key to continue . . .
```

Updated results with vector initializer lists:
To repeat this test use
https://github.com/janwilmans/CompileTimer/tree/24fde2dbded84e71f5d0ebc71f1b6c8bdc4674b1

```
ERROR: The process "tracker.exe" not found.
ERROR: The process "cl.exe" not found.
[==========] Running 11 tests from 11 test cases.
[----------] Global test environment set-up.
[----------] 1 test from BaselineEmptyTest
[ RUN      ] BaselineEmptyTest.BuildTimesTest
[ AVG TIME ] EMPTY_BASELINE: 4ns
[       OK ] BaselineEmptyTest.BuildTimesTest (2 ms)
[----------] 1 test from BaselineEmptyTest (2 ms total)

[----------] 1 test from BaselineSleep1msTest
[ RUN      ] BaselineSleep1msTest.BuildTimesTest
[---(0)----] cycletime: 20ms
[---(1)----] cycletime: 20ms
[---(2)----] cycletime: 20ms
[---(3)----] cycletime: 21ms
[---(4)----] cycletime: 21ms
[ AVG TIME ] 20ms Baseline: 23.743ms
[       OK ] BaselineSleep1msTest.BuildTimesTest (120 ms)
[----------] 1 test from BaselineSleep1msTest (120 ms total)

[----------] 1 test from EmptyProjectTest
[ RUN      ] EmptyProjectTest.BuildTimesTest
             msbuild gen\project.vcxproj /t:Rebuild /p:Configuration=Debug
[---(0)----] cycletime: 942ms
             msbuild gen\project.vcxproj /t:Rebuild /p:Configuration=Debug
[---(1)----] cycletime: 785ms
             msbuild gen\project.vcxproj /t:Rebuild /p:Configuration=Debug
[---(2)----] cycletime: 772ms
             msbuild gen\project.vcxproj /t:Rebuild /p:Configuration=Debug
[---(3)----] cycletime: 765ms
             msbuild gen\project.vcxproj /t:Rebuild /p:Configuration=Debug
[---(4)----] cycletime: 765ms
[ AVG TIME ] 808.317ms
[       OK ] EmptyProjectTest.BuildTimesTest (4047 ms)
[----------] 1 test from EmptyProjectTest (4047 ms total)

[----------] 1 test from WindowsHeaderTest
[ RUN      ] WindowsHeaderTest.BuildTimesTest
             msbuild gen\project.vcxproj /t:Rebuild /p:Configuration=Debug
[---(0)----] cycletime: 1128ms
             msbuild gen\project.vcxproj /t:Rebuild /p:Configuration=Debug
[---(1)----] cycletime: 1162ms
             msbuild gen\project.vcxproj /t:Rebuild /p:Configuration=Debug
[---(2)----] cycletime: 1142ms
             msbuild gen\project.vcxproj /t:Rebuild /p:Configuration=Debug
[---(3)----] cycletime: 1138ms
             msbuild gen\project.vcxproj /t:Rebuild /p:Configuration=Debug
[---(4)----] cycletime: 1131ms
[ AVG TIME ] 1142.36ms
[       OK ] WindowsHeaderTest.BuildTimesTest (5720 ms)
[----------] 1 test from WindowsHeaderTest (5720 ms total)

[----------] 1 test from Vector1kTest
[ RUN      ] Vector1kTest.BuildTimesTest
             msbuild gen\project.vcxproj /t:Rebuild /p:Configuration=Debug
[---(0)----] cycletime: 1240ms
             msbuild gen\project.vcxproj /t:Rebuild /p:Configuration=Debug
[---(1)----] cycletime: 1218ms
             msbuild gen\project.vcxproj /t:Rebuild /p:Configuration=Debug
[---(2)----] cycletime: 1232ms
             msbuild gen\project.vcxproj /t:Rebuild /p:Configuration=Debug
[---(3)----] cycletime: 1242ms
             msbuild gen\project.vcxproj /t:Rebuild /p:Configuration=Debug
[---(4)----] cycletime: 1248ms
[ AVG TIME ] 1238.76ms
[       OK ] Vector1kTest.BuildTimesTest (6208 ms)
[----------] 1 test from Vector1kTest (6210 ms total)

[----------] 1 test from VectorInit1kTest
[ RUN      ] VectorInit1kTest.BuildTimesTest
             msbuild gen\project.vcxproj /t:Rebuild /p:Configuration=Debug
[---(0)----] cycletime: 1137ms
             msbuild gen\project.vcxproj /t:Rebuild /p:Configuration=Debug
[---(1)----] cycletime: 1130ms
             msbuild gen\project.vcxproj /t:Rebuild /p:Configuration=Debug
[---(2)----] cycletime: 1107ms
             msbuild gen\project.vcxproj /t:Rebuild /p:Configuration=Debug
[---(3)----] cycletime: 1120ms
             msbuild gen\project.vcxproj /t:Rebuild /p:Configuration=Debug
[---(4)----] cycletime: 1103ms
[ AVG TIME ] 1122.22ms
[       OK ] VectorInit1kTest.BuildTimesTest (5621 ms)
[----------] 1 test from VectorInit1kTest (5623 ms total)

[----------] 1 test from VectorWith10Values1kTest
[ RUN      ] VectorWith10Values1kTest.BuildTimesTest
             msbuild gen\project.vcxproj /t:Rebuild /p:Configuration=Debug
[---(0)----] cycletime: 1488ms
             msbuild gen\project.vcxproj /t:Rebuild /p:Configuration=Debug
[---(1)----] cycletime: 1558ms
             msbuild gen\project.vcxproj /t:Rebuild /p:Configuration=Debug
[---(2)----] cycletime: 1508ms
             msbuild gen\project.vcxproj /t:Rebuild /p:Configuration=Debug
[---(3)----] cycletime: 1509ms
             msbuild gen\project.vcxproj /t:Rebuild /p:Configuration=Debug
[---(4)----] cycletime: 1526ms
[ AVG TIME ] 1520.88ms
[       OK ] VectorWith10Values1kTest.BuildTimesTest (7616 ms)
[----------] 1 test from VectorWith10Values1kTest (7618 ms total)

[----------] 1 test from VectorWith20Values1kTest
[ RUN      ] VectorWith20Values1kTest.BuildTimesTest
             msbuild gen\project.vcxproj /t:Rebuild /p:Configuration=Debug
[---(0)----] cycletime: 1773ms
             msbuild gen\project.vcxproj /t:Rebuild /p:Configuration=Debug
[---(1)----] cycletime: 1792ms
             msbuild gen\project.vcxproj /t:Rebuild /p:Configuration=Debug
[---(2)----] cycletime: 1798ms
             msbuild gen\project.vcxproj /t:Rebuild /p:Configuration=Debug
[---(3)----] cycletime: 1794ms
             msbuild gen\project.vcxproj /t:Rebuild /p:Configuration=Debug
[---(4)----] cycletime: 1788ms
[ AVG TIME ] 1791.65ms
[       OK ] VectorWith20Values1kTest.BuildTimesTest (8972 ms)
[----------] 1 test from VectorWith20Values1kTest (8980 ms total)

[----------] 1 test from Vector2KTest
[ RUN      ] Vector2KTest.BuildTimesTest
             msbuild gen\project.vcxproj /t:Rebuild /p:Configuration=Debug
[---(0)----] cycletime: 1563ms
[ AVG TIME ] 1564.69ms
[       OK ] Vector2KTest.BuildTimesTest (1581 ms)
[----------] 1 test from Vector2KTest (1594 ms total)

[----------] 1 test from Vector2kSameTest
[ RUN      ] Vector2kSameTest.BuildTimesTest
             msbuild gen\project.vcxproj /t:Rebuild /p:Configuration=Debug
[---(0)----] cycletime: 1544ms
[ AVG TIME ] 1545.11ms
[       OK ] Vector2kSameTest.BuildTimesTest (1558 ms)
[----------] 1 test from Vector2kSameTest (1565 ms total)

[----------] 1 test from Vector5kTest
[ RUN      ] Vector5kTest.BuildTimesTest
             msbuild gen\project.vcxproj /t:Rebuild /p:Configuration=Debug
[---(0)----] cycletime: 4210ms
[ AVG TIME ] 4212.58ms
[       OK ] Vector5kTest.BuildTimesTest (4231 ms)
[----------] 1 test from Vector5kTest (4231 ms total)

[----------] Global test environment tear-down
[==========] 11 tests from 11 test cases ran. (45736 ms total)
[  PASSED  ] 11 tests.
Press any key to continue . . .

```

```
ERROR: The process "tracker.exe" not found.
ERROR: The process "cl.exe" not found.
[==========] Running 11 tests from 11 test cases.
[----------] Global test environment set-up.
[----------] 1 test from BaselineEmptyTest
[ RUN      ] BaselineEmptyTest.BuildTimesTest
[ AVG TIME ] EMPTY_BASELINE: 1ns
[       OK ] BaselineEmptyTest.BuildTimesTest (1 ms)
[----------] 1 test from BaselineEmptyTest (1 ms total)

[----------] 1 test from BaselineSleep1msTest
[ RUN      ] BaselineSleep1msTest.BuildTimesTest
[ AVG TIME ] 20ms Baseline: 20.395ms
[       OK ] BaselineSleep1msTest.BuildTimesTest (103 ms)
[----------] 1 test from BaselineSleep1msTest (103 ms total)

[----------] 1 test from EmptyProjectTest
[ RUN      ] EmptyProjectTest.BuildTimesTest
[ AVG TIME ] 810ms
[       OK ] EmptyProjectTest.BuildTimesTest (4063 ms)
[----------] 1 test from EmptyProjectTest (4064 ms total)

[----------] 1 test from WindowsHeaderTest
[ RUN      ] WindowsHeaderTest.BuildTimesTest
[ AVG TIME ] 1179ms
[       OK ] WindowsHeaderTest.BuildTimesTest (5904 ms)
[----------] 1 test from WindowsHeaderTest (5904 ms total)

[----------] 1 test from Vector1kTest
[ RUN      ] Vector1kTest.BuildTimesTest
[ AVG TIME ] 11562ms
[       OK ] Vector1kTest.BuildTimesTest (57827 ms)
[----------] 1 test from Vector1kTest (57829 ms total)

[----------] 1 test from VectorInit1kTest
[ RUN      ] VectorInit1kTest.BuildTimesTest
[ AVG TIME ] 3880ms
[       OK ] VectorInit1kTest.BuildTimesTest (19417 ms)
[----------] 1 test from VectorInit1kTest (19417 ms total)

[----------] 1 test from VectorWith10Values1kTest
[ RUN      ] VectorWith10Values1kTest.BuildTimesTest
[ AVG TIME ] 245429ms         //////// <= link.exe running 4 minutes?
[       OK ] VectorWith10Values1kTest.BuildTimesTest (1227162 ms)
[----------] 1 test from VectorWith10Values1kTest (1227162 ms total)

[----------] 1 test from VectorWith20Values1kTest
[ RUN      ] VectorWith20Values1kTest.BuildTimesTest
[ AVG TIME ] 3797ms
[       OK ] VectorWith20Values1kTest.BuildTimesTest (19003 ms)
[----------] 1 test from VectorWith20Values1kTest (19003 ms total)

[----------] 1 test from Vector2KTest
[ RUN      ] Vector2KTest.BuildTimesTest
[ AVG TIME ] 63495ms
[       OK ] Vector2KTest.BuildTimesTest (63511 ms)
[----------] 1 test from Vector2KTest (63518 ms total)

[----------] 1 test from Vector2kSameTest
[ RUN      ] Vector2kSameTest.BuildTimesTest
[ AVG TIME ] 62668ms
[       OK ] Vector2kSameTest.BuildTimesTest (62683 ms)
[----------] 1 test from Vector2kSameTest (62684 ms total)

[----------] 1 test from Vector5kTest
[ RUN      ] Vector5kTest.BuildTimesTest
[ AVG TIME ] 9561ms
[       OK ] Vector5kTest.BuildTimesTest (9580 ms)
[----------] 1 test from Vector5kTest (9592 ms total)

[----------] Global test environment tear-down
[==========] 11 tests from 11 test cases ran. (1469296 ms total)
[  PASSED  ] 11 tests.
Press any key to continue . . .

```
