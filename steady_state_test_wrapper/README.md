Legacy testwrapper for steady state tests. 

* it imports SBML files
* sets up the steady state task and report

to use it:

* configure with `BUILD_STEADY_STATE_RUNNER=ON`
* run

```bash
steady_state_test_wrapper SBMLFILENAME OUTPUTFILE_PREFIX
```

More comprehensive tests are defined in the [python copasi testsuite](https://github.com/copasi/python-copasi-testsuite/).