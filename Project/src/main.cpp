/* main.cpp
 * ENB241 Portfolio 2
 *
 * Solar System demonstration
 *
 *
 *
 */

#include "powersystem.h"

int main(int argc, char *argv[])
{
    // Check for invalid command line inputs
    if(argc > 2 )
    {
        cout << "Too many input arguments: argc > 2" << endl;
        exit(EXIT_FAILURE);
    }
    else if(( argc == 2 &&  argv[1][0] == '-' && argv[1][1] != 't') || ( argc == 2 &&  argv[1][0] != '-'))
    {
        cout << "Invalid use of input argument: use -t to switch into basic mode" << endl;
        exit(EXIT_FAILURE);
    }
    // Choose between basic and advanced functionality
    else if(argc > 1 && argv[1][0] == '-' && argv[1][1] == 't')
    {
// Basic mode:
//===========================================================================================================
        // Implement system
        PowerSystem simpleSystem = PowerSystem();
        simpleSystem.Output();
    }
    else
// Advanced mode:
//===========================================================================================================
    {
        int NUM_BANKS;
        // Get number of banks to install:
        cout << "Enter the number of Banks to install: ";
        while(!(cin >> NUM_BANKS) || NUM_BANKS < 0)
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cerr << "Invalid input. Must be a positive number.\nTry again: ";
        }
        cout << "Number of banks: " << NUM_BANKS << endl;

        // Implement system
        PowerSystem advancedSystem = PowerSystem(NUM_BANKS);
        advancedSystem.Output();
    }
}
