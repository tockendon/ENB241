/* powersystem.cpp
 * ENB241 Project
 *
 * PowerSystem class file
 *
 *
 */

#include "powersystem.h"
#include <limits>

double readNumber();
double readPercentage();
double readHours();
string readCoordinates();
double readAngle(unsigned int max);

PowerSystem::PowerSystem()
 : _ratedPower(1), _wireLoss(1)
{
    // Get basic input
    cout << "Enter power rating for bank in Watts: ";
    _ratedPower[0] = readNumber();
    cout << "Rated power: " << _ratedPower[0] << " W" << endl;

    cout << "Enter orientation loss % for bank: ";
    _orientLoss = readPercentage();
    cout << "Orientation loss: " << _orientLoss << "%" << endl;

    cout << "Enter installation loss % for bank: ";
    _tiltLoss = readPercentage();
    cout << "Installation loss: " << _tiltLoss << "%" << endl;

    cout << "Enter wire loss % for bank: ";
    _wireLoss[0] = readPercentage();
    cout << "wire loss: " << _wireLoss[0] << "%" << endl;

    cout << "Enter inverter efficiency in %: ";
    _inverterEfficiency = readPercentage();
    cout << "Inverter efficiency: " << _inverterEfficiency << "%" << endl;

    cout << "Enter projected reduction in efficiency for solar panels in %: ";
    _paneltimeEfficiency = readPercentage();
    cout << "Reduction in efficiency: " << _paneltimeEfficiency << "%" << endl;

    cout << "Enter the mean sunlight hours for location: ";
    _sunlightHours = readHours();
    cout << "Mean sunlight hours: " << _sunlightHours << "Hrs" << endl;


    cout << endl;

    // Power in kW
    _ratedPower[0] = _ratedPower[0]/1000;

    // Number of banks for basic implementation
    _NUM_BANKS = 1;

    // Declare objects
    bank = new Bank(_ratedPower[0], _orientLoss + _tiltLoss);
    vectorBank.push_back(bank);

    wire = new Wire(bank->getPowerOut(), _wireLoss[0]);
    vectorWire.push_back(wire);

    // Declare unused objects as NULL
    inverter = NULL;
    analysis = NULL;
    local = NULL;

}

PowerSystem::PowerSystem(unsigned int NUM_BANKS)
 : _ratedPower(NUM_BANKS), _orientAngle(NUM_BANKS), _tiltAngle(NUM_BANKS), _wireLoss(NUM_BANKS)
{
    int i;
    _NUM_BANKS = NUM_BANKS;

    // Location input:
    getline(cin, _gpsCord);
    cout << "Enter gps location: ";
    // getline(cin, _gpsCord);
    _gpsCord = readCoordinates();
    cout << "Location: " << _gpsCord << endl;

    // Declare location object here to output optimum tilt angle
    local = new Location(_gpsCord);
    _optimAngle = local->optimalAngle();
    //cout << "\nOtimum tilt angle for location is: " << _optimAngle << " degrees\n" << endl;

    // Get advanced input for each bank
    for(i = 0; i < NUM_BANKS; i++)
    {

        cout << "Enter power rating (Watts) for bank " << i+1 << ": ";
        _ratedPower[i] = readNumber();
        cout << "Rated power for bank " << i+1 << ": " << _ratedPower[i] << " W" << endl;

        cout << "Enter orientation angle (degrees) for bank " << i+1 << ": ";
        _orientAngle[i] = readAngle(359);
        cout << "Orientation angle for bank " << i+1 << ": " << _orientAngle[i] << " degrees" << endl;

        cout << "Enter installation angle (degrees) for bank " << i+1 << ": ";
        _tiltAngle[i] = readAngle(90);
        cout << "Tilt angle for bank " << i+1 << ": " << _tiltAngle[i] << " degrees" << endl;

        cout << "Enter wire loss % for bank " << i+1 << ": ";
        _wireLoss[i] = readPercentage();
        cout << "Wire loss for bank " << i+1 << ": " << _wireLoss[i] << "%" << endl;

        // Power in kW
        _ratedPower[i] = _ratedPower[i]/1000;

    }

    // Get advanced input shared across banks
    cout << "Enter inverter efficiency in %: ";
    _inverterEfficiency = readPercentage();
    cout << "Inverter efficiency: " << _inverterEfficiency << "%" << endl;

    cout << "Enter projected reduction in efficiency for solar panels in %: ";
    _paneltimeEfficiency = readPercentage();
    cout << "Reduction in efficiency: " << _paneltimeEfficiency << "%" << endl;

    cout << endl;

    // Cost benefit inputs:
    cout << "Enter average usage(kWh) during peak daylight hours: ";
    _genUsage = readNumber();
    cout << "General usage: " << _genUsage << " kWh" << endl;

    cout << "Enter average usage(kWh) during peak tariff hours: ";
    _peakUsage = readNumber();
    cout << "Peak usage: " << _peakUsage << " kWh" << endl;

    cout << "Enter average usage(kWh) during off peak tariff hours: ";
    _offPeakUsage = readNumber();
    cout << "Off peak usage: " << _offPeakUsage << " kWh" << endl;

    cout << "Enter system installation cost (AUD): ";
    _installCost = readNumber();
    cout << "Installation cost: $" << _installCost << endl;

    cout << endl;

    // Set up objects
	_NS = local->getNS();
    _sunlightHours = local->sunlightHours();

    for(i = 0; i < _NUM_BANKS; i++)
    {
        bank = new Bank(_ratedPower[i], _orientAngle[i], _tiltAngle[i], _optimAngle, _NS);
        vectorBank.push_back(bank);
        wire = new Wire(vectorBank[i]->getPowerOut(), _wireLoss[i]);
        vectorWire.push_back(wire);
    }

    analysis = new CostBenefit(*local, _genUsage, _peakUsage, _offPeakUsage, _installCost);

    // Unused objects
    inverter = NULL;

}

