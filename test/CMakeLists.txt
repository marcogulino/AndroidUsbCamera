set(SocketConnectorIntegrationTest_SRCS socketconnectorintegrationtest.cpp )
qt4_automoc(${SocketConnectorIntegrationTest_SRCS})
include_directories(${QT_INCLUDES} ${CMAKE_CURRENT_BINARY_DIR})

add_executable(SocketConnectorIntegrationTest ${SocketConnectorIntegrationTest_SRCS})
target_link_libraries(SocketConnectorIntegrationTest ${QT_QTCORE_LIBRARY} ${QT_QTTEST_LIBRARY} )
