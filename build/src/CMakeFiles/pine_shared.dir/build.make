# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.28

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/hello/Documents/Network

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/hello/Documents/Network/build

# Include any dependencies generated for this target.
include src/CMakeFiles/pine_shared.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include src/CMakeFiles/pine_shared.dir/compiler_depend.make

# Include the progress variables for this target.
include src/CMakeFiles/pine_shared.dir/progress.make

# Include the compile flags for this target's objects.
include src/CMakeFiles/pine_shared.dir/flags.make

src/CMakeFiles/pine_shared.dir/Acceptor.cpp.o: src/CMakeFiles/pine_shared.dir/flags.make
src/CMakeFiles/pine_shared.dir/Acceptor.cpp.o: /home/hello/Documents/Network/src/Acceptor.cpp
src/CMakeFiles/pine_shared.dir/Acceptor.cpp.o: src/CMakeFiles/pine_shared.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/hello/Documents/Network/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object src/CMakeFiles/pine_shared.dir/Acceptor.cpp.o"
	cd /home/hello/Documents/Network/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/CMakeFiles/pine_shared.dir/Acceptor.cpp.o -MF CMakeFiles/pine_shared.dir/Acceptor.cpp.o.d -o CMakeFiles/pine_shared.dir/Acceptor.cpp.o -c /home/hello/Documents/Network/src/Acceptor.cpp

src/CMakeFiles/pine_shared.dir/Acceptor.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/pine_shared.dir/Acceptor.cpp.i"
	cd /home/hello/Documents/Network/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/hello/Documents/Network/src/Acceptor.cpp > CMakeFiles/pine_shared.dir/Acceptor.cpp.i

src/CMakeFiles/pine_shared.dir/Acceptor.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/pine_shared.dir/Acceptor.cpp.s"
	cd /home/hello/Documents/Network/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/hello/Documents/Network/src/Acceptor.cpp -o CMakeFiles/pine_shared.dir/Acceptor.cpp.s

src/CMakeFiles/pine_shared.dir/Buffer.cpp.o: src/CMakeFiles/pine_shared.dir/flags.make
src/CMakeFiles/pine_shared.dir/Buffer.cpp.o: /home/hello/Documents/Network/src/Buffer.cpp
src/CMakeFiles/pine_shared.dir/Buffer.cpp.o: src/CMakeFiles/pine_shared.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/hello/Documents/Network/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object src/CMakeFiles/pine_shared.dir/Buffer.cpp.o"
	cd /home/hello/Documents/Network/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/CMakeFiles/pine_shared.dir/Buffer.cpp.o -MF CMakeFiles/pine_shared.dir/Buffer.cpp.o.d -o CMakeFiles/pine_shared.dir/Buffer.cpp.o -c /home/hello/Documents/Network/src/Buffer.cpp

src/CMakeFiles/pine_shared.dir/Buffer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/pine_shared.dir/Buffer.cpp.i"
	cd /home/hello/Documents/Network/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/hello/Documents/Network/src/Buffer.cpp > CMakeFiles/pine_shared.dir/Buffer.cpp.i

src/CMakeFiles/pine_shared.dir/Buffer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/pine_shared.dir/Buffer.cpp.s"
	cd /home/hello/Documents/Network/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/hello/Documents/Network/src/Buffer.cpp -o CMakeFiles/pine_shared.dir/Buffer.cpp.s

src/CMakeFiles/pine_shared.dir/Channel.cpp.o: src/CMakeFiles/pine_shared.dir/flags.make
src/CMakeFiles/pine_shared.dir/Channel.cpp.o: /home/hello/Documents/Network/src/Channel.cpp
src/CMakeFiles/pine_shared.dir/Channel.cpp.o: src/CMakeFiles/pine_shared.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/hello/Documents/Network/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object src/CMakeFiles/pine_shared.dir/Channel.cpp.o"
	cd /home/hello/Documents/Network/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/CMakeFiles/pine_shared.dir/Channel.cpp.o -MF CMakeFiles/pine_shared.dir/Channel.cpp.o.d -o CMakeFiles/pine_shared.dir/Channel.cpp.o -c /home/hello/Documents/Network/src/Channel.cpp

src/CMakeFiles/pine_shared.dir/Channel.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/pine_shared.dir/Channel.cpp.i"
	cd /home/hello/Documents/Network/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/hello/Documents/Network/src/Channel.cpp > CMakeFiles/pine_shared.dir/Channel.cpp.i

