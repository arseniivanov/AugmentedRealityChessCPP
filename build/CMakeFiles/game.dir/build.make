# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.18

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
CMAKE_COMMAND = /usr/local/bin/cmake

# The command to remove a file.
RM = /usr/local/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/arseni/projects/Peer_to_peer_AR_Chess

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/arseni/projects/Peer_to_peer_AR_Chess/build

# Include any dependencies generated for this target.
include CMakeFiles/game.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/game.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/game.dir/flags.make

CMakeFiles/game.dir/test/connect.cc.o: CMakeFiles/game.dir/flags.make
CMakeFiles/game.dir/test/connect.cc.o: ../test/connect.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/arseni/projects/Peer_to_peer_AR_Chess/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/game.dir/test/connect.cc.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/game.dir/test/connect.cc.o -c /home/arseni/projects/Peer_to_peer_AR_Chess/test/connect.cc

CMakeFiles/game.dir/test/connect.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/game.dir/test/connect.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/arseni/projects/Peer_to_peer_AR_Chess/test/connect.cc > CMakeFiles/game.dir/test/connect.cc.i

CMakeFiles/game.dir/test/connect.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/game.dir/test/connect.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/arseni/projects/Peer_to_peer_AR_Chess/test/connect.cc -o CMakeFiles/game.dir/test/connect.cc.s

CMakeFiles/game.dir/helpers/glad.c.o: CMakeFiles/game.dir/flags.make
CMakeFiles/game.dir/helpers/glad.c.o: ../helpers/glad.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/arseni/projects/Peer_to_peer_AR_Chess/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/game.dir/helpers/glad.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/game.dir/helpers/glad.c.o -c /home/arseni/projects/Peer_to_peer_AR_Chess/helpers/glad.c

CMakeFiles/game.dir/helpers/glad.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/game.dir/helpers/glad.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/arseni/projects/Peer_to_peer_AR_Chess/helpers/glad.c > CMakeFiles/game.dir/helpers/glad.c.i

CMakeFiles/game.dir/helpers/glad.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/game.dir/helpers/glad.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/arseni/projects/Peer_to_peer_AR_Chess/helpers/glad.c -o CMakeFiles/game.dir/helpers/glad.c.s

CMakeFiles/game.dir/helpers/objloader.cpp.o: CMakeFiles/game.dir/flags.make
CMakeFiles/game.dir/helpers/objloader.cpp.o: ../helpers/objloader.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/arseni/projects/Peer_to_peer_AR_Chess/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/game.dir/helpers/objloader.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/game.dir/helpers/objloader.cpp.o -c /home/arseni/projects/Peer_to_peer_AR_Chess/helpers/objloader.cpp

CMakeFiles/game.dir/helpers/objloader.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/game.dir/helpers/objloader.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/arseni/projects/Peer_to_peer_AR_Chess/helpers/objloader.cpp > CMakeFiles/game.dir/helpers/objloader.cpp.i

CMakeFiles/game.dir/helpers/objloader.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/game.dir/helpers/objloader.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/arseni/projects/Peer_to_peer_AR_Chess/helpers/objloader.cpp -o CMakeFiles/game.dir/helpers/objloader.cpp.s

CMakeFiles/game.dir/helpers/chesstype.cc.o: CMakeFiles/game.dir/flags.make
CMakeFiles/game.dir/helpers/chesstype.cc.o: ../helpers/chesstype.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/arseni/projects/Peer_to_peer_AR_Chess/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/game.dir/helpers/chesstype.cc.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/game.dir/helpers/chesstype.cc.o -c /home/arseni/projects/Peer_to_peer_AR_Chess/helpers/chesstype.cc

CMakeFiles/game.dir/helpers/chesstype.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/game.dir/helpers/chesstype.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/arseni/projects/Peer_to_peer_AR_Chess/helpers/chesstype.cc > CMakeFiles/game.dir/helpers/chesstype.cc.i

CMakeFiles/game.dir/helpers/chesstype.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/game.dir/helpers/chesstype.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/arseni/projects/Peer_to_peer_AR_Chess/helpers/chesstype.cc -o CMakeFiles/game.dir/helpers/chesstype.cc.s

