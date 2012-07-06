# Try to find the Qwt library
# Once done this will define
#
#  QWT_FOUND - system has qwt
#  QWT_INCLUDE_DIR - the qwt include directory
#  QWT_LIBRARIES - Link these to use qwt

find_path(QWT_INCLUDE_DIR qwt.h)

find_library(QWT_LIBRARIES NAMES qwt-qt4 libqwt-qt4 qwt libqwt)

# handle the QUIETLY and REQUIRED arguments and set QWT_FOUND to TRUE if
# all listed variables are TRUE
include(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(QWT DEFAULT_MSG QWT_LIBRARIES QWT_INCLUDE_DIR)

mark_as_advanced(QWT_INCLUDE_DIR QWT_LIBRARIES)

