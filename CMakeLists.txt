cmake_minimum_required(VERSION 3.2)

set(THIS MorpheusMatrix)
if (DEFINED ENV{TRAVIS_BUILD_NUMBER})
    project(${THIS} VERSION 0.0.$ENV{TRAVIS_BUILD_NUMBER})
else()
    project(${THIS} VERSION 0.0.1)
endif()

set(CMAKE_CXX_STANDARD 17)

include_directories(lib)
include_directories(src)

add_executable (Morpheus_Matrix src/main.cpp lib/matrix.h)
set_target_properties(Morpheus_Matrix PROPERTIES CXX_STANDARD_REQUIRED ON)
target_include_directories(Morpheus_Matrix PRIVATE "${CMAKE_BINARY_DIR}")


install(TARGETS Morpheus_Matrix RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")
set(CPACK_PACKAGE_CONTACT example@example.com)

include(CPack)