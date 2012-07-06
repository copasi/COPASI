# Try to find the CLAPACK library
# Once done this will define
#
#  CLAPACK_FOUND - system has clapack
#  CLAPACK_INCLUDE_DIR - the clapack include directory
#  CLAPACK_LIBRARIES - Link these to use clapack
#  TODO USE_BLASWRAP - whether clapack was compiled with blaswrap support

find_path(CLAPACK_INCLUDE_DIR clapack.h)

find_library(CLAPACK_LIBRARIES NAMES clapack libclapack lapack liblapapack)

# handle the QUIETLY and REQUIRED arguments and set CLAPACK_FOUND to TRUE if
# all listed variables are TRUE
include(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(CLAPACK DEFAULT_MSG CLAPACK_LIBRARIES CLAPACK_INCLUDE_DIR)

mark_as_advanced(CLAPACK_INCLUDE_DIR CLAPACK_LIBRARIES)

