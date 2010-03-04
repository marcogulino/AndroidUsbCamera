ENABLE_TESTING()
project(AndroidUsbCamera)
cmake_minimum_required(VERSION 2.6)
find_package(Qt4 REQUIRED)

include_directories(${QT_INCLUDES} ${CMAKE_CURRENT_BINARY_DIR} src)

set(AndroidUsbCamera_SRCS main.cpp )
qt4_automoc(${AndroidUsbCamera_SRCS})
add_executable(AndroidUsbCamera ${AndroidUsbCamera_SRCS})
target_link_libraries(AndroidUsbCamera AndroidUsbCameraStaticLib -lavformat -lswscale ${QT_QTCORE_LIBRARY} ${QT_QTNETWORK_LIBRARY} )

add_subdirectory(src)
add_subdirectory(test)
ADD_TEST("SocketConnectorTest" "${CMAKE_CURRENT_BINARY_DIR}/test/SocketConnectorTest")