src/CMakeFiles/pine_shared.dir/Channel.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/pine_shared.dir/Channel.cpp.s"
	cd /home/hello/Documents/Network/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/hello/Documents/Network/src/Channel.cpp -o CMakeFiles/pine_shared.dir/Channel.cpp.s

src/CMakeFiles/pine_shared.dir/Connection.cpp.o: src/CMakeFiles/pine_shared.dir/flags.make
src/CMakeFiles/pine_shared.dir/Connection.cpp.o: /home/hello/Documents/Network/src/Connection.cpp
src/CMakeFiles/pine_shared.dir/Connection.cpp.o: src/CMakeFiles/pine_shared.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/hello/Documents/Network/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object src/CMakeFiles/pine_shared.dir/Connection.cpp.o"
	cd /home/hello/Documents/Network/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/CMakeFiles/pine_shared.dir/Connection.cpp.o -MF CMakeFiles/pine_shared.dir/Connection.cpp.o.d -o CMakeFiles/pine_shared.dir/Connection.cpp.o -c /home/hello/Documents/Network/src/Connection.cpp

src/CMakeFiles/pine_shared.dir/Connection.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/pine_shared.dir/Connection.cpp.i"
	cd /home/hello/Documents/Network/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/hello/Documents/Network/src/Connection.cpp > CMakeFiles/pine_shared.dir/Connection.cpp.i

src/CMakeFiles/pine_shared.dir/Connection.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/pine_shared.dir/Connection.cpp.s"
	cd /home/hello/Documents/Network/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/hello/Documents/Network/src/Connection.cpp -o CMakeFiles/pine_shared.dir/Connection.cpp.s

src/CMakeFiles/pine_shared.dir/Epoll.cpp.o: src/CMakeFiles/pine_shared.dir/flags.make
src/CMakeFiles/pine_shared.dir/Epoll.cpp.o: /home/hello/Documents/Network/src/Epoll.cpp
src/CMakeFiles/pine_shared.dir/Epoll.cpp.o: src/CMakeFiles/pine_shared.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/hello/Documents/Network/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object src/CMakeFiles/pine_shared.dir/Epoll.cpp.o"
	cd /home/hello/Documents/Network/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/CMakeFiles/pine_shared.dir/Epoll.cpp.o -MF CMakeFiles/pine_shared.dir/Epoll.cpp.o.d -o CMakeFiles/pine_shared.dir/Epoll.cpp.o -c /home/hello/Documents/Network/src/Epoll.cpp

src/CMakeFiles/pine_shared.dir/Epoll.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/pine_shared.dir/Epoll.cpp.i"
	cd /home/hello/Documents/Network/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/hello/Documents/Network/src/Epoll.cpp > CMakeFiles/pine_shared.dir/Epoll.cpp.i

src/CMakeFiles/pine_shared.dir/Epoll.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/pine_shared.dir/Epoll.cpp.s"
	cd /home/hello/Documents/Network/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/hello/Documents/Network/src/Epoll.cpp -o CMakeFiles/pine_shared.dir/Epoll.cpp.s

src/CMakeFiles/pine_shared.dir/EventLoop.cpp.o: src/CMakeFiles/pine_shared.dir/flags.make
src/CMakeFiles/pine_shared.dir/EventLoop.cpp.o: /home/hello/Documents/Network/src/EventLoop.cpp
src/CMakeFiles/pine_shared.dir/EventLoop.cpp.o: src/CMakeFiles/pine_shared.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/hello/Documents/Network/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object src/CMakeFiles/pine_shared.dir/EventLoop.cpp.o"
	cd /home/hello/Documents/Network/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/CMakeFiles/pine_shared.dir/EventLoop.cpp.o -MF CMakeFiles/pine_shared.dir/EventLoop.cpp.o.d -o CMakeFiles/pine_shared.dir/EventLoop.cpp.o -c /home/hello/Documents/Network/src/EventLoop.cpp

src/CMakeFiles/pine_shared.dir/EventLoop.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/pine_shared.dir/EventLoop.cpp.i"
	cd /home/hello/Documents/Network/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/hello/Documents/Network/src/EventLoop.cpp > CMakeFiles/pine_shared.dir/EventLoop.cpp.i

src/CMakeFiles/pine_shared.dir/EventLoop.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/pine_shared.dir/EventLoop.cpp.s"
	cd /home/hello/Documents/Network/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/hello/Documents/Network/src/EventLoop.cpp -o CMakeFiles/pine_shared.dir/EventLoop.cpp.s

