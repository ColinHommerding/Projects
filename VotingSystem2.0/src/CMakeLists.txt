set(BINARY ${CMAKE_PROJECT_NAME})

file(GLOB SOURCES LIST_DIRECTORIES true *.h *.cpp *.cc)

set(SOURCES ${SOURCES})

add_executable(${BINARY} ${SOURCES})

add_library(${BINARY}_lib STATIC ${SOURCES})
