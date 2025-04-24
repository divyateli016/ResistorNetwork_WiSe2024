// Standard (system) header files
#include <iostream>
#include <stdlib.h>
#include <fstream>
// Add more standard header files as required
// #include <string>

using namespace std;

// Add your project's header files here
// #include "CFraction.h"
#include "Resistor.h"
#include "SerialResistorConnection.h"
#include "ParallelResistorConnection.h"
#include "ResistanceReader.h"

// Main program
int main (void)
{
    cout << "Exam-2024WiSe started." << endl << endl;
    
    extern void allTests();
    allTests();

    return 0;
}
