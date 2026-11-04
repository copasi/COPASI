The tests in this folder uses [Catch2](https://catch2.org) to test the functionality
of COPASI. 

It is integrated with CMake, once configured with `BUILD_TESTS=ON`. To run use: 

```bash
ctest -R api -V
```

to invoke manually, specify the `srcdir` environment variable to point to this folder, 
this is needed to resolve the files in `./test-data/`.

You can manually invoke the test runer with the following command line switches: 

```
 ./tests/test_api --help

Catch v2.13.10
usage:
  test_api [<test name|pattern|tags> ... ] options

where options are:
  -?, -h, --help                            display usage information
  -l, --list-tests                          list all/matching test cases
  -t, --list-tags                           list all/matching tags
  -s, --success                             include successful tests in
                                            output
  -b, --break                               break into debugger on failure
  -e, --nothrow                             skip exception tests
  -i, --invisibles                          show invisibles (tabs, newlines)
  -o, --out <filename>                      output filename
  -r, --reporter <name>                     reporter to use (defaults to
                                            console)
  -n, --name <name>                         suite name
  -a, --abort                               abort at first failure
  -x, --abortx <no. failures>               abort after x failures
  -w, --warn <warning name>                 enable warnings
  -d, --durations <yes|no>                  show test durations
  -D, --min-duration <seconds>              show test durations for tests
                                            taking at least the given number
                                            of seconds
  -f, --input-file <filename>               load test names to run from a
                                            file
  -#, --filenames-as-tags                   adds a tag for the filename
  -c, --section <section name>              specify section to run
  -v, --verbosity <quiet|normal|high>       set output verbosity
  --list-test-names-only                    list all/matching test cases
                                            names only
  --list-reporters                          list all reporters
  --order <decl|lex|rand>                   test case order (defaults to
                                            decl)
  --rng-seed <'time'|number>                set a specific seed for random
                                            numbers
  --use-colour <yes|no>                     should output be colourised
  --libidentify                             report name and version according
                                            to libidentify standard
  --wait-for-keypress <never|start|exit     waits for a keypress before
  |both>                                    exiting
  --benchmark-samples <samples>             number of samples to collect
                                            (default: 100)
  --benchmark-resamples <resamples>         number of resamples for the
                                            bootstrap (default: 100000)
  --benchmark-confidence-interval           confidence interval for the
  <confidence interval>                     bootstrap (between 0 and 1,
                                            default: 0.95)
  --benchmark-no-analysis                   perform only measurements; do not
                                            perform any analysis
  --benchmark-warmup-time                   amount of time in milliseconds
  <benchmarkWarmupTime>                     spent on warming up each test
                                            (default: 100)

```

For example the list of test tags right now is: 

```bash
./tests/test_api -t    
All available tags:
  37  [COPASI][copasi]
   5  [creation]
   1  [data]
   3  [datahandler]
   2  [manipulation]
   2  [miriam]
   1  [multiple_models]
   1  [optimization]
   9  [sbml]
   9  [sedml]
```

so to run only the sedml tests, you would run: 

```bash
./tests/test_api "[sedml]"
Filters: [sedml]
===============================================================================
All tests passed (80 assertions in 9 test cases)
```

(ensure to have the `srcdir` environment variable defined first.)