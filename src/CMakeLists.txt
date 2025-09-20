
add_subdirectory(utils)
add_subdirectory(network)

add_executable(main main.cc)

target_include_directories(main 
    PRIVATE 
        ${CMAKE_CURRENT_SOURCE_DIR}/include/network
        ${CMAKE_CURRENT_SOURCE_DIR}/include/utils
)

target_link_libraries(main 
    PRIVATE 
        network_shared
)
