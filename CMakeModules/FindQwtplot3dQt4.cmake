# Try to find the qwtplot3d library
# Once done this will define
#
#  QWTPLOT3D_FOUND - system has qwtplot3d
#  QWTPLOT3D_INCLUDE_DIR - the qwtplot3d include directory
#  QWTPLOT3D_LIBRARIES - Link these to use qwtplot3d

find_path(QWTPLOT3D_INCLUDE_DIR qwt3d_plot.h
    PATHS $ENV{QWTPLOT3D_DIR}/include
          $ENV{QWTPLOT3D_DIR}
          ~/Library/Frameworks
          /Library/Frameworks
          /usr/local/include
          /usr/include/
          /sw/include # Fink
          /opt/local/include # DarwinPorts
          /opt/csw/include # Blastwave
          /opt/include
          /usr/freeware/include
    PATH_SUFFIXES qwtplot3d qwtplot3d-qt4 
)

find_library(QWTPLOT3D_LIBRARIES NAMES qwtplot3d-qt4 libqwtplot3d-qt4 qwtplot3d libqwtplot3d)

# handle the QUIETLY and REQUIRED arguments and set SBW_FOUND to TRUE if
# all listed variables are TRUE
include(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(QWTPLOT3D DEFAULT_MSG QWTPLOT3D_LIBRARIES QWTPLOT3D_INCLUDE_DIR)

mark_as_advanced(QWTPLOT3D_INCLUDE_DIR QWTPLOT3D_LIBRARIES)

