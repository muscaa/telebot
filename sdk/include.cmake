message(STATUS "Adding subdirectory: ${SDK_DIR}")

include(${SDK_DIR}/packages.cmake)

add_subdirectory(${SDK_DIR})
