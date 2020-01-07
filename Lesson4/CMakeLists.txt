# CMakeList.txt : CMake project for Chapter4, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Look for boost installation
find_package(Boost 1.65 COMPONENTS filesystem iostreams)
find_package(Threads REQUIRED)

# Add source to this project's executable.
add_executable (binary_search "Exercise18/binary_search.cpp")
set_property (TARGET binary_search PROPERTY CXX_STANDARD 14)

add_executable (merge_sort "Exercise19/merge_sort.cpp") 
set_property (TARGET merge_sort PROPERTY CXX_STANDARD 14)

add_executable (quick_sort "Exercise20/quick_sort.cpp") 
set_property (TARGET quick_sort PROPERTY CXX_STANDARD 14)

add_executable (linear_time_select "Exercise21/linear_time_select.cpp") 
set_property (TARGET linear_time_select PROPERTY CXX_STANDARD 14)

add_executable (transform_accumulate "Exercise22/transform_accumulate.cpp") 
set_property (TARGET transform_accumulate PROPERTY CXX_STANDARD 14)

if(Boost_FOUND)
	add_executable (mapreduce_wordcount "Activity10/mapreduce_wordcount.cpp")
	target_include_directories (mapreduce_wordcount PUBLIC Activity10/mapreduce/include ${Boost_INCLUDE_DIRS})
	set_property (TARGET mapreduce_wordcount PROPERTY CXX_STANDARD 14)
	target_link_libraries (mapreduce_wordcount Boost::filesystem Boost::iostreams Threads::Threads)

	add_executable (mapreduce_primecheck "Exercise23/mapreduce_primecheck.cpp")
	target_include_directories (mapreduce_primecheck PUBLIC Activity10/mapreduce/include ${Boost_INCLUDE_DIRS})
	set_property (TARGET mapreduce_primecheck PROPERTY CXX_STANDARD 14)
	target_link_libraries (mapreduce_primecheck Boost::filesystem Boost::iostreams Threads::Threads)

	add_executable (mapreduce_wordcount_skeleton "Activity10/mapreduce_wordcount_skeleton.cpp")
	target_include_directories (mapreduce_wordcount_skeleton PUBLIC Activity10/mapreduce/include ${Boost_INCLUDE_DIRS})
	set_property (TARGET mapreduce_wordcount_skeleton PROPERTY CXX_STANDARD 14)
	target_link_libraries (mapreduce_wordcount_skeleton Boost::filesystem Boost::iostreams Threads::Threads)
else()
	message("Boost libraries not found! Please install them and try to build again")
endif()

# TODO: Add tests and install targets if needed.
