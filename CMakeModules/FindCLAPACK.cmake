# Copyright (C) 2012 - 2013 by Pedro Mendes, Virginia Tech Intellectual 
# Properties, Inc., University of Heidelberg, and The University 
# of Manchester. 
# All rights reserved. 

# Try to find the CLAPACK library
# Once done this will define
#
#  CLAPACK_FOUND - system has clapack
#  CLAPACK_INCLUDE_DIR - the clapack include directory
#  CLAPACK_LIBRARIES - Link these to use clapack
#  TODO USE_BLASWRAP - whether clapack was compiled with blaswrap support

#  Goto, 
#  ATLAS,
#  PhiPACK,
#  CXML,
#  DXML,
#  SunPerf,
#  SCSL,
#  SGIMATH,
#  IBMESSL,
#  Intel10_32 (intel mkl v10 32 bit),
#  Intel10_64lp (intel mkl v10 64 bit,lp thread model, lp64 model),
#  Intel( older versions of mkl 32 and 64 bit), 
#  ACML,
#  ACML_MP,
#  ACML_GPU,
#  Apple, 
#  NAS, 
#  Generic

set(LAPACK_FIND_QUIETLY TRUE)


set(BLA_VENDOR "Apple")
find_package(LAPACK)
  
if (LAPACK_FOUND)
  add_definitions(-DHAVE_APPLE)
endif ()

if (NOT LAPACK_FOUND)
  # cmake MKL Detection does only support MKL version 10 and older
  if (DEFINED ENV{MKLROOT})
    set(BLA_VENDOR "Intel (MKL)")

    if (UNIX)
      if (COPASI_BUILD_TYPE EQUAL "32bit")
        set(LAPACK_LIBRARIES "-Wl,--start-group $ENV{MKLROOT}/lib/ia32/libmkl_intel.a $ENV{MKLROOT}/lib/ia32/libmkl_core.a $ENV{MKLROOT}/lib/ia32/libmkl_sequential.a -Wl,--end-group -lpthread -lm")
      elseif (COPASI_BUILD_TYPE EQUAL "64bit")
        set(LAPACK_LIBRARIES "-Wl,--start-group $ENV{MKLROOT}/lib/intel64/libmkl_intel_lp64.a $ENV{MKLROOT}/lib/intel64/libmkl_core.a $ENV{MKLROOT}/lib/intel64/libmkl_sequential.a -Wl,--end-group -lpthread -lm")
      endif ()
    else ()
      if (COPASI_BUILD_TYPE EQUAL "32bit")
        set(LAPACK_LIBRARIES "mkl_intel_c.lib mkl_core.lib mkl_sequential.lib")
        set(LAPACK_LINKER_FLAGS "-LIBPATH:\"$ENV{MKLROOT}/lib/ia32\"")
      elseif (COPASI_BUILD_TYPE EQUAL "64bit")
        set(LAPACK_LIBRARIES "mkl_intel_lp64.lib mkl_core.lib mkl_sequential.lib")
        set(LAPACK_LINKER_FLAGS "-LIBPATH:\"$ENV{MKLROOT}/lib/intel64\"")
      endif ()
    endif ()

    add_definitions(-DHAVE_MKL)
    set(LAPACK_FOUND "Yes")
  endif ()
endif ()

if (NOT LAPACK_FOUND)
  set(BLA_VENDOR "ATLAS")
  find_package(LAPACK)
endif() 

if (NOT LAPACK_FOUND)
  set(BLA_VENDOR "Generic")
  find_package(LAPACK REQUIRED)
endif() 

find_path(BLASWRAP_INCLUDE_DIR blaswrap.h
    PATHS $ENV{LAPACK_DIR}/include
          $ENV{LAPACK_DIR}
          ~/Library/Frameworks
          /Library/Frameworks
          /usr/local/include
          /usr/include/
          /sw/include        # Fink
          /opt/local/include # DarwinPorts
          /opt/csw/include   # Blastwave
          /opt/include
          /usr/freeware/include
)

if (BLASWRAP_INCLUDE_DIR)
  add_definitions(-DHAVE_BLASWRAP_H)
