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
- Run the tests:
-- make test (or just type ctest)