CMakeFiles/game.dir/helpers/chesspiece.cc.o: CMakeFiles/game.dir/flags.make
CMakeFiles/game.dir/helpers/chesspiece.cc.o: ../helpers/chesspiece.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/arseni/projects/Peer_to_peer_AR_Chess/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/game.dir/helpers/chesspiece.cc.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/game.dir/helpers/chesspiece.cc.o -c /home/arseni/projects/Peer_to_peer_AR_Chess/helpers/chesspiece.cc

CMakeFiles/game.dir/helpers/chesspiece.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/game.dir/helpers/chesspiece.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/arseni/projects/Peer_to_peer_AR_Chess/helpers/chesspiece.cc > CMakeFiles/game.dir/helpers/chesspiece.cc.i

CMakeFiles/game.dir/helpers/chesspiece.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/game.dir/helpers/chesspiece.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/arseni/projects/Peer_to_peer_AR_Chess/helpers/chesspiece.cc -o CMakeFiles/game.dir/helpers/chesspiece.cc.s

CMakeFiles/game.dir/connection.cc.o: CMakeFiles/game.dir/flags.make
CMakeFiles/game.dir/connection.cc.o: ../connection.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/arseni/projects/Peer_to_peer_AR_Chess/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/game.dir/connection.cc.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/game.dir/connection.cc.o -c /home/arseni/projects/Peer_to_peer_AR_Chess/connection.cc

CMakeFiles/game.dir/connection.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/game.dir/connection.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/arseni/projects/Peer_to_peer_AR_Chess/connection.cc > CMakeFiles/game.dir/connection.cc.i

CMakeFiles/game.dir/connection.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/game.dir/connection.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/arseni/projects/Peer_to_peer_AR_Chess/connection.cc -o CMakeFiles/game.dir/connection.cc.s

CMakeFiles/game.dir/server.cc.o: CMakeFiles/game.dir/flags.make
CMakeFiles/game.dir/server.cc.o: ../server.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/arseni/projects/Peer_to_peer_AR_Chess/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/game.dir/server.cc.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/game.dir/server.cc.o -c /home/arseni/projects/Peer_to_peer_AR_Chess/server.cc

CMakeFiles/game.dir/server.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/game.dir/server.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/arseni/projects/Peer_to_peer_AR_Chess/server.cc > CMakeFiles/game.dir/server.cc.i

CMakeFiles/game.dir/server.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/game.dir/server.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/arseni/projects/Peer_to_peer_AR_Chess/server.cc -o CMakeFiles/game.dir/server.cc.s

# Object files for target game
game_OBJECTS = \
"CMakeFiles/game.dir/test/connect.cc.o" \
"CMakeFiles/game.dir/helpers/glad.c.o" \
"CMakeFiles/game.dir/helpers/objloader.cpp.o" \
"CMakeFiles/game.dir/helpers/chesstype.cc.o" \
"CMakeFiles/game.dir/helpers/chesspiece.cc.o" \
"CMakeFiles/game.dir/connection.cc.o" \
"CMakeFiles/game.dir/server.cc.o"

# External object files for target game
game_EXTERNAL_OBJECTS =

