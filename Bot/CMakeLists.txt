project(Bot)				

set(SOURCE_EXE main.cc)			
find_package(Threads REQUIRED)

include_directories(../include)			
include_directories(.)			

add_executable(bot ${SOURCE_EXE})	
target_link_libraries(bot Threads::Threads)
if(WIN32)
  target_link_libraries(bot wsock32 ws2_32)
endif()
