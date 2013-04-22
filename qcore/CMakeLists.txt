PROJECT(rummiqcore)

FIND_PACKAGE(Qt4 REQUIRED QtCore)

INCLUDE(${QT_USE_FILE})

INCLUDE_DIRECTORIES(include)
INCLUDE_DIRECTORIES(${rummicore_SOURCE_DIR}/include)
AUX_SOURCE_DIRECTORY(src rummiqcore_SOURCES)

# For Qt creator to find the public headers.
FILE(GLOB rummiqcore_HEADERS include/qmodel/*.h)

ADD_LIBRARY(${PROJECT_NAME} SHARED ${rummiqcore_SOURCES} ${rummiqcore_HEADERS})
INSTALL(TARGETS ${PROJECT_NAME}
  LIBRARY DESTINATION lib
)

