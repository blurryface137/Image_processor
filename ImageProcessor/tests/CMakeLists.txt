project(ImageProcessor)
enable_testing()

find_package(Boost COMPONENTS filesystem system unit_test_framework REQUIRED)

include_directories(${Boost_INCLUDE_DIRS})

add_executable(ip_test Test.cpp ${SOURCES})
target_link_libraries(ip_test
                      ${Boost_FILESYSTEM_LIBRARY}
                      ${Boost_SYSTEM_LIBRARY}
                      ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}
                      )
                      
add_test(NAME CropFilterTest COMMAND ip_test)
add_test(NAME GrayScaleFilterTest COMMAND ip_test)