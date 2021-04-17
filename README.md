# Chia Log Analysis
[![CMake](https://github.com/Pengor/chia-log-analysis/actions/workflows/cmake.yml/badge.svg)](https://github.com/Pengor/chia-log-analysis/actions/workflows/cmake.yml)
[![Total alerts](https://img.shields.io/lgtm/alerts/g/Pengor/chia-log-analysis.svg?logo=lgtm&logoWidth=18)](https://lgtm.com/projects/g/Pengor/chia-log-analysis/alerts/)
[![Language grade: C/C++](https://img.shields.io/lgtm/grade/cpp/g/Pengor/chia-log-analysis.svg?logo=lgtm&logoWidth=18)](https://lgtm.com/projects/g/Pengor/chia-log-analysis/context:cpp)

Parses through Chia plotter log files and plops all the juicy details into a CSV file!

### Prerequisites
* CMake
* C++ compiler (I used GCC)

### Build Instructions
`git clone https://github.com/Pengor/chia-log-analysis.git`

`cd chia-log-analysis`

`cmake -E make_directory ./build`

`cmake -S src -B build`

`cmake --build build`

### Run
Guided prompts:

`./build/chia-log-analysis`

or command-line arguments:

`./build/chia-log-analysis -i <logfile directory> -o <output filename>`

where `<logfile directory>` is the path to your chia plotter logs and `<output filename>` is the path to the .csv file you want to save (file extension should be specified by the user).

### Why does this exist?
I started doing some chia plotting and wanted to compare the performance of different settings used during plotting. I imagine there are other tools out there that do the same thing as this one, but it gave me an excuse to do some more C++ learning outside my typical ecosystem. If you find any bugs or want to see a feature added please feel free to open a new _Issue_.
