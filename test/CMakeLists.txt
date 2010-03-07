include_directories(${QT_INCLUDES} ${CMAKE_CURRENT_BINARY_DIR} )

set(SocketConnectorTest_SRCS socketconnectortest.cpp )
qt4_automoc(${SocketConnectorTest_SRCS})
add_executable(SocketConnectorTest ${SocketConnectorTest_SRCS})
target_link_libraries(SocketConnectorTest AndroidUsbCameraStaticLib ${QT_QTCORE_LIBRARY} ${QT_QTTEST_LIBRARY} -lgmock -lgtest )

set(FramesDataExtractorTest_SRCS framesdataextractortest.cpp )
qt4_automoc(${FramesDataExtractorTest_SRCS})
add_executable(FramesDataExtractorTest ${FramesDataExtractorTest_SRCS})
target_link_libraries(FramesDataExtractorTest AndroidUsbCameraStaticLib ${QT_QTCORE_LIBRARY} ${QT_QTTEST_LIBRARY} -lgmock -lgtest )

set(FramesCreatorTest_SRCS framescreatortest.cpp )
qt4_automoc(${FramesCreatorTest_SRCS})
add_executable(FramesCreatorTest ${FramesCreatorTest_SRCS})
target_link_libraries(FramesCreatorTest AndroidUsbCameraStaticLib ${QT_QTCORE_LIBRARY} ${QT_QTTEST_LIBRARY} -lgmock -lgtest )


set(FramesFactoryTest_SRCS  framesfactorytest.cpp )
qt4_automoc(${FramesFactoryTest_SRCS})
add_executable(FramesFactoryTest ${FramesFactoryTest_SRCS})
target_link_libraries(FramesFactoryTest AndroidUsbCameraStaticLib ${QT_QTCORE_LIBRARY} ${QT_QTTEST_LIBRARY} -lgmock -lgtest )

