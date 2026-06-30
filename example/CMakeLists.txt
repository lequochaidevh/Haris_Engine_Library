cmake_minimum_required(VERSION 3.16)
project(SandboxApp VERSION 0.1)

# Todo: config at Producer
# Set global variable for project.
set(RELEASE_LIB_VERSION "v000")
set(RELEASE_LIB_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../release/${RELEASE_LIB_VERSION}")

if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU" OR CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
   set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-rtti") # optimize memory
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
   set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /GR-")
endif()

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 17)

file(GLOB_RECURSE SRC_FILES ${CMAKE_CURRENT_SOURCE_DIR}/SandboxApp/*.cpp CMAKE_CONFIGURE_DEPENDS)
add_executable(${PROJECT_NAME} ${SRC_FILES})

find_package(fmt CONFIG REQUIRED)

function(find_and_define_path TARGET_NAME MACRO_NAME SEARCH_PATTERN)
    # Find with file name
    file(GLOB_RECURSE FOUND_FILES "${SEARCH_PATTERN}")
    
    if(FOUND_FILES)
        # Get First
        list(GET FOUND_FILES 0 FILE_PATH)
        
        message(STATUS "[${TARGET_NAME}] Found ${MACRO_NAME}: ${FILE_PATH}")
        
        # Declare macro for C++ (Note: Need "\" to C++ know it is string)
        target_compile_definitions(${TARGET_NAME} PRIVATE ${MACRO_NAME}="${FILE_PATH}")
    else()
        message(WARNING "[${TARGET_NAME}] Could not find file for pattern: ${SEARCH_PATTERN}")
    endif()
endfunction()
# Find Checkerboard.png and declare macro CHECKERBOARD_PATH
find_and_define_path(${PROJECT_NAME} CHECKER_BOARD_PATH "${RELEASE_LIB_PATH}/*/Checkerboard.png")

# Find Checkerboard.png and declare macro HARIS_LOGO_PATH
find_and_define_path(${PROJECT_NAME} HARIS_LOGO_PATH "${RELEASE_LIB_PATH}/*/HarisLogo.png")

# Find Texture.shader and declare macro CHECKERBOARD_PATH
find_and_define_path(${PROJECT_NAME} TEXTURE_SHADER_PATH "${RELEASE_LIB_PATH}/*/Texture.shader")
find_and_define_path(${PROJECT_NAME} BASIC_TEXTURE_SHADER_PATH "${RELEASE_LIB_PATH}/*/BasicTexture.shader")

# Link Test
target_link_libraries(${PROJECT_NAME} PRIVATE 
   ${RELEASE_LIB_PATH}/lib/libHaris.a
   ${RELEASE_LIB_PATH}/lib/libglfw3.a
   ${RELEASE_LIB_PATH}/lib/libglad.a
   fmt::fmt
   pthread
)

find_library(DL_LIBRARY dl)
if(DL_LIBRARY)
    target_link_libraries(${PROJECT_NAME} PRIVATE ${DL_LIBRARY})
    message(STATUS "CMake load dl lib: ${DL_LIBRARY}")
endif()

target_include_directories(${PROJECT_NAME} PRIVATE 
      ${RELEASE_LIB_PATH}/include/Haris
      ${RELEASE_LIB_PATH}/include/Haris/Common
      ${RELEASE_LIB_PATH}/include/Haris/Engine
      ${RELEASE_LIB_PATH}/include/Haris/Event
      ${RELEASE_LIB_PATH}/include/Haris/Window
      ${RELEASE_LIB_PATH}/include/Haris/Vendors/glm
      ${RELEASE_LIB_PATH}/include/Haris/Vendors
      ${CMAKE_CURRENT_SOURCE_DIR}/SandboxApp
      ${CMAKE_SOURCE_DIR}/Engine
)
