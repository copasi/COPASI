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
#include "CCopasiException.h"
#include "CCopasiMessage.h"
#include "CGlobals.h"
#include "CReadConfig.h"
#include "CWriteConfig.h"
#include "CCompartment.h"
#include "CDatum.h"
#include "CCopasiVector.h"
#include "CMetab.h"
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
long  TestBaseFunction(void);

vector < CMetab * >
      InitMetabolites(CCopasiVector < CCompartment > & compartment);

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
        // TestBaseFunction();
        
        
    }

    catch (CCopasiException Exception)
    {
        cout << Exception.GetMessage().GetText() << endl;
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
        cout << Exception.GetMessage().GetText() << endl;
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
        cout << Exception.GetMessage().GetText() << endl;
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
    
    CCopasiVector < CCompartment > ListOut;

    ListOut.Load(Specific,2);

    CWriteConfig VectorOut((string) "TestCompartmentVector.txt");
    ListOut.Save(VectorOut);
    VectorOut.Flush();

    CCopasiVector < CCompartment > ListIn;

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
    
    CReadConfig inbuf("gps/chem1.gps");
 
    CCopasiVector< CCompartment > Compartments;
    inbuf.GetVariable("TotalCompartments", "long", &size,
                      CReadConfig::LOOP);
    
    Compartments.Load(inbuf, size);

    if (inbuf.GetVersion() < "4")
    {
        CMetabolitesOld OldMetabolites;

        inbuf.GetVariable("TotalMetabolites", "long", &size,
                          CReadConfig::LOOP);
        OldMetabolites.Load(inbuf, size);
        
        CMetab Metabolite;
        for (long i = 0; i < size; i++)
        {
            Metabolite = OldMetabolites[i];
            
            Compartments[OldMetabolites[i].GetIndex()].
                AddMetabolite(Metabolite);
        }
    }

    vector < CMetab * > Metabolites = InitMetabolites(Compartments);
    CCopasiVector < CKinFunction > Functions;
    inbuf.GetVariable("TotalUDKinetics", "long", &size,
                      CReadConfig::LOOP);
    Functions.Load(inbuf, size)    ;
    
    CWriteConfig outbuf("copasi.gps");
    size = Compartments.Size();
    outbuf.SetVariable("TotalCompartments", "long", &size);
    Compartments.Save(outbuf);
    size = Functions.Size();
    outbuf.SetVariable("TotalUDKinetics", "long", &size);
    Functions.Save(outbuf);
    
    outbuf.Flush();

    CReadConfig inbuf2("copasi.gps");
    Compartments.Delete();
    Functions.Delete();
    
    inbuf2.GetVariable("TotalCompartments", "long", &size,
                       CReadConfig::LOOP);
    Compartments.Load(inbuf2,size);
    inbuf2.GetVariable("TotalUDKinetics", "long", &size,
                      CReadConfig::LOOP);
    Functions.Load(inbuf2, size);

    CWriteConfig outbuf2("copasi2.gps");
    size = Compartments.Size();
    outbuf2.SetVariable("TotalCompartments", "long", &size);
    Compartments.Save(outbuf2);
    size = Functions.Size();
    outbuf2.SetVariable("TotalUDKinetics", "long", &size);
    Functions.Save(outbuf2);
    
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
    f.Init();
    
    f.SetName("test");
    f.SetDescription("(a-b)*(a+b)/5");
    
    f.Parse();
    f.SetIdentifierType("a", N_SUBSTRATE);
    
    double a = 4;
    double b = 1;
    
    vector < CCallParameter > CallParameters;

    CallParameters.resize(1);
    
    CallParameters[0].SetType(CCallParameter::VECTOR_DOUBLE);
    CallParameters[0].Identifiers().resize(2);
    
    CallParameters[0].Identifiers()[0] = &a;
    CallParameters[0].Identifiers()[1] = &b;
    
    double r = f.CalcValue(CallParameters);
    
    CWriteConfig out("TestKinFunction");
    f.Save(out);
    f.Delete();
    
    out.Flush();
    
    CReadConfig in("TestKinFunction");
    CKinFunction g;
    
    g.Load(in);
    
    a = 5;
    r = g.CalcValue(CallParameters);

    return 0;
}

vector < CMetab * > 
    InitMetabolites(CCopasiVector < CCompartment > & compartments)
{
    vector < CMetab * > Metabolites;

    for (long i = 0; i < compartments.Size(); i++)
        for (long j = 0; j < compartments[i].GetMetabolites().Size(); j++)
            Metabolites.push_back(&compartments[i].GetMetabolites()[j]);
    
    return Metabolites;
}

long TestBaseFunction()
{
    CBaseFunction BaseFunction;
    BaseFunction.Init();
    
    BaseFunction.CallParameters().resize(3);
    BaseFunction.Init();
    
    BaseFunction.Delete();
    
    return 0;
}

