include_directories(${QT_INCLUDES} ${CMAKE_CURRENT_BINARY_DIR})
set(AndroidUsbCameraStaticLib_SRCS framesfactory.cpp frame.cpp framescreator.cpp framesdataextractor.cpp socketconnector.cpp )
qt4_automoc(${AndroidUsbCameraStaticLib_SRCS})
add_library( AndroidUsbCameraStaticLib STATIC ${AndroidUsbCameraStaticLib_SRCS})
target_link_libraries(AndroidUsbCameraStaticLib qtInterfaces_lib -lavformat -lswscale ${QT_QTCORE_LIBRARY} ${QT_QTNETWORK_LIBRARY}  )

add_subdirectory(qtInterfaces)