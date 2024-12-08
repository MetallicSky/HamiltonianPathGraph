# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "100VerticesGraph_autogen"
  "CMakeFiles\\100VerticesGraph_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\100VerticesGraph_autogen.dir\\ParseCache.txt"
  )
endif()