game: CMakeFiles/game.dir/test/connect.cc.o
game: CMakeFiles/game.dir/helpers/glad.c.o
game: CMakeFiles/game.dir/helpers/objloader.cpp.o
game: CMakeFiles/game.dir/helpers/chesstype.cc.o
game: CMakeFiles/game.dir/helpers/chesspiece.cc.o
game: CMakeFiles/game.dir/connection.cc.o
game: CMakeFiles/game.dir/server.cc.o
game: CMakeFiles/game.dir/build.make
game: /usr/local/lib/libopencv_gapi.so.4.5.2
game: /usr/local/lib/libopencv_stitching.so.4.5.2
game: /usr/local/lib/libopencv_aruco.so.4.5.2
game: /usr/local/lib/libopencv_barcode.so.4.5.2
game: /usr/local/lib/libopencv_bgsegm.so.4.5.2
game: /usr/local/lib/libopencv_bioinspired.so.4.5.2
game: /usr/local/lib/libopencv_ccalib.so.4.5.2
game: /usr/local/lib/libopencv_dnn_objdetect.so.4.5.2
game: /usr/local/lib/libopencv_dnn_superres.so.4.5.2
game: /usr/local/lib/libopencv_dpm.so.4.5.2
game: /usr/local/lib/libopencv_face.so.4.5.2
game: /usr/local/lib/libopencv_freetype.so.4.5.2
game: /usr/local/lib/libopencv_fuzzy.so.4.5.2
game: /usr/local/lib/libopencv_hfs.so.4.5.2
game: /usr/local/lib/libopencv_img_hash.so.4.5.2
game: /usr/local/lib/libopencv_intensity_transform.so.4.5.2
game: /usr/local/lib/libopencv_line_descriptor.so.4.5.2
game: /usr/local/lib/libopencv_mcc.so.4.5.2
game: /usr/local/lib/libopencv_quality.so.4.5.2
game: /usr/local/lib/libopencv_rapid.so.4.5.2
game: /usr/local/lib/libopencv_reg.so.4.5.2
game: /usr/local/lib/libopencv_rgbd.so.4.5.2
game: /usr/local/lib/libopencv_saliency.so.4.5.2
game: /usr/local/lib/libopencv_stereo.so.4.5.2
game: /usr/local/lib/libopencv_structured_light.so.4.5.2
game: /usr/local/lib/libopencv_superres.so.4.5.2
game: /usr/local/lib/libopencv_surface_matching.so.4.5.2
game: /usr/local/lib/libopencv_tracking.so.4.5.2
game: /usr/local/lib/libopencv_videostab.so.4.5.2
game: /usr/local/lib/libopencv_wechat_qrcode.so.4.5.2
game: /usr/local/lib/libopencv_xfeatures2d.so.4.5.2
game: /usr/local/lib/libopencv_xobjdetect.so.4.5.2
game: /usr/local/lib/libopencv_xphoto.so.4.5.2
game: /usr/lib/x86_64-linux-gnu/libglfw.so.3.3
game: /usr/local/lib/libopencv_shape.so.4.5.2
game: /usr/local/lib/libopencv_highgui.so.4.5.2
game: /usr/local/lib/libopencv_datasets.so.4.5.2
game: /usr/local/lib/libopencv_plot.so.4.5.2
game: /usr/local/lib/libopencv_text.so.4.5.2
game: /usr/local/lib/libopencv_ml.so.4.5.2
game: /usr/local/lib/libopencv_phase_unwrapping.so.4.5.2
game: /usr/local/lib/libopencv_optflow.so.4.5.2
game: /usr/local/lib/libopencv_ximgproc.so.4.5.2
game: /usr/local/lib/libopencv_video.so.4.5.2
game: /usr/local/lib/libopencv_videoio.so.4.5.2
game: /usr/local/lib/libopencv_dnn.so.4.5.2
game: /usr/local/lib/libopencv_imgcodecs.so.4.5.2
game: /usr/local/lib/libopencv_objdetect.so.4.5.2
game: /usr/local/lib/libopencv_calib3d.so.4.5.2
game: /usr/local/lib/libopencv_features2d.so.4.5.2
game: /usr/local/lib/libopencv_flann.so.4.5.2
game: /usr/local/lib/libopencv_photo.so.4.5.2
game: /usr/local/lib/libopencv_imgproc.so.4.5.2
game: /usr/local/lib/libopencv_core.so.4.5.2
game: CMakeFiles/game.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/arseni/projects/Peer_to_peer_AR_Chess/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Linking CXX executable game"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/game.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/game.dir/build: game

.PHONY : CMakeFiles/game.dir/build

CMakeFiles/game.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/game.dir/cmake_clean.cmake
.PHONY : CMakeFiles/game.dir/clean

CMakeFiles/game.dir/depend:
	cd /home/arseni/projects/Peer_to_peer_AR_Chess/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/arseni/projects/Peer_to_peer_AR_Chess /home/arseni/projects/Peer_to_peer_AR_Chess /home/arseni/projects/Peer_to_peer_AR_Chess/build /home/arseni/projects/Peer_to_peer_AR_Chess/build /home/arseni/projects/Peer_to_peer_AR_Chess/build/CMakeFiles/game.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/game.dir/depend

