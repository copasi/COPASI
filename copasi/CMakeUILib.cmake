if(QT_USE_FILE)
include(${QT_USE_FILE})

if (ENABLE_SBW_INTEGRATION)
# SBW
include_directories(BEFORE ${SBW_INCLUDE_DIR})
endif()

# QWT
include_directories(BEFORE ${QWT_INCLUDE_DIR})

# QWTPLOT3D
include_directories(BEFORE ${QWTPLOT3D_INCLUDE_DIR})
endif(QT_USE_FILE)

