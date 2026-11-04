## Event Testsuite

This test suite runs the event tests. It runs `CopasiSE` on the test files. It is configured as test, when: 

* `CopasiSE` is built
*  a python interpreter is found

then it can be run using `ctest -R CopasiTestsuite`. 

If you want to manually invoke these tests, you would run (from the current folder): 

```bash
ABSOLUTE_ERROR=1e-04
RELATIVE_ERROR=1e-04
python3 ../Tools/RunTests.py `which CopasiSE` out ./Tests
```

The environment variables set the relative and absolute error for the comparison. The `RunTests` script takes
the arguments: 

* full path to the CopasiSE executable
* output directory
* test directory

This will run all the tests specified in [./Tests/TestInfo.txt].
