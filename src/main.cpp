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
#include "CCompartmentVector.h"
#include "CDatum.h"
#include "CMetabVector.h"
// #include "CNodeK.h"
#include "CKinetics.h"
#include "CStep.h"

long  TestReadConfig(void);
long  TestWriteConfig(void);
long  TestCompartment(void);
long  TestException(void);
long  TestDatum(void);
long  TestMetab(void);
long  TestMessage(void);
long  TestReadSample(void);

long main(void)
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

long  TestMessage(void)
{
    try
    {
        CCopasiMessage(CCopasiMessage::WARNING, "Test %s %d", "string", 5, 3);
        FatalError();
    }

    catch (CCopasiException Exception)
    {
        cout << Exception.Message.GetText() << endl;
    }
    return 0;
}

long  TestException()
{
    try
    {
        cout << "Entering exception test." << endl;
        CCopasiMessage Error(CCopasiMessage::ERROR, "Fatal Error");
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


long  TestReadConfig(void)
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
 
long  TestWriteConfig(void)
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
   

long TestCompartment(void)
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
    
    CCompartmentVector ListOut;

    ListOut.Load(Specific,2);

    CWriteConfig VectorOut((string) "TestCompartmentVector.txt");
    ListOut.Save(VectorOut);
    VectorOut.Flush();

    CCompartmentVector ListIn;
    CReadConfig VectorIn((string) "TestCompartmentVector.txt");
    ListIn.Load(VectorIn,2);

    cout << endl;
    return 0;
}

#ifdef XXXX

long TestDatum(void)
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

long TestMetab(void)
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
#endif

long TestReadSample(void)
{
    long size = 0;
    
    CReadConfig inbuf("sample.gps");
    
    CCompartmentVector Compartments;
    
    inbuf.GetVariable("TotalCompartments", "long", &size,
                      CReadConfig::LOOP);
    
    Compartments.Load(inbuf, size);
    
    CMetabVector Metabolites;

    inbuf.GetVariable("TotalMetabolites", "long", &size,
                      CReadConfig::LOOP);
    Metabolites.Load(inbuf, size);

    // CNodeKVector Nodes;
    // Nodes.Load(inbuf);
#ifdef XXXX
    CStep Step;
    Step.Load(inbuf);
    
    CKinetics Kinetics;
    Kinetics.Load(inbuf);
#endif     
    CWriteConfig outbuf("copasi.gps");
#ifdef XXXX
    Step.Save(outbuf);
    Kinetics.Save(outbuf);
#endif     
    Metabolites.Save(outbuf);
    Compartments.Save(outbuf);
    // Nodes.Save(outbuf);
    
    outbuf.Flush();
    return 0;
}
