PROJECT(core)

INCLUDE_DIRECTORIES(include)
AUX_SOURCE_DIRECTORY(src core_SOURCES)

# For Qt creator to find the public headers.
FILE(GLOB core_HEADERS include/*.h)

ADD_LIBRARY(${PROJECT_NAME} SHARED ${core_SOURCES} ${core_HEADERS})

