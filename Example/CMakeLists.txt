project(Example)				

set(SOURCE_EXE main.cc)			

include_directories(../include)			

add_executable(example ${SOURCE_EXE})	
if(WIN32)
  target_link_libraries(example wsock32 ws2_32)
endif()

