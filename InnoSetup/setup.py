## @file    setup.py
## @brief   Python distutils code for COPASI Python module
## 

from distutils.core import setup, Extension

setup(name             = "COPASI", 
      version          = "%COPASI_VERSION%",
      description      = "COPASI Python API",
      long_description = ("COPASI is a software application for simulation and analysis of biochemical networks and their dynamics. COPASI is a stand-alone program that supports models in the SBML standard and can simulate their behavior using ODEs or Gillespie's stochastic simulation algorithm; arbitrary discrete events can be included in such simulations."),
      license          = "Artistic License 2.0",
      author           = "COPASI Team",
      author_email     = "support@copasi.org",
      url              = "http://www.copasi.org",
      packages         = ["COPASI"],
      package_dir      = {"COPASI": "COPASI"},
      package_data     = {"COPASI": ["LICENSE", "examples/*"]},
      ext_package      = "COPASI", 
      ext_modules      = [Extension("_COPASI", 
         sources       = ["dummy"],
         define_macros = [(None)],
         include_dirs  = [],
         libraries     = [],
         library_dirs  = []
      )]
)

