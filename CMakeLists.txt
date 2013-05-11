CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
PROJECT(rummikub--)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
SET(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall")
SET(CMAKE_INSTALL_RPATH ${CMAKE_INSTALL_PREFIX}/lib)

OPTION(RUMMIKUB_BUILD_TESTS "Build tests for rummikub" OFF)

INCLUDE(ExternalProject)
SET_DIRECTORY_PROPERTIES(PROPERTIES EP_PREFIX ${CMAKE_BINARY_DIR}/third-party)

IF(RUMMIKUB_BUILD_TESTS)
  MESSAGE("Enable rummikub test...")
  ENABLE_TESTING()
  ExternalProject_Add(
    googletest
    SVN_REPOSITORY http://googletest.googlecode.com/svn/tags/release-1.6.0
    TIMEOUT 10
    # Force separate output paths for debug and release builds to allow easy
    # identification of correct lib in subsequent TARGET_LINK_LIBRARIES commands
    CMAKE_ARGS -Dgtest_force_shared_crt=ON
    # Disable install step
    INSTALL_COMMAND ""
    # Wrap download, configure and build steps in a script to log output
    LOG_DOWNLOAD ON
    LOG_CONFIGURE ON
    LOG_BUILD ON
  )
ENDIF(RUMMIKUB_BUILD_TESTS)

ADD_SUBDIRECTORY(core)
ADD_SUBDIRECTORY(game)

INCLUDE(CPack)

