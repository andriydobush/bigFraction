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
    
    fraction f1 (1, 2);
    fraction f2 (1, 3);
    fraction f3 (5, 3);
    fraction fres2;
    fraction fres;
    /* Print fraction 1 */
    cout << "f1: " << f1 << std::endl;

    /* Print fraction 2 */
    cout << "f2: " << f2 << std::endl;

    /* Print fraction 3 */
    cout << "f3: " << f3 << std::endl;

    /* Print fraction 3 */
    cout << "fres: Init state: " << fres << std::endl;
    /* Add two fractions */
    fres = f3+f2;
    cout << "fres = f2 + f3: " << fres << " = " << f2 << " + " << f3 << std::endl;
    fres2 = fres + f1;
    cout << "fres2 = fres + f1: " << fres2 << " = " << fres << " + " << f1 << std::endl;;

    /* Fraction from string that does not fit into int32 */
    fraction f1_str ("10000000000000000", "21453139344136567");
    fraction f2_str ("2", "4");
    fraction f3_str ("10000000000000000", "21453139344136566");
    fraction fres_str = f1_str * f2_str;
    std::cout <<f1_str << " * " << f2_str << " = " << fres_str << std::endl;
    
    /* fraction multiplication to int */
    fres_str = f2_str * 2;
    cout << "1/2 * 2 = " << fres_str << std::endl;

    /* fraction comparing */
    // f1 = 1/2, f2 = 1/3
    if (f1 > f2)
    {
        std::cout<< "Compare correct f1 > f2: " << f1 << " > " << f2 << std::endl;
    }
    else
    {
        std::cout<< "Compare not correct " << std::endl;
    }

    // f1_str = 10000000000000000 / 21453139344136567
    // f3_str = 10000000000000000 / 21453139344136566
    if (f1_str < f3_str)
    {
        std::cout<< "Compare correct f1_str < f3_str: " << std::endl << f1_str << " < " << f3_str << std::endl;
        std::cout<< "Note f3_str is reduced to lower terms" << std::endl;
    }

    else
    {
        std::cout<< "Compare not correct " << std::endl;
    }
    return 0;
}
