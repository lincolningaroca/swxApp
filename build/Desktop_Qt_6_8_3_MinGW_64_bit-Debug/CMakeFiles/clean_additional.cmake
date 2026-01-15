# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\xxxApp_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\xxxApp_autogen.dir\\ParseCache.txt"
  "xxxApp_autogen"
  )
endif()
