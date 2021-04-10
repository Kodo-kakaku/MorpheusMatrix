cmake_minimum_required(VERSION 3.17)
project(MorpheusMatrix)

set(THIS MorpheusMatrix)
if (DEFINED ENV{TRAVIS_BUILD_NUMBER})
    project(${THIS} VERSION 0.0.$ENV{TRAVIS_BUILD_NUMBER})
else()
    project(${THIS} VERSION 0.0.1)
endif()

set(CMAKE_CXX_STANDARD 17)
add_executable(MorpheusMatrix_main src/main.cpp lib/matrix.h)

if (MSVC)
    target_compile_options(MorpheusMatrix_main PRIVATE
            /W4
            )
else ()
    target_compile_options(MorpheusMatrix_main PRIVATE
            -Wall -Wextra -pedantic -Werror
            )
endif()


install(TARGETS MorpheusMatrix_main RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT example@example.com)

include(CPack)