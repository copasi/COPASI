# Copyright (C) 2019 - 2022 by Pedro Mendes, Rector and Visitors of the 
# University of Virginia, University of Heidelberg, and University 
# of Connecticut School of Medicine. 
# All rights reserved. 

# Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual 
# Properties, Inc., University of Heidelberg, and University of 
# of Connecticut School of Medicine. 
# All rights reserved. 

# Copyright (C) 2012 - 2016 by Pedro Mendes, Virginia Tech Intellectual 
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

string(TOUPPER ${PROJECT_NAME} _UPPER_PROJECT_NAME)
set(_PROJECT_DEPENDENCY_DIR ${_UPPER_PROJECT_NAME}_DEPENDENCY_DIR)

set(LAPACK_FIND_QUIETLY TRUE)
set(BLA_STATIC TRUE)
set(LAPACK_STATIC TRUE)

if (APPLE)
  set(BLA_VENDOR "Apple")
  find_package(LAPACK)
endif()

if (BLAS_FOUND AND APPLE)
  add_definitions(-DHAVE_APPLE)

  if (NOT CLAPACK_INCLUDE_DIR)
    # as it turns out the new OSX has different definitions for blas
    # it is a bit hard to find the right directory, so lets try here
    exec_program(xcode-select ARGS -print-path OUTPUT_VARIABLE CMAKE_XCODE_DEVELOPER_DIR)
    find_path(CLAPACK_INCLUDE_DIR cblas.h
    PATHS
       ${CMAKE_OSX_SYSROOT}/System/Library/Frameworks/Accelerate.framework/Versions/Current/Frameworks/vecLib.framework/Headers/
       ${CMAKE_XCODE_DEVELOPER_DIR}/Platforms/MacOSX.platform/Developer/SDKs/MacOSX.sdk/System/Library/Frameworks/Accelerate.framework/Versions/Current/Frameworks/vecLib.framework/Headers/
    )

    if (CLAPACK_INCLUDE_DIR)
      add_definitions(-DHAVE_CBLAS_H)
    endif()

    if (NOT CLAPACK_INCLUDE_DIR)
      # fallback
      set(CLAPACK_INCLUDE_DIR "${COPASI_SOURCE_DIR}")
    endif (NOT CLAPACK_INCLUDE_DIR)

  else()
  
    add_definitions(-DHAVE_CBLAS_H)
    
  endif (NOT CLAPACK_INCLUDE_DIR)


  if (NOT CLAPACK_LIBRARIES)
    set(CLAPACK_LIBRARIES ${BLAS_LIBRARIES})
  endif(NOT CLAPACK_LIBRARIES)

endif()

if (LAPACK_FOUND)
  add_definitions(-DHAVE_APPLE)
  if (NOT CLAPACK_INCLUDE_DIR)
    set(CLAPACK_INCLUDE_DIR "${COPASI_SOURCE_DIR}")
  endif (NOT CLAPACK_INCLUDE_DIR)


  if (NOT CLAPACK_LIBRARIES)
    set(CLAPACK_LIBRARIES ${LAPACK_LIBRARIES})
  endif(NOT CLAPACK_LIBRARIES)

  if (NOT CLAPACK_LINKER_FLAGS)
    set(CLAPACK_LINKER_FLAGS ${LAPACK_LINKER_FLAGS})
  endif(NOT CLAPACK_LINKER_FLAGS)

endif ()

