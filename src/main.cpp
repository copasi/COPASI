// Main 
// 
// (C) Pedro Mendes 2000
//

#include <iostream>
#include <fstream>
#include <string>
#include <strstream>
#include <vector>

#include "copasi.h"
#include "CReadConfig.h"
#include "CWriteConfig.h"
#include "CCompartment.h"
#include "CDatum.h"
#include "CMetab.h"

int  TestReadConfig(void);
int  TestWriteConfig(void);
int  TestCompartment(void);
int  TestException(void);
int  TestDatum(void);
int  TestMetab(void);
int  TestMessage(void);
int  TestReadSample(void);

int main(void)
{
    cout << "Starting main program." << endl;
    
    
    try
    {
        // TestException();
        // TestMessage();

        // TestWriteConfig();
        // TestReadConfig();
        
        // TestCompartment();
        // TestDatum();
        // TestMetab();
        TestReadSample();
    }

    catch (CCopasiException Exception)
    {
        cout << Exception.Message.GetText() << endl;
    }

    cout << "Leaving main program." << endl;
    return 0;
}

int  TestMessage(void)
{
    try
    {
        CCopasiMessage(WARNING, "Test %s %d", "string", 5, 3);
        FatalError();
    }

    catch (CCopasiException Exception)
    {
        cout << Exception.Message.GetText() << endl;
    }
    return 0;
}

int  TestException()
{
    try
    {
        cout << "Entering exception test." << endl;
        CCopasiMessage Error(ERROR, "Fatal Error");
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
    
    cout << endl;
    return 0;
}


int  TestReadConfig(void)
{
    cout << "Entering TestReadConfig." << endl;
    // CReadConfig Default;
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
    // Default.Free();
    // Specific.Free();
    
    cout << endl;
    return 0;
}
 
int  TestWriteConfig(void)
{
    cout << "Entering TestWriteConfig." << endl;
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
    Specific.Flush();
    
    outstring = "Blubber";
    Specific.SetVariable((string) "Compartment", 
                         (string) "string", 
                         (void *) &outstring);
    outdouble = 1.03e3;
    Specific.SetVariable((string) "Junk", 
                         (string) "double", 
                         (void *) &outdouble);
    Specific.Flush();
    
    cout << endl;
    return 0;
}
   

int TestCompartment(void)
{
    cout << "Entering TestCompartment." << endl;
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
    
    CCompartmentVector ListOut(2);

    ListOut[0].Load(Specific);
    ListOut[1].Load(Specific);

    CWriteConfig VectorOut((string) "TestCompartmentVector.txt");
    ListOut.Save(VectorOut);
    VectorOut.Flush();

    CCompartmentVector ListIn;
    CReadConfig VectorIn((string) "TestCompartmentVector.txt");
    ListIn.Load(VectorIn);

    cout << endl;
    return 0;
}


int TestDatum(void)
{
    cout << "Entering TestDatum." << endl;
    double doublevariable;
    cout << "creating a CDatum object..." << endl;
    CDatum d((string)"[medicarpin]t", 
             D_TCONC, 
             (string)"medicarpin", 
             (string)"", &doublevariable);
    cout << "Opening an output stream" << endl;
    CWriteConfig of("TestDatum1.txt");
    d.Save(of);
    of.Flush();
    
    CReadConfig Specific((string) "TestDatum1.txt");
    CDatum* e;
    e = new CDatum[2];
    e[0].Load(Specific);

    e[1] = e[0];
    cout << "Opening another output stream" << endl;
    CWriteConfig of2("TestDatum2.txt");
    e[1].Save(of2);

    delete [] e;

    cout << endl;
    return 0;
}

int TestMetab(void)
{
    cout << "Entering TestMetab." << endl;
    cout << "creating a CMetab object..." << endl;

    CCompartmentVector ListIn;
    CReadConfig VectorIn((string) "TestCompartmentVector.txt");
    ListIn.Load(VectorIn);

    CMetab c((string) "MetabTest", 1, ListIn[0]);

    cout << "Opening an output stream" << endl;
    CWriteConfig of("TestMetab.txt");
    c.Save(of,ListIn);
    of.Flush();

    CMetab d;
    CReadConfig inf("TestMetab.txt");
    d.Load(inf,ListIn);
    
    cout << endl;
    return 0;
}

int TestReadSample(void)
{
    CReadConfig inbuf("sample.gps");
    
    CCompartmentVector Compartments;
    Compartments.Load(inbuf);
    
    CMetabVector Metabolites;
    Metabolites.Load(inbuf, Compartments);

    CWriteConfig outbuf("copasi.gps");
    Compartments.Save(outbuf);
    Metabolites.Save(outbuf, Compartments);
    
    outbuf.Flush();
    return 0;
}