src/CMakeFiles/pine_shared.dir/HttpRequest.cpp.o: src/CMakeFiles/pine_shared.dir/flags.make
src/CMakeFiles/pine_shared.dir/HttpRequest.cpp.o: /home/hello/Documents/Network/src/HttpRequest.cpp
src/CMakeFiles/pine_shared.dir/HttpRequest.cpp.o: src/CMakeFiles/pine_shared.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/hello/Documents/Network/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object src/CMakeFiles/pine_shared.dir/HttpRequest.cpp.o"
	cd /home/hello/Documents/Network/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/CMakeFiles/pine_shared.dir/HttpRequest.cpp.o -MF CMakeFiles/pine_shared.dir/HttpRequest.cpp.o.d -o CMakeFiles/pine_shared.dir/HttpRequest.cpp.o -c /home/hello/Documents/Network/src/HttpRequest.cpp

src/CMakeFiles/pine_shared.dir/HttpRequest.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/pine_shared.dir/HttpRequest.cpp.i"
	cd /home/hello/Documents/Network/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/hello/Documents/Network/src/HttpRequest.cpp > CMakeFiles/pine_shared.dir/HttpRequest.cpp.i

src/CMakeFiles/pine_shared.dir/HttpRequest.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/pine_shared.dir/HttpRequest.cpp.s"
	cd /home/hello/Documents/Network/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/hello/Documents/Network/src/HttpRequest.cpp -o CMakeFiles/pine_shared.dir/HttpRequest.cpp.s

src/CMakeFiles/pine_shared.dir/HttpResponse.cpp.o: src/CMakeFiles/pine_shared.dir/flags.make
src/CMakeFiles/pine_shared.dir/HttpResponse.cpp.o: /home/hello/Documents/Network/src/HttpResponse.cpp
src/CMakeFiles/pine_shared.dir/HttpResponse.cpp.o: src/CMakeFiles/pine_shared.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/hello/Documents/Network/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object src/CMakeFiles/pine_shared.dir/HttpResponse.cpp.o"
	cd /home/hello/Documents/Network/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/CMakeFiles/pine_shared.dir/HttpResponse.cpp.o -MF CMakeFiles/pine_shared.dir/HttpResponse.cpp.o.d -o CMakeFiles/pine_shared.dir/HttpResponse.cpp.o -c /home/hello/Documents/Network/src/HttpResponse.cpp

src/CMakeFiles/pine_shared.dir/HttpResponse.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/pine_shared.dir/HttpResponse.cpp.i"
	cd /home/hello/Documents/Network/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/hello/Documents/Network/src/HttpResponse.cpp > CMakeFiles/pine_shared.dir/HttpResponse.cpp.i

src/CMakeFiles/pine_shared.dir/HttpResponse.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/pine_shared.dir/HttpResponse.cpp.s"
	cd /home/hello/Documents/Network/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/hello/Documents/Network/src/HttpResponse.cpp -o CMakeFiles/pine_shared.dir/HttpResponse.cpp.s

src/CMakeFiles/pine_shared.dir/InetAddress.cpp.o: src/CMakeFiles/pine_shared.dir/flags.make
src/CMakeFiles/pine_shared.dir/InetAddress.cpp.o: /home/hello/Documents/Network/src/InetAddress.cpp
src/CMakeFiles/pine_shared.dir/InetAddress.cpp.o: src/CMakeFiles/pine_shared.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/hello/Documents/Network/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building CXX object src/CMakeFiles/pine_shared.dir/InetAddress.cpp.o"
	cd /home/hello/Documents/Network/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/CMakeFiles/pine_shared.dir/InetAddress.cpp.o -MF CMakeFiles/pine_shared.dir/InetAddress.cpp.o.d -o CMakeFiles/pine_shared.dir/InetAddress.cpp.o -c /home/hello/Documents/Network/src/InetAddress.cpp

src/CMakeFiles/pine_shared.dir/InetAddress.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/pine_shared.dir/InetAddress.cpp.i"
	cd /home/hello/Documents/Network/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/hello/Documents/Network/src/InetAddress.cpp > CMakeFiles/pine_shared.dir/InetAddress.cpp.i

src/CMakeFiles/pine_shared.dir/InetAddress.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/pine_shared.dir/InetAddress.cpp.s"
	cd /home/hello/Documents/Network/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/hello/Documents/Network/src/InetAddress.cpp -o CMakeFiles/pine_shared.dir/InetAddress.cpp.s

