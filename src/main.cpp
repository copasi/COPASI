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
#include "CCopasiVector.h"
#include "CNodeK.h"
#include "CKinFunction.h"
#include "CStep.h"
#include "CMoiety.h"

long  TestReadConfig(void);
long  TestWriteConfig(void);
long  TestCompartment(void);
long  TestException(void);
long  TestDatum(void);
long  TestMetab(void);
long  TestMessage(void);
long  TestReadSample(void);
long  TestMoiety(void);
long  TestKinFunction(void);

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
        // TestMoiety();
        // TestKinFunction();
        
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
   
#ifdef XXXX

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
 
    CCopasiVector< CCompartment > Compartments;
//    CCompartmentVector Compartments;
    
    inbuf.GetVariable("TotalCompartments", "long", &size,
                      CReadConfig::LOOP);
    
    Compartments.Load(inbuf, size);
    
    CCopasiVector< CMetab > Metabolites;
//    CMetabVector Metabolites;

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

long TestMoiety()
{
    CMoiety mo("test");
    CCompartment c("comp", 1.0);
    CCopasiVector < CMetab > mv;
    
    mv = c.GetMetabolites();
    
    mv.Add(CMetab("metab 1"));

    c.GetMetabolites().Add(CMetab("metab 1"));
    c.GetMetabolites().Add(CMetab("metab 2"));
    
    c.GetMetabolites()[0].SetConcentration(5.2);
    c.GetMetabolites()[1].SetConcentration(2.0);
    CMetab m = c.GetMetabolites()["metab 2"];
    
    mo.Add(-2000, c.GetMetabolites()[0]);
    mo.Add(3, c.GetMetabolites()[1]);
    mo.Add(0, c.GetMetabolites()[1]);
    
    double Value=mo.Value();
    string Description = mo.GetDescription();
    
    mo.Change("metab 2", 2);
    
    mo.Delete("metab 1");
    Value=mo.Value();
    
    return 0;
}

long TestKinFunction()
{
    CKinFunction f;
    f.SetName("test");
    f.SetDescription("(a-b)*(a+b)/5");
    
    f.Parse();
    f.SetIdentifierType("a", N_SUBSTRATE);
    
    double a = 4;
    double b = 1;
    
    vector < double * > Identifiers;
    
    Identifiers.push_back(&a);
    Identifiers.push_back(&b);
    
    double r = f.CalcValue(Identifiers);
    
    CWriteConfig out("TestKinFunction");
    f.Save(out);

    out.Flush();
    
    CReadConfig in("TestKinFunction");
    CKinFunction g;
    
    g.Load(in);
    
    a = 5;
    r = g.CalcValue(Identifiers);

    return 0;
}
