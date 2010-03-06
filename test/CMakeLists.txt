set(SocketConnectorTest_SRCS socketconnectortest.cpp )
set(FramesDataExtractorTest_SRCS framesdataextractortest.cpp )

qt4_automoc(${SocketConnectorTest_SRCS})
qt4_automoc(${FramesDataExtractorTest_SRCS})

include_directories(${QT_INCLUDES} ${CMAKE_CURRENT_BINARY_DIR} )

add_executable(SocketConnectorTest ${SocketConnectorTest_SRCS})
add_executable(FramesDataExtractorTest ${FramesDataExtractorTest_SRCS})

target_link_libraries(SocketConnectorTest AndroidUsbCameraStaticLib ${QT_QTCORE_LIBRARY} ${QT_QTTEST_LIBRARY} -lgmock -lgtest )
target_link_libraries(FramesDataExtractorTest AndroidUsbCameraStaticLib ${QT_QTCORE_LIBRARY} ${QT_QTTEST_LIBRARY} -lgmock -lgtest )
