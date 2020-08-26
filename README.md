# CodeMore

![Build Status: Windows](https://ci.appveyor.com/api/projects/status/github/ivorob/CodeMore?branch=master&svg=true)

## Build on windows

Go to sources directory

```sh
mkdir build
cd build
cmake -G "NMake Makefiles" .. -DCMAKE_PREFIX_PATH=path_to_compiled_qt_libraries
cmake --build .
windeployqt --qmldir path_to_qml_dir CodeMore.exe
```

## Build tests

To build tests use the following commad in build directory:

```sh
cmake . -DBUILD_TESTING=ON
```

To disable build tests use the following command in build directory:

```sh
cmake . -DBUILD_TESTING=OFF
```
