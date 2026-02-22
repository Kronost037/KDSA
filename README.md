# KDSA
### (GCC/CLANG only)
An experimental Data Structure and Algorithms Library.
It uses advanced debug instrumentation and error logging to help with reliable development and quick debugging.

## Build
```terminal
$ make
```
## Create a compilation database (for clangd / editors):
```terminal
$ bear -- make
```
## Wipe state clean
```terminal
$ make clean
```

## Usage
Write yourfile.c in the root of the library and compile:
```terminal
$ gcc -I ./include/yourfile.c -L./lib -llist -Wl,-rpath,'$$ORIGIN/lib' -o yourfile 
```
Otherwise, save the library in your system to use directly:
### Linux:
```terminal
$ sudo cp include/list.h /usr/local/include/
$ sudo cp lib/liblist.so /usr/local/lib/
```
Then compile from anywhere:
```terminal
$ gcc yourfile.c -o yourfile -llist
```
