PROJECT(rummicore)

INCLUDE_DIRECTORIES(include)
AUX_SOURCE_DIRECTORY(src rummicore_SOURCES)

# For Qt creator to find the headers.
FILE(GLOB_RECURSE rummicore_INCLUDE_HEADERS include *.h)
FILE(GLOB rummicore_SOURCE_HEADERS src/*.h)
SET(rummicore_HEADERS ${rummicore_INCLUDE_HEADERS} ${rummicore_SOURCE_HEADERS})

ADD_LIBRARY(${PROJECT_NAME} SHARED ${rummicore_SOURCES} ${rummicore_HEADERS})
INSTALL(TARGETS ${PROJECT_NAME}
  LIBRARY DESTINATION lib
)

IF(RUMMIKUB_BUILD_TESTS)
  INCLUDE(${rummikub--_SOURCE_DIR}/cmake/GTestUtil.cmake)
  AUX_SOURCE_DIRECTORY(test rummicore_TEST_SOURCES)
  ADD_GTEST_TEST(${PROJECT_NAME} ${rummicore_TEST_SOURCES})
ENDIF(RUMMIKUB_BUILD_TESTS)

