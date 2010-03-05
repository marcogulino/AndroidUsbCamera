Build instructions:
- Checkout project (well, if you're reading this file, probably you already
  did...).
- create a build directory (can be in any place, let's assume it's in
  SOURCE_DIR/build):
-- cd <SOURCE_DIR>; mkdir build

- configure the project with cmake:
-- cd build; cmake <SOURCE_DIR> (i.e.: "cmake .." in this case)
- build the project:
-- make
Optional:
- Run the tests:
-- make test (or just type ctest)

