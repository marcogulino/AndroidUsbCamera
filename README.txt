Prerequisites: 
- git
- QT framework (any version above 4.2 should work)
Only for unit testing(developers):
- google mock framework: http://code.google.com/p/googlemock/

Build instructions:
- Checkout project
-- git clone git://github.com/marcogulino/AndroidUsbCamera.git
OR
-- git clone http://github.com/marcogulino/AndroidUsbCamera.git

- create a build directory (can be in any place, let's assume it's in
  AndroidUsbCamera/build):
-- cd AndroidUsbCamera; mkdir build

- configure the project with cmake:
-- cd build; cmake ../
- build the project:
-- make
Optional:
- Run the tests (build only if CMAKE_BUILD_TYPE is debug):
-- make test (or just type ctest)

to have a better output with failing tests, setting the environment variable:
- CTEST_OUTPUT_ON_FAILURE=1
can greatly help.

Usage:
- Load vloopback module (sources and instructions: http://www.lavrsen.dk/twiki/bin/view/Motion/VideoFourLinuxLoopbackDevice)
-- modprobe vloopback
- Find the video output device
-- dmesg | grep vloopback
-- look for a string like "[vloopback_init] : Loopback 0 registered, input: video0, output: video1
-- in this case, /dev/video0 is your video output device
- load AndroidUsbCamera application:
-- AndroidUsbCamera /dev/video0


