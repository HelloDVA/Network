
add_subdirectory(network)
add_subdirectory(utils)
add_subdirectory(server)

add_executable(main main.cc)

target_include_directories(main PRIVATE ./network ./utils ./server)

target_link_libraries(main network utils server)
