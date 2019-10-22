cmake_minimum_required(VERSION 2.8)

project(homework_2_ip_filter)

add_executable(ip_filter
    ip_filter.cpp
    .travis.yml
)

set_target_properties(ip_filter PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
    COMPILE_OPTIONS "-Wpedantic;-Wall;-Wextra"
)

#add_library(ip_lib
#    ip_class.cpp
#)

#add_executable(Tests
#    "test.cpp"
#)

#find_package(Boost COMPONENTS unit_test_framework REQUIRED)
#set_target_properties(Tests PROPERTIES
#    COMPILE_DEFINITIONS BOOST_TEST_DYN_LINK
#    INCLUDE_DIRECTORIES ${Boost_INCLUDE_DIR}
#)

#target_link_libraries(${PROJECT_NAME}
#    ${ip_lib}
#)

#target_link_libraries(Tests
#    ${Boost_LIBRARIES}
#    ${ip_lib}
#)

#enable_testing()

#add_test(helloworld_tests test_version)

#настройка создания пакета
install(TARGETS ip_filter RUNTIME DESTINATION bin)
set(CPACK_GENERATOR DEB)
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")
set(CPACK_PACKAGE_CONTACT my_mail@some_mail.com)
set(CPACK_DEBIAN_PACKAGE_SHLIBDEPS ON)
include(CPack)