PowerSystem::~PowerSystem()
{
    if (bank != NULL){
        delete bank;
    }
    else if (wire != NULL){
        delete wire;
    }
    else if (inverter != NULL){
        delete inverter;
    }
    else if (analysis != NULL){
        delete analysis;
    }
    else if (local != NULL){
        delete local;
    }
}

// Display total output of the entire system
void PowerSystem::Output()
{
    int i;
    int year;
    double totalOutput = 0;
    double output;
    double investmentReturn;
    double totalInvestReturn = 0;
    unsigned int recoupYears = 0;
    double profitLoss;

    // Get output
    for(i = 0; i < _NUM_BANKS; i++)
    {
        totalOutput = *vectorWire[i] + totalOutput; //kW (uses operator overloading)
    }

    // Erase vectors once output is obtained
    vectorBank.erase(vectorBank.begin(),vectorBank.end());
    vectorWire.erase(vectorWire.begin(),vectorWire.end());


    cout << " Year  Total kWh for Year      Average kWh Per Day" << endl;
    cout << " ----- -------------------     -------------------" << endl;
    for(year = 1; year <= 25; year++ )
    {
        inverter = new Inverter(totalOutput, _inverterEfficiency);
        output = *inverter * _sunlightHours; // calculate output using operator overloading

        // Stadnard output (from both simple and advanced)
        cout << setw(4)  << year << " " << setw(10) << output*365 << " kWh/year " << setw(16) << output << " kWh/d ";

        // Cost benefit analysis output
        if (analysis != NULL){
            investmentReturn = analysis->calcInvestReturn(output);
            totalInvestReturn = analysis->tallyReturn(totalInvestReturn); //tally's the total return on the investment
            if(recoupYears == 0)
            {
                recoupYears = analysis->recoup(totalInvestReturn, year);//returns zero if initial cost hasn't been recouped. Otherwise returns the recoup year
            }
            cout << setw(4) << "$" << investmentReturn << " Return on investment";
        }

        cout << endl;

        totalOutput *= (1-_paneltimeEfficiency/100); //decline in efficiency - only starts declining at end of first year;

    }

    cout << endl;

    // Output final total cost benefit information
    if (analysis != NULL){
        profitLoss = analysis->calcProfitLoss(totalInvestReturn);

        cout << "The total return on investment(savings + income) over the life of the system = $" << totalInvestReturn << endl;

        if(profitLoss>=0)
        {
            cout << "\nThe return on the investment exceeds the initial system cost after " << recoupYears << " years.\n"
                 << "The total profit over the life of the system = $" << profitLoss << endl;
        }
        else
        {
            cout << "\nThe return on the investment never exceeds the initial system cost.\n"
                 << "Therefore the total loss over the life of the system = $" << profitLoss << endl;
        }
		// output optimal tilt and orientation
		cout << "\nTo improve panel output adjust panels to optimal tilt angle of " << _optimAngle << " degrees and optimal orientation of " << local->optimalOrientation() << endl;
    }
}

// Read in values, and alert if incorrect input.
double readNumber()
{
    double input;
    while(!(cin >> input) || input < 0)
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cerr << "Invalid input. Must be a positive number.\nTry again: ";
    }
    return input;
}

double readPercentage()
{
    double input;
    while(!(cin >> input) || input < 0 || input > 100)
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cerr << "Invalid input. Must be a percentage between 0 and 100.\nTry again: ";
    }
    return input;
}

double readHours()
{
    double input;
    while(!(cin >> input) || input < 0 || input > 24)
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cerr << "Invalid input. Must be an hour value between 0 and 24.\nTry again: ";
    }
    return input;
}

string readCoordinates()
{
    string input;
    double latitude;
    double longitude;
    char NS;
    char EW;

    getline(cin, input);
    istringstream ss(input);
    ss >> latitude >> NS >> longitude >> EW;
    // Capitalise to make error checking easier
    NS = toupper(NS);
    EW = toupper(EW);
    // Booleans for all unwanted outcomes. Keep prompting for new input string until correct string entered.
    while( ((NS !=  'S') && (NS !=  'N')) || ((EW !=  'E') && (EW !=  'W')) ||
        (latitude < 0) || (latitude > 90) || (longitude < 0) || (longitude > 180) )
    {
        // Prompt
        cerr << "Invalid input. Must be GPS location in decimal degrees, eg: 12.345 S 67.890 E." <<
        endl << "Latitude must be between -90 and 90, and Longitude  between -180 and 180.\nTry again: ";
        // Get input
        getline(cin, input);
        istringstream ss(input);
        ss >> latitude >> NS >> longitude >> EW;
        NS = toupper(NS);
        EW = toupper(EW);
        // Loop back to top and check new input
    }
    return input;
}

double readAngle(unsigned int maxValue)
{
    double input;
    while(!(cin >> input) || input < 0 || input > maxValue)
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cerr << "Invalid input. Must be an angle between 0 and " << maxValue << " degrees.\nTry again: ";
    }
    return input;
}









