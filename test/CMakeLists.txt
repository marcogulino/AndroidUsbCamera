set(SocketConnectorTest_SRCS socketconnectortest.cpp )
qt4_automoc(${SocketConnectorTest_SRCS})
include_directories(${QT_INCLUDES} ${CMAKE_CURRENT_BINARY_DIR} )

add_executable(SocketConnectorTest ${SocketConnectorTest_SRCS})
target_link_libraries(SocketConnectorTest AndroidUsbCameraStaticLib ${QT_QTCORE_LIBRARY} ${QT_QTTEST_LIBRARY} -lgmock -lgtest )
