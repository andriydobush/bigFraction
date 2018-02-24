//============================================================================
// Name        : Fraction_main.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include "fraction.h"
using namespace std;

int main() {
    
    fraction f1 (1,2);
    fraction f2 (1,3);
    fraction f3 (5,3);
    fraction fres2;
    fraction fres;
    /* Print fraction 1 */
    cout << "f1: ";
    f1.printFract();
    cout << endl;

    /* Print fraction 2 */
    cout << "f2: ";
    f2.printFract();
    cout << endl;

    /* Print fraction 3 */
    cout << "f3: ";
    f3.printFract();
    cout << endl;

    /* Print fraction 3 */
    cout << "fres: Init state:"; 
    fres.printFract();
    cout << endl;
    /* Add two fractals */
    fres = f3+f2;
    cout << "fres = f2 + f3: ";
    fres.printFract();
    cout << endl;
    fres2 = fres + f1;
    cout << "fres2 = fres + f1: ";
    fres2.printFract();
    cout << endl;

    /* Fraction from string that does not fit into int32 */
    fraction f1_str ("10000000000000000", "21453139344136567");
    fraction f2_str ("2", "4");

    f1_str.printFract();
    std::cout << std::endl;
    f2_str.printFract();
    std::cout << std::endl;

    fraction fres_str = f1_str * f2_str;

    fres_str.printFract();
    std::cout << std::endl;
    return 0;
}