if (NOT LAPACK_FOUND)
  # cmake MKL Detection does only support MKL version 10 and older
  if (DEFINED ENV{MKLROOT})
    set(BLA_VENDOR "Intel (MKL)")

    if (UNIX)
      if (COPASI_BUILD_TYPE EQUAL "32bit")
        set(LAPACK_LIBRARIES "-Wl,--start-group $ENV{MKLROOT}/lib/ia32/libmkl_intel.a $ENV{MKLROOT}/lib/ia32/libmkl_core.a $ENV{MKLROOT}/lib/ia32/libmkl_sequential.a -Wl,--end-group -lpthread -lm -ldl")
      elseif (COPASI_BUILD_TYPE EQUAL "64bit")
        set(LAPACK_LIBRARIES "-Wl,--start-group $ENV{MKLROOT}/lib/intel64/libmkl_intel_lp64.a $ENV{MKLROOT}/lib/intel64/libmkl_core.a $ENV{MKLROOT}/lib/intel64/libmkl_sequential.a -Wl,--end-group -lpthread -lm -ldl")
      endif ()
    else ()
      if (COPASI_BUILD_TYPE EQUAL "32bit")
        set(LAPACK_LIBRARIES "$ENV{MKLROOT}/lib/ia32/mkl_intel_c.lib" "$ENV{MKLROOT}/lib/ia32/mkl_core.lib" "$ENV{MKLROOT}/lib/ia32/mkl_sequential.lib")
      elseif (COPASI_BUILD_TYPE EQUAL "64bit")
        set(LAPACK_LIBRARIES "$ENV{MKLROOT}/lib/intel64/mkl_intel_lp64.lib" "$ENV{MKLROOT}/lib/intel64/mkl_core.lib" "$ENV{MKLROOT}/lib/intel64/mkl_sequential.lib")
      endif ()
    endif ()

    add_definitions(-DHAVE_MKL)
    set(LAPACK_FOUND "Yes")
  endif ()
endif ()

if (NOT LAPACK_FOUND AND DEFINED ENV{LAPACK_DIR} AND EXISTS $ENV{LAPACK_DIR})
  message (status " Using COPASI Dependencies for LAPACK")

  # clapack
  set (CLAPACK_INCLUDE_DIR $ENV{LAPACK_DIR}/include CACHE PATH "clapack include directory" FORCE)

  find_library(CLAPACK_LIBRARY_LAPACK
      NAMES lapack
      PATHS $ENV{LAPACK_DIR}/${CMAKE_INSTALL_LIBDIR} ${${_PROJECT_DEPENDENCY_DIR}}/${CMAKE_INSTALL_LIBDIR}
      NO_DEFAULT_PATH)

  find_library(CLAPACK_LIBRARY_BLAS
      NAMES blas
      PATHS $ENV{LAPACK_DIR}/${CMAKE_INSTALL_LIBDIR} ${${_PROJECT_DEPENDENCY_DIR}}/${CMAKE_INSTALL_LIBDIR}
      NO_DEFAULT_PATH)

  find_library(CLAPACK_LIBRARY_F2C
      NAMES f2c
      PATHS $ENV{LAPACK_DIR}/${CMAKE_INSTALL_LIBDIR} ${${_PROJECT_DEPENDENCY_DIR}}/${CMAKE_INSTALL_LIBDIR}
      NO_DEFAULT_PATH)

  set (CLAPACK_LIBRARIES
       ${CLAPACK_LIBRARY_LAPACK};${CLAPACK_LIBRARY_BLAS};${CLAPACK_LIBRARY_F2C}
       CACHE FILEPATH "lapack library" FORCE)

  add_definitions(-DHAVE_BLASWRAP_H)
  add_definitions(-DHAVE_F2C_H)
  add_definitions(-DHAVE_CLAPACK_H)
  add_definitions(-DNO_BLAS_WRAP)

  set (BLA_VENDOR "COPASI Dependencies")
  set (LAPACK_FOUND "Yes")
endif()

if (NOT LAPACK_FOUND AND LINUX)
  set(TMP ${CMAKE_FIND_LIBRARY_SUFFIXES})
  set(CMAKE_FIND_LIBRARY_SUFFIXES ${CMAKE_FIND_LIBRARY_SUFFIXES} .so.3)
  find_library( GFORTRAN_LIBRARY
                NAMES gfortran
                PATHS ENV LD_LIBRARY_PATH )
  set(CMAKE_FIND_LIBRARY_SUFFIXES ${TMP})

  if (GFORTRAN_LIBRARY)
    set(CMAKE_FIND_LIBRARY_SUFFIXES ${CMAKE_FIND_LIBRARY_SUFFIXES} .so.3gf)
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

if (LAPACK_FOUND AND GFORTRAN_LIBRARY)
  set(LAPACK_LIBRARIES ${LAPACK_LIBRARIES} ${GFORTRAN_LIBRARY} m)
endif()

if (NOT BLASWRAP_INCLUDE_DIR)
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
endif(NOT BLASWRAP_INCLUDE_DIR)

