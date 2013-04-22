PROJECT(rummiqcore)

FIND_PACKAGE(Qt4 REQUIRED)

INCLUDE_DIRECTORIES(include)
INCLUDE_DIRECTORIES(${rummicore_SOURCE_DIR}/include)
AUX_SOURCE_DIRECTORY(src rummiqcore_SOURCES)

# For Qt creator to find the public headers.
FILE(GLOB rummiqcore_HEADERS include/qmodel/*.h)

INCLUDE(${QT_USE_FILE})
ADD_DEFINITIONS(${QT_DEFINITIONS})
QT4_WRAP_CPP(rummiqcore_HEADERS_MOC ${rummiqcore_HEADERS})

ADD_LIBRARY(${PROJECT_NAME} SHARED ${rummiqcore_SOURCES} ${rummiqcore_HEADERS_MOC} ${rummiqcore_HEADERS})
INSTALL(TARGETS ${PROJECT_NAME}
  LIBRARY DESTINATION lib
)

