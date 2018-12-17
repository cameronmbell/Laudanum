# Based on a file which is Copyright (c) 2015 Andrew Kelley
# Used under MIT licensed.
# See http://opensource.org/licenses/MIT

# Sets:
# GLFW3_FOUND
# GLFW3_INCLUDE_DIR
# GLFW3_LIBRARY

set(GLFW3_SEARCH_PATHS ${DEPENDENCIES_ROOT})

find_path(GLFW3_INCLUDE_DIR 
    NAMES GLFW/glfw3.h 
    PATHS ${GLFW3_SEARCH_PATHS} 
    PATH_SUFFIXES include)

find_library(GLFW3_LIBRARY 
    NAMES glfw3
    PATHS ${GLFW3_SEARCH_PATHS}
    PATH_SUFFIXES lib)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(GLFW DEFAULT_MSG GLFW3_LIBRARY GLFW3_INCLUDE_DIR)

mark_as_advanced(GLFW3_INCLUDE_DIR GLFW3_LIBRARY)