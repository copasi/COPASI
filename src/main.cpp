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
#include "CDatum.h"

int  TestReadConfig(void);
int  TestCompartment(void);
int  TestDatum(void);

int main(void)
{
    // TestReadConfig();

    TestCompartment();
    TestDatum();

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


int TestDatum(void)
{
    double doublevariable;
    cout << "creating a CDatum object..." << endl;
    CDatum d((string)"[medicarpin]t", D_TCONC, (string)"medicarpin", (string)"", &doublevariable);
    cout << "Opening an output stream" << endl;
    ofstream of("test2.txt");
    d.Save(&of);
    of.close();

    CReadConfig Specific((string) "test2.txt");
    CDatum* e;
    e = new CDatum[2];
    e[0].Load(&Specific);
    Specific.Free();
    e[1] = e[0];
    cout << "Opening another output stream" << endl;
    ofstream of2("test3.txt");
    e[1].Save(&of2);
    of2.close();
    delete [] e;

    return 0;
}
