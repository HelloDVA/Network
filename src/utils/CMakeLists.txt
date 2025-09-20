file(GLOB SOURCES "*.cc")

add_library(utils_shared SHARED ${SOURCES})

target_include_directories(utils_shared
    PUBLIC
        ${CMAKE_SOURCE_DIR}/include/utils
)

