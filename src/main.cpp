// Main 
// 
// (C) Pedro Mendes 2000
//

#include <iostream>
#include <fstream>
#include <string>
#include <strstream>

#include "copasi.h"
#include "CReadConfig.h"
#include "CWriteConfig.h"
#include "CCompartment.h"
#include "CCopasiMessage.h"
#include "CCopasiException.h"
#include "CDatum.h"

int  TestReadConfig(void);
int  TestWriteConfig(void);
int  TestCompartment(void);
int  TestException(void);
int  TestDatum(void);

int main(void)
{
    cout << "Starting main program." << endl;
    
    // TestWriteConfig();
    // TestException();
    // TestReadConfig();
    TestCompartment();
    // TestDatum();

    cout << "Leaving main program." << endl;
    return 0;
}

int  TestException()
{
    try
    {
        cout << "Entering exception test." << endl;
        CCopasiMessage FatalError((string)"Fatal Error",
                                  (enum COPASI_MESSAGE_TYPE) ERROR);
        cout << "Leaving exception test." << endl;
    }
    
    catch (CCopasiException Exception)
    {
        cout << "Entering fatal error handling." << endl;
        cout << Exception.Message.GetText() << endl;
        cout << "Leaving fatal error handling." << endl;
    }

    // newline

    catch (char *str)
    {
        cout << "Caugth other exception" <<endl;
    }

    return 0;
}


int  TestReadConfig(void)
{
    CReadConfig Default;
    CReadConfig Specific((string) "TestWriteConfig.txt");
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
 
int  TestWriteConfig(void)
{
    // CWriteConfig Default;
    CWriteConfig Specific((string) "TestWriteConfig.txt");
    string outstring = "Laber";
    Specific.SetVariable((string) "Compartment", 
                         (string) "string", 
                         (void *) &outstring);
    double outdouble = 1.03e3;
    Specific.SetVariable((string) "Volume", 
                         (string) "double", 
                         (void *) &outdouble);

    outstring = "Blubber";
    Specific.SetVariable((string) "Compartment", 
                         (string) "string", 
                         (void *) &outstring);
    outdouble = 1.03e3;
    Specific.SetVariable((string) "Junk", 
                         (string) "double", 
                         (void *) &outdouble);
    
    return 0;
}
   

int TestCompartment(void)
{
    cout << "creating a CCompartment object..." << endl;
    CCompartment c;
    cout << "Opening an output stream" << endl;
    CWriteConfig of("TestCompartment.txt");
    c.Save(of);
    of.Flush();

    CCompartment *d = NULL;
    d = new CCompartment[1];

    CCompartment g((string) "test2", 1.1e-2);
    d[0] = g;
    d[0].Save(of);
    of.Flush();
    
    c=d[0];

    delete [] d;

    CReadConfig Specific((string) "TestCompartment.txt");
    CCompartment e,f;
    e.Load(Specific);
    f.Load(Specific);
    Specific.Free();

    return 0;
}


int TestDatum(void)
{
    double doublevariable;
    cout << "creating a CDatum object..." << endl;
    CDatum d((string)"[medicarpin]t", 
             D_TCONC, 
             (string)"medicarpin", 
             (string)"", &doublevariable);
    cout << "Opening an output stream" << endl;
    CWriteConfig of("test2.txt");
    d.Save(of);
    of.Flush();
    
    CReadConfig Specific((string) "test2.txt");
    CDatum* e;
    e = new CDatum[2];
    e[0].Load(Specific);
    Specific.Free();
    e[1] = e[0];
    cout << "Opening another output stream" << endl;
    CWriteConfig of2("test3.txt");
    e[1].Save(of2);

    delete [] e;

    return 0;
}
