// Main 
// 
// (C) Pedro Mendes 2000
//

#include <iostream>
#include <fstream>
#include <string>

using namespace std ;

#include "CReadConfig.h"
#include "CCompartment.h"

int  TestReadConfig(void);
int  TestCompartment(void);

int main(void)
{
    // TestReadConfig();

    TestCompartment();

    return 0;
}

int  TestReadConfig(void)
{
    CReadConfig Default;
    CReadConfig Specific((string) "test.txt");
    string outstring = "";
    Specific.GetVariable((string) "Compartment", 
                         (string) "string", 
                         (void *) &outstring);
    double outdouble = 0;
    Specific.GetVariable((string) "Volume", 
                         (string) "double", 
                         (void *) &outdouble);
    Specific.GetVariable((string) "Compartment", 
                         (string) "string", 
                         (void *) &outstring);
    Specific.GetVariable((string) "Volume", 
                         (string) "double", 
                         (void *) &outdouble);
    Default.Free();
    Specific.Free();
    
    return 0;
}
    

int TestCompartment(void)
{
    cout << "creating a CCompartment object..." << endl;
    CCompartment c;
    cout << "Opening an output stream" << endl;
    ofstream of("test.txt");
    c.Save(&of);
	    
    CCompartment *d = NULL;
    d = new CCompartment[1];

    CCompartment g((string) "test2", 1.1e-2);
    d[0] = g;
    d[0].Save(&of);

    c=d[0];

    of.close();

    delete [] d;

    CReadConfig Specific((string) "test.txt");
    CCompartment e,f;
    e.Load(&Specific);
    f.Load(&Specific);
    Specific.Free();

    return 0;
}