src/CMakeFiles/pine_shared.dir/Log.cpp.o: src/CMakeFiles/pine_shared.dir/flags.make
src/CMakeFiles/pine_shared.dir/Log.cpp.o: /home/hello/Documents/Network/src/Log.cpp
src/CMakeFiles/pine_shared.dir/Log.cpp.o: src/CMakeFiles/pine_shared.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/hello/Documents/Network/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Building CXX object src/CMakeFiles/pine_shared.dir/Log.cpp.o"
	cd /home/hello/Documents/Network/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/CMakeFiles/pine_shared.dir/Log.cpp.o -MF CMakeFiles/pine_shared.dir/Log.cpp.o.d -o CMakeFiles/pine_shared.dir/Log.cpp.o -c /home/hello/Documents/Network/src/Log.cpp

src/CMakeFiles/pine_shared.dir/Log.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/pine_shared.dir/Log.cpp.i"
	cd /home/hello/Documents/Network/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/hello/Documents/Network/src/Log.cpp > CMakeFiles/pine_shared.dir/Log.cpp.i

src/CMakeFiles/pine_shared.dir/Log.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/pine_shared.dir/Log.cpp.s"
	cd /home/hello/Documents/Network/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/hello/Documents/Network/src/Log.cpp -o CMakeFiles/pine_shared.dir/Log.cpp.s

src/CMakeFiles/pine_shared.dir/Server.cpp.o: src/CMakeFiles/pine_shared.dir/flags.make
src/CMakeFiles/pine_shared.dir/Server.cpp.o: /home/hello/Documents/Network/src/Server.cpp
src/CMakeFiles/pine_shared.dir/Server.cpp.o: src/CMakeFiles/pine_shared.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/hello/Documents/Network/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_11) "Building CXX object src/CMakeFiles/pine_shared.dir/Server.cpp.o"
	cd /home/hello/Documents/Network/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/CMakeFiles/pine_shared.dir/Server.cpp.o -MF CMakeFiles/pine_shared.dir/Server.cpp.o.d -o CMakeFiles/pine_shared.dir/Server.cpp.o -c /home/hello/Documents/Network/src/Server.cpp

src/CMakeFiles/pine_shared.dir/Server.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/pine_shared.dir/Server.cpp.i"
	cd /home/hello/Documents/Network/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/hello/Documents/Network/src/Server.cpp > CMakeFiles/pine_shared.dir/Server.cpp.i

src/CMakeFiles/pine_shared.dir/Server.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/pine_shared.dir/Server.cpp.s"
	cd /home/hello/Documents/Network/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/hello/Documents/Network/src/Server.cpp -o CMakeFiles/pine_shared.dir/Server.cpp.s

src/CMakeFiles/pine_shared.dir/Socket.cpp.o: src/CMakeFiles/pine_shared.dir/flags.make
src/CMakeFiles/pine_shared.dir/Socket.cpp.o: /home/hello/Documents/Network/src/Socket.cpp
src/CMakeFiles/pine_shared.dir/Socket.cpp.o: src/CMakeFiles/pine_shared.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/hello/Documents/Network/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_12) "Building CXX object src/CMakeFiles/pine_shared.dir/Socket.cpp.o"
	cd /home/hello/Documents/Network/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/CMakeFiles/pine_shared.dir/Socket.cpp.o -MF CMakeFiles/pine_shared.dir/Socket.cpp.o.d -o CMakeFiles/pine_shared.dir/Socket.cpp.o -c /home/hello/Documents/Network/src/Socket.cpp

src/CMakeFiles/pine_shared.dir/Socket.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/pine_shared.dir/Socket.cpp.i"
	cd /home/hello/Documents/Network/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/hello/Documents/Network/src/Socket.cpp > CMakeFiles/pine_shared.dir/Socket.cpp.i

src/CMakeFiles/pine_shared.dir/Socket.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/pine_shared.dir/Socket.cpp.s"
	cd /home/hello/Documents/Network/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/hello/Documents/Network/src/Socket.cpp -o CMakeFiles/pine_shared.dir/Socket.cpp.s

src/CMakeFiles/pine_shared.dir/ThreadPool.cpp.o: src/CMakeFiles/pine_shared.dir/flags.make
src/CMakeFiles/pine_shared.dir/ThreadPool.cpp.o: /home/hello/Documents/Network/src/ThreadPool.cpp
src/CMakeFiles/pine_shared.dir/ThreadPool.cpp.o: src/CMakeFiles/pine_shared.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/hello/Documents/Network/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_13) "Building CXX object src/CMakeFiles/pine_shared.dir/ThreadPool.cpp.o"
	cd /home/hello/Documents/Network/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/CMakeFiles/pine_shared.dir/ThreadPool.cpp.o -MF CMakeFiles/pine_shared.dir/ThreadPool.cpp.o.d -o CMakeFiles/pine_shared.dir/ThreadPool.cpp.o -c /home/hello/Documents/Network/src/ThreadPool.cpp

