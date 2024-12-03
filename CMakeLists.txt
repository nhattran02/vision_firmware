# The following lines of boilerplate have to be in your project's
# CMakeLists in this exact order for cmake to work correctly
cmake_minimum_required(VERSION 3.5)

set(EXTRA_COMPONENT_DIRS ../../components aws_libraries/backoffAlgorithm aws_libraries/coreMQTT aws_libraries/coreJSON aws_libraries/common/posix_compat)


add_compile_options(-fdiagnostics-color=always)
include($ENV{IDF_PATH}/tools/cmake/project.cmake)
project(human_face_detection_web)


target_add_binary_data(${CMAKE_PROJECT_NAME}.elf "aws_package/root_cert_auth.crt" TEXT)
target_add_binary_data(${CMAKE_PROJECT_NAME}.elf "aws_package/client.crt" TEXT)
target_add_binary_data(${CMAKE_PROJECT_NAME}.elf "aws_package/client.key" TEXT)
