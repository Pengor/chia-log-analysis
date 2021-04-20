# Chia Log Analysis
[![Build](https://github.com/Pengor/chia-log-analysis/actions/workflows/build.yml/badge.svg)](https://github.com/Pengor/chia-log-analysis/actions/workflows/build.yml)
[![Total alerts](https://img.shields.io/lgtm/alerts/g/Pengor/chia-log-analysis.svg?logo=lgtm&logoWidth=18)](https://lgtm.com/projects/g/Pengor/chia-log-analysis/alerts/)
[![Language grade: C/C++](https://img.shields.io/lgtm/grade/cpp/g/Pengor/chia-log-analysis.svg?logo=lgtm&logoWidth=18)](https://lgtm.com/projects/g/Pengor/chia-log-analysis/context:cpp)

Parses through Chia plotter log files and plops all the juicy details into a CSV file!

## Build
See below for instructions if you prefer to build the application yourself. Otherwise feel free to simply download the binaries from the [latest release](https://github.com/Pengor/chia-log-analysis/releases/latest).

### Build Prerequisites
* CMake
* C++ compiler

### Build Instructions
`git clone https://github.com/Pengor/chia-log-analysis.git`

`cd chia-log-analysis`

`cmake -E make_directory ./build`

`cmake -S src -B build`

`cmake --build build`

## Run
Navigate to the location of the built or downloaded binary and run one of the following options.

#### Guided prompts:

`./chia-log-analysis`

#### Command-line arguments:

`./chia-log-analysis -i <logfile directory> -o <output filename>`

where `<logfile directory>` is the path to your chia plotter logs and `<output filename>` is the path to the .csv file you want to save (file extension should be specified by the user).

### Note for Windows
If the application does not you may need to install the [Microsoft Visual C++ Redistributable for Visual Studio 2019](https://visualstudio.microsoft.com/downloads/#microsoft-visual-c-redistributable-for-visual-studio-2019)

## About

### What info does it parse?
For each file it parses as much as it can find of the following (I imagine I'm not the only one who's had a plot interrupted):
* Plot size 
* Buffer size 
* Buckets 
* Threads 
* Stripe size 
* Start date 
* Phase 1 duration 
* Phase 2 duration 
* Phase 3 duration 
* Phase 4 duration 
* Total time 
* Plot filename

### Why does this exist?
I started doing some chia plotting and wanted to compare the performance of different settings used during plotting. I imagine there are other tools out there that do the same thing as this one, but it gave me an excuse to do some more C++ learning outside my typical ecosystem. If you find any bugs or want to see a feature added please feel free to open a new _Issue_.
