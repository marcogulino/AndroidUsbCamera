ENABLE_TESTING()
project(AndroidUsbCamera)
cmake_minimum_required(VERSION 2.6)
find_package(Qt4 REQUIRED)

include_directories(${QT_INCLUDES} ${CMAKE_CURRENT_BINARY_DIR})

set(AndroidUsbCamera_SRCS AndroidUsbCamera.cpp main.cpp src/databridge.cpp)
qt4_automoc(${AndroidUsbCamera_SRCS})
add_executable(AndroidUsbCamera ${AndroidUsbCamera_SRCS})
target_link_libraries(AndroidUsbCamera -lavformat -lswscale ${QT_QTCORE_LIBRARY} ${QT_QTNETWORK_LIBRARY} )

add_subdirectory(test)
ADD_TEST("Socket Connector Integration Test" "test/SocketConnectorIntegrationTest")