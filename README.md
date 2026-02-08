# KDSA

An experimental Data Structure and Algorithms Library.
It uses advanced debug instrumentation and error logging to help with reliable development and quick debugging.

## Build
```bash
make
```
## Create a compilation database (for clangd / editors):
```
bear -- make
```
## Wipe state clean
```bash
make clean
```

## Usage
Write yourfile.c in the root of the library and compile:
```bash
gcc -I ./include/yourfile.c -L./lib -llist -Wl,-rpath,'$$ORIGIN/lib' -o yourfile 
```
Otherwise, save the library in your system to use directly:
### Linux:
```bash
sudo cp include/list.h /usr/local/include/
sudo cp lib/liblist.so /usr/local/lib/
```
Then compile from anywhere:
```bash
gcc yourfile.c -o yourfile -llist
```
