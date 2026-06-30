#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "Haris::Haris" for configuration "Release"
set_property(TARGET Haris::Haris APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(Haris::Haris PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "CXX"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/libHaris.a"
  )

list(APPEND _IMPORT_CHECK_TARGETS Haris::Haris )
list(APPEND _IMPORT_CHECK_FILES_FOR_Haris::Haris "${_IMPORT_PREFIX}/lib/libHaris.a" )

# Import target "Haris::glad" for configuration "Release"
set_property(TARGET Haris::glad APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(Haris::glad PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "C"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/libglad.a"
  )

list(APPEND _IMPORT_CHECK_TARGETS Haris::glad )
list(APPEND _IMPORT_CHECK_FILES_FOR_Haris::glad "${_IMPORT_PREFIX}/lib/libglad.a" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