src/CMakeFiles/pine_shared.dir/ThreadPool.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/pine_shared.dir/ThreadPool.cpp.i"
	cd /home/hello/Documents/Network/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/hello/Documents/Network/src/ThreadPool.cpp > CMakeFiles/pine_shared.dir/ThreadPool.cpp.i

src/CMakeFiles/pine_shared.dir/ThreadPool.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/pine_shared.dir/ThreadPool.cpp.s"
	cd /home/hello/Documents/Network/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/hello/Documents/Network/src/ThreadPool.cpp -o CMakeFiles/pine_shared.dir/ThreadPool.cpp.s

# Object files for target pine_shared
pine_shared_OBJECTS = \
"CMakeFiles/pine_shared.dir/Acceptor.cpp.o" \
"CMakeFiles/pine_shared.dir/Buffer.cpp.o" \
"CMakeFiles/pine_shared.dir/Channel.cpp.o" \
"CMakeFiles/pine_shared.dir/Connection.cpp.o" \
"CMakeFiles/pine_shared.dir/Epoll.cpp.o" \
"CMakeFiles/pine_shared.dir/EventLoop.cpp.o" \
"CMakeFiles/pine_shared.dir/HttpRequest.cpp.o" \
"CMakeFiles/pine_shared.dir/HttpResponse.cpp.o" \
"CMakeFiles/pine_shared.dir/InetAddress.cpp.o" \
"CMakeFiles/pine_shared.dir/Log.cpp.o" \
"CMakeFiles/pine_shared.dir/Server.cpp.o" \
"CMakeFiles/pine_shared.dir/Socket.cpp.o" \
"CMakeFiles/pine_shared.dir/ThreadPool.cpp.o"

# External object files for target pine_shared
pine_shared_EXTERNAL_OBJECTS =

src/libpine_shared.so: src/CMakeFiles/pine_shared.dir/Acceptor.cpp.o
src/libpine_shared.so: src/CMakeFiles/pine_shared.dir/Buffer.cpp.o
src/libpine_shared.so: src/CMakeFiles/pine_shared.dir/Channel.cpp.o
src/libpine_shared.so: src/CMakeFiles/pine_shared.dir/Connection.cpp.o
src/libpine_shared.so: src/CMakeFiles/pine_shared.dir/Epoll.cpp.o
src/libpine_shared.so: src/CMakeFiles/pine_shared.dir/EventLoop.cpp.o
src/libpine_shared.so: src/CMakeFiles/pine_shared.dir/HttpRequest.cpp.o
src/libpine_shared.so: src/CMakeFiles/pine_shared.dir/HttpResponse.cpp.o
src/libpine_shared.so: src/CMakeFiles/pine_shared.dir/InetAddress.cpp.o
src/libpine_shared.so: src/CMakeFiles/pine_shared.dir/Log.cpp.o
src/libpine_shared.so: src/CMakeFiles/pine_shared.dir/Server.cpp.o
src/libpine_shared.so: src/CMakeFiles/pine_shared.dir/Socket.cpp.o
src/libpine_shared.so: src/CMakeFiles/pine_shared.dir/ThreadPool.cpp.o
src/libpine_shared.so: src/CMakeFiles/pine_shared.dir/build.make
src/libpine_shared.so: src/CMakeFiles/pine_shared.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/home/hello/Documents/Network/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_14) "Linking CXX shared library libpine_shared.so"
	cd /home/hello/Documents/Network/build/src && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/pine_shared.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/CMakeFiles/pine_shared.dir/build: src/libpine_shared.so
.PHONY : src/CMakeFiles/pine_shared.dir/build

src/CMakeFiles/pine_shared.dir/clean:
	cd /home/hello/Documents/Network/build/src && $(CMAKE_COMMAND) -P CMakeFiles/pine_shared.dir/cmake_clean.cmake
.PHONY : src/CMakeFiles/pine_shared.dir/clean

src/CMakeFiles/pine_shared.dir/depend:
	cd /home/hello/Documents/Network/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/hello/Documents/Network /home/hello/Documents/Network/src /home/hello/Documents/Network/build /home/hello/Documents/Network/build/src /home/hello/Documents/Network/build/src/CMakeFiles/pine_shared.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : src/CMakeFiles/pine_shared.dir/depend

