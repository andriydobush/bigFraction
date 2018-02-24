# C++ Big Frations

C++ Big Frations using big integer gmp lirary. 
Features:
- Reduce fraction to lowest terms
- Use gmp big integers only if required.
- Use result prediction to avoid reduntant use of gmp
- Use commont integer where it is possible for faster calculations
- Sign is carried by denumerator
- is not provided as library.

### Prerequisites

Fraction library requires gmp library.


## Getting Started

Example of using is at /fractions/fractionUsage.cpp

Linux (tested on Ubuntu16.04):
1. Install gmp library
$ sudo apt-get install  libgmp3-dev
2. build project
$ make
3. Run application
$ ./fractionUsage

Windows:
Available for windows.
Worked with VS 2017/2015 and mpir library.
