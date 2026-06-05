cmake_minimum_required (VERSION 4.0)

# MSVC hot reload if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

# Uncomment the line below to specify Git executable location if necessary
#set(GIT_EXECUTABLE "C:/Program Files/Git/bin/git.exe") 


project ("acx" LANGUAGES CXX)
# Shortcut to source directory
set(SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src")
# All executables as a list
set(SOURCES
  "${SRC_DIR}/source.cpp"
)


add_library(acx INTERFACE)
target_include_directories(acx INTERFACE "${SRC_DIR}")
set_target_properties(acx PROPERTIES LINKER_LANGUAGE CXX)
if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET acx PROPERTY CXX_STANDARD 20)
endif()


add_executable (acx_exe ${SOURCES})
set_target_properties(acx_exe PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(acx_exe PRIVATE acx)
if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET acx_exe PROPERTY CXX_STANDARD 20)
endif()
