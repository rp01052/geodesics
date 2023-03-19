# geodesics
Testing geodesics algorithms in CGAL. After cloning this repository, get the submodule [googletest](https://github.com/google/googletest) by
```shell
cd geodesics/
git submodule update --init
```
There are three target that can be built: geodesics_run, geodesics_lib and geodesics_test. To built all of those, execute
```shell
mkdir build
cd build/
cmake ..
make
```
The executables can be run using
```shell
cd src/
./geodesics_run
```
and
```shell
cd test/
./geodesics_test
```
