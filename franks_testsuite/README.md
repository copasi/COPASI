This is the legacy test wrapper written to support:

[Bergmann, F. T., & Sauro, H. M. (2008). Comparing simulation results of SBML capable simulators. *Bioinformatics*, 24(17), 1963–1965.](https://doi.org/10.1093/bioinformatics/btn319)

it imports SBML files, configures a report, and sets up the time course task to simulate the file
for 10 secodns. To run it: 

* configure with `BUILD_FRANKS_TESTSUITE=ON`
* and run:

```
franks-testsuite SBMLFILENAME STARTTIME ENDTIME STEPNUMBER OUTFILENAME
```


More comprehensive tests are defined in the [python copasi testsuite](https://github.com/copasi/python-copasi-testsuite/).