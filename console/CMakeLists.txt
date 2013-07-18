PROJECT(rummiconsole)

AUX_SOURCE_DIRECTORY(. rummiconsole_SOURCES)

# For Qt creator to find the headers.
FILE(GLOB rummiconsole_HEADERS *.h)

INCLUDE_DIRECTORIES(${rummicore_SOURCE_DIR}/include)

ADD_EXECUTABLE(${PROJECT_NAME} ${rummiconsole_SOURCES} ${rummiconsole_HEADERS})
TARGET_LINK_LIBRARIES(${PROJECT_NAME} rummicore)
INSTALL(TARGETS ${PROJECT_NAME}
  RUNTIME DESTINATION bin
)

