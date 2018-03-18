# C++ Big Frations

C++ Big Frations using big integer gmp lirary. 
Features:
- Reduce fraction to lowest terms
- Smart switching between usage of gmp library and commom integer.
- Use multiplication result prediction to avoid reduntant use of gmp library.
- Use commont integer where it is possible for faster calculations
- Sign is carried by denumerator
- is not provided as library.

### Prerequisites

Fraction library requires gmp library.


## Getting Started

Example of using is at /fractions/fractionUsage.cpp

#### Linux (tested on Ubuntu16.04):
1. Install gmp library
$ sudo apt-get install  libgmp3-dev
2. build project
$ make
3. Run application
$ ./fractionUsage


#### Windows:
Available for windows.
Worked with VS 2017/2015 and mpir library.
Currently steps are not finalised.
Feel fre to ask if steps for Windows is needed

### Doxygen generation
Ubuntu:
sudo apt-get install doxygen
sudo apt-get install graphviz
doxygen -g fraction.doxygen
doxygen fraction.doxygen
