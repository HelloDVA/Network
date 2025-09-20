file(GLOB SOURCES "*.cc")

add_library(network_shared SHARED ${SOURCES})

target_include_directories(network_shared
    PUBLIC 
    ${CMAKE_SOURCE_DIR}/include/network
    ${CMAKE_SOURCE_DIR}/include/utils
)

target_link_libraries(network_shared 
    PUBLIC 
        utils_shared
)