endif (BLASWRAP_INCLUDE_DIR)

find_path(F2C_INCLUDE_DIR f2c.h
    PATHS $ENV{LAPACK_DIR}/include
          $ENV{LAPACK_DIR}
          ~/Library/Frameworks
          /Library/Frameworks
          /usr/local/include
          /usr/include/
          /sw/include        # Fink
          /opt/local/include # DarwinPorts
          /opt/csw/include   # Blastwave
          /opt/include
          /usr/freeware/include
)

if (F2C_INCLUDE_DIR)
  add_definitions(-DHAVE_F2C_H)
endif (F2C_INCLUDE_DIR)

find_path(BLAS_INCLUDE_DIR blas.h
    PATHS $ENV{LAPACK_DIR}/include
          $ENV{LAPACK_DIR}
          ~/Library/Frameworks
          /Library/Frameworks
          /usr/local/include
          /usr/include/
          /sw/include        # Fink
          /opt/local/include # DarwinPorts
          /opt/csw/include   # Blastwave
          /opt/include
          /usr/freeware/include
)

if (BLAS_INCLUDE_DIR)
  add_definitions(-DHAVE_BLAS_H)
endif (BLAS_INCLUDE_DIR)

find_path(LAPACKWRAP_INCLUDE_DIR lapackwrap.h
    PATHS $ENV{LAPACK_DIR}/include
          $ENV{LAPACK_DIR}
          ~/Library/Frameworks
          /Library/Frameworks
          /usr/local/include
          /usr/include/
          /sw/include        # Fink
          /opt/local/include # DarwinPorts
          /opt/csw/include   # Blastwave
          /opt/include
          /usr/freeware/include
)

if (LAPACKWRAP_INCLUDE_DIR)
  add_definitions(-DHAVE_LAPACKWRAP_H)
endif (LAPACKWRAP_INCLUDE_DIR)

find_path(CLAPACK_INCLUDE_DIR clapack.h
    PATHS $ENV{LAPACK_DIR}/include
          $ENV{LAPACK_DIR}
          ~/Library/Frameworks
          /Library/Frameworks
          /usr/local/include
          /usr/include/
          /sw/include        # Fink
          /opt/local/include # DarwinPorts
          /opt/csw/include   # Blastwave
          /opt/include
          /usr/freeware/include
)

if (CLAPACK_INCLUDE_DIR)
  add_definitions(-DHAVE_CLAPACK_H)
endif (CLAPACK_INCLUDE_DIR)

if (NOT CLAPACK_INCLUDE_DIR)
  find_path(CLAPACK_INCLUDE_DIR lapack.h
      PATHS $ENV{LAPACK_DIR}/include
            $ENV{LAPACK_DIR}
            ~/Library/Frameworks
            /Library/Frameworks
            /usr/local/include
            /usr/include/
            /sw/include        # Fink
            /opt/local/include # DarwinPorts
            /opt/csw/include   # Blastwave
            /opt/include
            /usr/freeware/include
)

  if (CLAPACK_INCLUDE_DIR)
    add_definitions(-DHAVE_LAPACK_H)
  endif (CLAPACK_INCLUDE_DIR)
endif (NOT CLAPACK_INCLUDE_DIR)

if (NOT CLAPACK_INCLUDE_DIR)
  set(CLAPACK_INCLUDE_DIR "${COPASI_SOURCE_DIR}")
endif (NOT CLAPACK_INCLUDE_DIR)

set(CLAPACK_LIBRARIES ${LAPACK_LIBRARIES})
set(CLAPACK_LINKER_FLAGS ${LAPACK_LINKER_FLAGS})

# find_library(CLAPACK_LIBRARIES NAMES clapack libclapack lapack liblapapack)

# handle the QUIETLY and REQUIRED arguments and set CLAPACK_FOUND to TRUE if
# all listed variables are TRUE
include(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(CLAPACK DEFAULT_MSG CLAPACK_LIBRARIES CLAPACK_INCLUDE_DIR)

mark_as_advanced(CLAPACK_INCLUDE_DIR CLAPACK_LIBRARIES)