if (BLASWRAP_INCLUDE_DIR)
  add_definitions(-DHAVE_BLASWRAP_H)
endif (BLASWRAP_INCLUDE_DIR)

if (NOT F2C_INCLUDE_DIR)
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
endif(NOT F2C_INCLUDE_DIR)

if (F2C_INCLUDE_DIR)
  add_definitions(-DHAVE_F2C_H)
endif (F2C_INCLUDE_DIR)

if (NOT BLAS_INCLUDE_DIR)
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
endif(NOT BLAS_INCLUDE_DIR)

if (BLAS_INCLUDE_DIR)
  add_definitions(-DHAVE_BLAS_H)
endif (BLAS_INCLUDE_DIR)

if (NOT LAPACKWRAP_INCLUDE_DIR)
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
endif( NOT LAPACKWRAP_INCLUDE_DIR)

if (LAPACKWRAP_INCLUDE_DIR)
  add_definitions(-DHAVE_LAPACKWRAP_H)
endif (LAPACKWRAP_INCLUDE_DIR)

if(NOT CLAPACK_INCLUDE_DIR)
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
endif(NOT CLAPACK_INCLUDE_DIR)


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


if (NOT CLAPACK_LIBRARIES)
set(CLAPACK_LIBRARIES ${LAPACK_LIBRARIES})
endif(NOT CLAPACK_LIBRARIES)

if (NOT CLAPACK_LINKER_FLAGS)
set(CLAPACK_LINKER_FLAGS ${LAPACK_LINKER_FLAGS})
endif(NOT CLAPACK_LINKER_FLAGS)

if (NOT CLAPACK_LIBRARIES AND NOT APPLE)

if (CONAN_LIB_DIRS_LAPACK)

find_library( LAPACK_LIBRARY
                NAMES liblapack lapack lapack.dll
                PATHS ${CONAN_LIB_DIRS_LAPACK} )
find_library( BLAS_LIBRARY
                NAMES libblas blas blas.dll
                PATHS ${CONAN_LIB_DIRS_LAPACK} )

SET (CLAPACK_LIBRARIES ${LAPACK_LIBRARY} ${BLAS_LIBRARY})
SET (BLA_VENDOR "Conan")

endif(CONAN_LIB_DIRS_LAPACK)

if (CONAN_LIB_DIRS_CLAPACK)

find_library( LAPACK_LIBRARY
                NAMES liblapack lapack liblapack.a
                PATHS ${CONAN_LIB_DIRS_CLAPACK} )
find_library( BLAS_LIBRARY
                NAMES libblas blas libblas.a
                PATHS ${CONAN_LIB_DIRS_CLAPACK} )

find_library( F2C_LIBRARY
                NAMES libf2c libf2c.a
                PATHS ${CONAN_LIB_DIRS_CLAPACK} )

SET (CLAPACK_LIBRARIES ${LAPACK_LIBRARY} ${BLAS_LIBRARY} ${F2C_LIBRARY})
SET (CLAPACK_INCLUDE_DIR ${CONAN_INCLUDE_DIRS_CLAPACK})
SET (F2C_INCLUDE_DIR ${CONAN_INCLUDE_DIRS_CLAPACK})
SET (BLASWRAP_INCLUDE_DIR ${CONAN_INCLUDE_DIRS_CLAPACK})

SET (BLA_VENDOR "COPASI Dependencies")


add_definitions(-DHAVE_BLASWRAP_H)
add_definitions(-DHAVE_F2C_H)
add_definitions(-DHAVE_CLAPACK_H)
add_definitions(-DNO_BLAS_WRAP)


endif(CONAN_LIB_DIRS_CLAPACK)

endif(NOT CLAPACK_LIBRARIES AND NOT APPLE)

# find_library(CLAPACK_LIBRARIES NAMES clapack libclapack lapack liblapapack)

# handle the QUIETLY and REQUIRED arguments and set CLAPACK_FOUND to TRUE if
# all listed variables are TRUE
include(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(CLAPACK DEFAULT_MSG CLAPACK_LIBRARIES CLAPACK_INCLUDE_DIR BLA_VENDOR)

mark_as_advanced(CLAPACK_INCLUDE_DIR CLAPACK_LIBRARIES BLA_VENDOR)


