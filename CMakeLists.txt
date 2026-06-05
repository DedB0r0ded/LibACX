cmake_minimum_required (VERSION 4.0)

# MSVC hot reload if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("LibACX" LANGUAGES CXX)

# Uncomment the line below to specify Git executable location if necessary
#set(GIT_EXECUTABLE "C:/Program Files/Git/bin/git.exe") 


# Shortcut to source directory
set(SRC_DIR "${CMAKE_SOURCE_DIR}/src")

# All executables as a list
set(SOURCES
  "${SRC_DIR}/source.cpp"
)


add_executable (LibACX ${SOURCES})

set_target_properties(LibACX PROPERTIES LINKER_LANGUAGE CXX)

target_include_directories(LibACX PRIVATE ${CMAKE_SOURCE_DIR})
target_include_directories(LibACX PRIVATE ${SRC_DIR})

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET LibACX PROPERTY CXX_STANDARD 20)
endif()
