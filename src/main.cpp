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

C_INT32  TestReadConfig(void);
C_INT32  TestWriteConfig(void);
C_INT32  TestCompartment(void);
C_INT32  TestException(void);
C_INT32  TestDatum(void);
C_INT32  TestMetab(void);
C_INT32  TestMessage(void);
C_INT32  TestReadSample(void);
C_INT32  TestMoiety(void);
C_INT32  TestKinFunction(void);
C_INT32  TestBaseFunction(void);
C_INT32  MakeFunctionDB(void);
C_INT32  MakeFunctionEntry(const string &name,
                           const string &description,
                           short reversible,
                           vector < string > modifier,
                           vector < string > parameter,
                           CCopasiVector <CKinFunction> &functions);

vector < CMetab * >
InitMetabolites(CCopasiVector < CCompartment > & compartment);

C_INT32 main(void)
{
    cout << "Starting main program." << endl;
    
    
    try
    {
        cout << "sizeof(long) = " << sizeof(long) << endl;
        cout << "sizeof(int) = " << sizeof(int) << endl;
        cout << "sizeof(short) = " << sizeof(short) << endl;
        cout << "sizeof(double) = " << sizeof(double) << endl;
        cout << "sizeof(float) = " << sizeof(float) << endl;
        
        
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
        // MakeFunctionDB();
    }

    catch (CCopasiException Exception)
    {
        cout << Exception.GetMessage().GetText() << endl;
    }

    cout << "Leaving main program." << endl;
    return 0;
}

C_INT32  TestMessage(void)
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

C_INT32  TestException()
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


C_INT32  TestReadConfig(void)
{
    cout << "Entering TestReadConfig." << endl;
    // CReadConfig Default;
    CReadConfig Specific((string) "TestWriteConfig.txt");
    string outstring = "";
    Specific.GetVariable((string) "Compartment", 
                         (string) "string", 
                         (void *) &outstring);
    C_FLOAT64 outdouble = 0;
    Specific.GetVariable((string) "Volume", 
                         (string) "C_FLOAT64", 
                         (void *) &outdouble);
    Specific.GetVariable((string) "Compartment", 
                         (string) "string", 
                         (void *) &outstring);
    Specific.GetVariable((string) "Volume", 
                         (string) "C_FLOAT64", 
                         (void *) &outdouble);
    // Default.Free();
    // Specific.Free();
    
    cout << endl;
    return 0;
}
 
C_INT32  TestWriteConfig(void)
{
    cout << "Entering TestWriteConfig." << endl;
    // CWriteConfig Default;
    CWriteConfig Specific((string) "TestWriteConfig.txt");
    string outstring = "Laber";
    Specific.SetVariable((string) "Compartment", 
                         (string) "string", 
                         (void *) &outstring);
    C_FLOAT64 outdouble = 1.03e3;
    Specific.SetVariable((string) "Volume", 
                         (string) "C_FLOAT64", 
                         (void *) &outdouble);
    Specific.Flush();
    
    outstring = "Blubber";
    Specific.SetVariable((string) "Compartment", 
                         (string) "string", 
                         (void *) &outstring);
    outdouble = 1.03e3;
    Specific.SetVariable((string) "Junk", 
                         (string) "C_FLOAT64", 
                         (void *) &outdouble);
    Specific.Flush();
    
    cout << endl;
    return 0;
}
   

C_INT32 TestCompartment(void)
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

C_INT32 TestDatum(void)
{
    cout << "Entering TestDatum." << endl;
    C_FLOAT64 doublevariable;
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

C_INT32 TestMetab(void)
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

C_INT32 TestReadSample(void)
{
    C_INT32 size = 0;
    C_INT32 i;
    
    CMetabolitesOld OldMetabolites;
    
    CReadConfig inbuf("gps/chem1.gps");
 
    if (inbuf.GetVersion() < "4")
    {
        inbuf.GetVariable("TotalMetabolites", "C_INT32", &size,
                          CReadConfig::LOOP);
        OldMetabolites.Load(inbuf, size);
    }
    
    CCopasiVector< CCompartment > Compartments;
    inbuf.GetVariable("TotalCompartments", "C_INT32", &size,
                      CReadConfig::LOOP);
    
    Compartments.Load(inbuf, size);

    if (inbuf.GetVersion() < "4")
    {
        // Create the correct compartment / metabolite relationships
        CMetab Metabolite;
        for (i = 0; i < OldMetabolites.Size(); i++)
        {
            Metabolite = OldMetabolites[i];
            
            Compartments[OldMetabolites[i].GetIndex()].
                AddMetabolite(Metabolite);
        }
    }

    vector < CMetab * > Metabolites = InitMetabolites(Compartments);
    CCopasiVector < CKinFunction > Functions;
    inbuf.GetVariable("TotalUDKinetics", "C_INT32", &size,
                      CReadConfig::LOOP);
    Functions.Load(inbuf, size)    ;

    for (i = 0; i < Functions.Size(); i++)
        Copasi.FunctionDB.Add(Functions[i]);
    
    CCopasiVector < CStep > Steps;
    inbuf.GetVariable("TotalSteps", "C_INT32", &size,
                      CReadConfig::LOOP);
    Steps.Load(inbuf, size);
    
    if (inbuf.GetVersion() < "4")
    {
        // Create the correct step-substrate / metabolite relationships
        // Create the correct step-product / metabolite relationships  
        // Create the correct step-modifier / metabolite relationships  
    }

    CWriteConfig outbuf("copasi.gps");
    size = Compartments.Size();
    outbuf.SetVariable("TotalCompartments", "C_INT32", &size);
    Compartments.Save(outbuf);
    size = Functions.Size();
    outbuf.SetVariable("TotalUDKinetics", "C_INT32", &size);
    Functions.Save(outbuf);
    
    outbuf.Flush();

    CReadConfig inbuf2("copasi.gps");
    Compartments.Delete();
    Functions.Delete();
    
    inbuf2.GetVariable("TotalCompartments", "C_INT32", &size,
                       CReadConfig::LOOP);
    Compartments.Load(inbuf2,size);
    inbuf2.GetVariable("TotalUDKinetics", "C_INT32", &size,
                       CReadConfig::LOOP);
    Functions.Load(inbuf2, size);

    CWriteConfig outbuf2("copasi2.gps");
    size = Compartments.Size();
    outbuf2.SetVariable("TotalCompartments", "C_INT32", &size);
    Compartments.Save(outbuf2);
    size = Functions.Size();
    outbuf2.SetVariable("TotalUDKinetics", "C_INT32", &size);
    Functions.Save(outbuf2);
    
    return 0;
}

C_INT32 TestMoiety()
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
    
    C_FLOAT64 Value=mo.Value();
    string Description = mo.GetDescription();
    
    mo.Change("metab 2", 2);
    
    mo.Delete("metab 1");
    Value=mo.Value();
    
    return 0;
}

C_INT32 TestKinFunction()
{
    CKinFunction f;
    f.Init();
    
    f.SetName("test");
    f.SetDescription("(a-b)*(a+b)/5");
    
    f.Parse();
    f.SetIdentifierType("a", N_SUBSTRATE);
    
    C_FLOAT64 a = 4;
    C_FLOAT64 b = 1;
    
    vector < CCallParameter > CallParameters;

    CallParameters.resize(1);
    
    CallParameters[0].SetType(CCallParameter::VECTOR_DOUBLE);
    CallParameters[0].Identifiers().resize(2);
    
    CallParameters[0].Identifiers()[0] = &a;
    CallParameters[0].Identifiers()[1] = &b;
    
    C_FLOAT64 r = f.CalcValue(CallParameters);
    
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

    for (C_INT32 i = 0; i < compartments.Size(); i++)
        for (C_INT32 j = 0; j < compartments[i].GetMetabolites().Size(); j++)
            Metabolites.push_back(&compartments[i].GetMetabolites()[j]);
    
    return Metabolites;
}

C_INT32 TestBaseFunction()
{
    CBaseFunction BaseFunction;
    BaseFunction.Init();
    
    BaseFunction.CallParameters().resize(3);
    BaseFunction.Init();
    
    BaseFunction.Delete();
    
    return 0;
}

C_INT32 MakeFunctionDB()
{
    CCopasiVector <CKinFunction> functions;
    vector <string> modifier;
    vector <string> parameter;

    parameter.push_back("v");
    MakeFunctionEntry("Constant flux (irreversible)",
                      "v",
                      FALSE,
                      modifier,
                      parameter,
                      functions);
    modifier.clear();
    parameter.clear();

    parameter.push_back("v");
    MakeFunctionEntry("Constant flux (reversible)",
                      "v",
                      TRUE,
                      modifier,
                      parameter,
                      functions);
    modifier.clear();
    parameter.clear();

    parameter.push_back("Km");
    parameter.push_back("V");
    MakeFunctionEntry("Henri-Michaelis-Menten (irreversible)",
                      "V*substrate/(Km+substrate)",
                      FALSE,
                      modifier,
                      parameter,
                      functions);
    modifier.clear();
    parameter.clear();

    parameter.push_back("Kms");
    parameter.push_back("Kmp");
    parameter.push_back("Vf");
    parameter.push_back("Vr");
    MakeFunctionEntry("Reversible Michaelis-Menten",
                      "(Vf*substrate/Kms-Vr*product/Kmp)/(1+substrate/Kms+product/Kmp)",
                      TRUE,
                      modifier,
                      parameter,
                      functions);
    modifier.clear();
    parameter.clear();

    parameter.push_back("Kms");
    parameter.push_back("Kmp");
    parameter.push_back("Vf");
    parameter.push_back("Vr");
    parameter.push_back("Ki");
    MakeFunctionEntry("Substrate inhibition (rev)",
                      "(Vf*substrate/Kms-Vr*product/Kmp)/(1+substrate/Kms+product/Kmp+(substrate/Ki)^2)",
                      TRUE,
                      modifier,
                      parameter,
                      functions);
    modifier.clear();
    parameter.clear();

    parameter.push_back("Km");
    parameter.push_back("V");
    parameter.push_back("Ki");
    MakeFunctionEntry("Substrate inhibition (irr)",
                      "V*substrate/(Km+substrate+Km*(substrate/Ki)^2)",
                      FALSE,
                      modifier,
                      parameter,
                      functions);
    modifier.clear();
    parameter.clear();

    parameter.push_back("V");
    parameter.push_back("Ksc");
    parameter.push_back("Ksa");
    MakeFunctionEntry("Substrate activation (irr)",
                      "V*(substrate/Ksa)^2/(1+substrate/Ksc+substrate/Ksa+(substrate/Ksa)^2)",
                      FALSE,
                      modifier,
                      parameter,
                      functions);
    modifier.clear();
    parameter.clear();

    modifier.push_back("Inhibitor");
    parameter.push_back("Kms");
    parameter.push_back("Kmp");
    parameter.push_back("Vf");
    parameter.push_back("Vr");
    parameter.push_back("Ki");
    MakeFunctionEntry("Competitive inhibition (rev)",
                      "(Vf*substrate/Kms-Vr*product/Kmp)/(1+substrate/Kms+product/Kmp+Inhibitor/Ki)",
                      TRUE,
                      modifier,
                      parameter,
                      functions);
    modifier.clear();
    parameter.clear();

    modifier.push_back("Inhibitor");
    parameter.push_back("Km");
    parameter.push_back("V");
    parameter.push_back("Ki");
    MakeFunctionEntry("Competitive inhibition (irr)",
                      "V*substrate/(Km+substrate+Km*Inhibitor/Ki)",
                      FALSE,
                      modifier,
                      parameter,
                      functions);
    modifier.clear();
    parameter.clear();

    modifier.push_back("Inhibitor");
    parameter.push_back("Kms");
    parameter.push_back("Kmp");
    parameter.push_back("Vf");
    parameter.push_back("Vr");
    parameter.push_back("Ki");
    MakeFunctionEntry("Uncompetitive inhibition (rev)",
                      "(Vf*substrate/Kms-Vr*product/Kmp)/(1+(substrate/Kms+product/Kmp)*(1+Inhibitor/Ki))",
                      TRUE,
                      modifier,
                      parameter,
                      functions);
    modifier.clear();
    parameter.clear();

    modifier.push_back("Inhibitor");
    parameter.push_back("Km");
    parameter.push_back("V");
    parameter.push_back("Ki");
    MakeFunctionEntry("Uncompetitive inhibition (irr)",
                      "V*substrate/(Km+substrate*(1+Inhibitor/Ki))",
                      FALSE,
                      modifier,
                      parameter,
                      functions);
    modifier.clear();
    parameter.clear();

    modifier.push_back("Inhibitor");
    parameter.push_back("Kms");
    parameter.push_back("Kmp");
    parameter.push_back("Vf");
    parameter.push_back("Vr");
    parameter.push_back("Ki");
    MakeFunctionEntry("Noncompetitive inhibition (rev)",
                      "(Vf*substrate/Kms-Vr*product/Kmp)/((1+substrate/Kms+product/Kmp)*(1+Inhibitor/Ki))",
                      FALSE,
                      modifier,
                      parameter,
                      functions);
    modifier.clear();
    parameter.clear();

    modifier.push_back("Inhibitor");
    parameter.push_back("Km");
    parameter.push_back("V");
    parameter.push_back("Ki");
    MakeFunctionEntry("Noncompetitive inhibition (irr)",
                      "V*substrate/((Km+substrate)*(1+Inhibitor/Ki))",
                      FALSE,
                      modifier,
                      parameter,
                      functions);
    modifier.clear();
    parameter.clear();

    modifier.push_back("Inhibitor");
    parameter.push_back("Kms");
    parameter.push_back("Kmp");
    parameter.push_back("Vf");
    parameter.push_back("Vr");
    parameter.push_back("Kis");
    parameter.push_back("Kic");
    MakeFunctionEntry("Mixed inhibition (rev)",
                      "(Vf*substrate/Kms-Vr*product/Kmp)/(1+Inhibitor/Kis+(substrate/Kms+product/Kmp)*(1+Inhibitor/Kic))",
                      TRUE,
                      modifier,
                      parameter,
                      functions);
    modifier.clear();
    parameter.clear();

    modifier.push_back("Inhibitor");
    parameter.push_back("Km");
    parameter.push_back("V");
    parameter.push_back("Kis");
    parameter.push_back("Kic");
    MakeFunctionEntry("Mixed inhibition (irr)",
                      "V*substrate/(Km*(1+Inhibitor/Kis)+substrate*(1+Inhibitor/Kic))",
                      FALSE,
                      modifier,
                      parameter,
                      functions);
    modifier.clear();
    parameter.clear();

    modifier.push_back("Activator");
    parameter.push_back("Kms");
    parameter.push_back("Kmp");
    parameter.push_back("Vf");
    parameter.push_back("Vr");
    parameter.push_back("Ka");
    MakeFunctionEntry("Specific activation (rev)",
                      "(Vf*substrate/Kms-Vr*product/Kmp)*Activator/(Ka+(1+substrate/Kms+product/Kmp)*Activator)",
                      TRUE,
                      modifier,
                      parameter,
                      functions);
    modifier.clear();
    parameter.clear();

    modifier.push_back("Activator");
    parameter.push_back("Kms");
    parameter.push_back("V");
    parameter.push_back("Ka");
    MakeFunctionEntry("Specific activation (irrev)",
                      "V*substrate*Activator/(Kms*Ka+(Kms+substrate)*Activator)",
                      FALSE,
                      modifier,
                      parameter,
                      functions);
    modifier.clear();
    parameter.clear();

    modifier.push_back("Activator");
    parameter.push_back("Kms");
    parameter.push_back("Kmp");
    parameter.push_back("Vf");
    parameter.push_back("Vr");
    parameter.push_back("Ka");
    MakeFunctionEntry("Catalytic activation (rev)",
                      "(Vf*substrate/Kms-Vr*product/Kmp)*Activator/((1+substrate/Kms+product/Kmp)*(Ka+Activator))",
                      TRUE,
                      modifier,
                      parameter,
                      functions);
    modifier.clear();
    parameter.clear();

    modifier.push_back("Activator");
    parameter.push_back("Kms");
    parameter.push_back("V");
    parameter.push_back("Ka");
    MakeFunctionEntry("Catalytic activation (irrev)",
                      "V*substrate*Activator/((Kms+substrate)*(Ka+Activator))",
                      FALSE,
                      modifier,
                      parameter,
                      functions);
    modifier.clear();
    parameter.clear();

    modifier.push_back("Activator");
    parameter.push_back("Kms");
    parameter.push_back("Kmp");
    parameter.push_back("Vf");
    parameter.push_back("Vr");
    parameter.push_back("Kas");
    parameter.push_back("Kac");
    MakeFunctionEntry("Mixed activation (rev)",
                      "(Vf*substrate/Kms-Vr*product/Kmp)*Activator/(Kas+Activator+(substrate/Kms+product/Kmp)*(Kac+Activator))",
                      TRUE,
                      modifier,
                      parameter,
                      functions);
    modifier.clear();
    parameter.clear();

    modifier.push_back("Activator");
    parameter.push_back("Kms");
    parameter.push_back("V");
    parameter.push_back("Kas");
    parameter.push_back("Kac");
    MakeFunctionEntry("Mixed activation (irrev)",
                      "V*substrate*Activator/(Kms*(Kas+Activator)+substrate*(Kac+Activator))",
                      FALSE,
                      modifier,
                      parameter,
                      functions);
    modifier.clear();
    parameter.clear();

    modifier.push_back("Modifier");
    parameter.push_back("Km");
    parameter.push_back("V");
    parameter.push_back("Kd");
    parameter.push_back("a");
    parameter.push_back("b");
    MakeFunctionEntry("Hyperbolic modifier (irrev)",
                      "V*substrate*(1+b*Modifier/(a*Kd))/(Km*(1+Modifier/Kd)+substrate*(1+Modifier/(a*Kd)))",
                      FALSE,
                      modifier,
                      parameter,
                      functions);
    modifier.clear();
    parameter.clear();

    modifier.push_back("Modifier");
    parameter.push_back("Kms");
    parameter.push_back("Kmp");
    parameter.push_back("Vf");
    parameter.push_back("Vr");
    parameter.push_back("Kd");
    parameter.push_back("a");
    parameter.push_back("b");
    MakeFunctionEntry("Hyperbolic modifier (rev)",
                      "(Vf*substrate/Kms-Vr*product/Kmp)*(1+b*Modifier/(a*Kd))/(1+Modifier/Kd+(substrate/Kms+product/Kmp)*(1+Modifier/(a*Kd)))",
                      TRUE,
                      modifier,
                      parameter,
                      functions);
    modifier.clear();
    parameter.clear();

    modifier.push_back("Inhibitor");
    parameter.push_back("V");
    parameter.push_back("Ks");
    parameter.push_back("n");
    parameter.push_back("L");
    parameter.push_back("Ki");
    MakeFunctionEntry("Allosteric inhibition (MWC)",
                      "V*substrate*(1+substrate/Ks)^(n-1)/(Ks*L*(1+Inhibitor/Ki)^n+(Ks+substrate)^n)",
                      FALSE,
                      modifier,
                      parameter,
                      functions);
    modifier.clear();
    parameter.clear();

    modifier.push_back("Inhibitor");
    parameter.push_back("Vf");
    parameter.push_back("Vr");
    parameter.push_back("Kms");
    parameter.push_back("Kmp");
    parameter.push_back("n");
    parameter.push_back("Ki");
    MakeFunctionEntry("Allosteric inhibition (empirical)",
                      "(Vf*substrate/Kms-Vr*product/Kmp)/(1+substrate/Kms+product/Kmp+(Inhibitor/Ki)^n)",
                      TRUE,
                      modifier,
                      parameter,
                      functions);
    modifier.clear();
    parameter.clear();

    parameter.push_back("Shalve");
    parameter.push_back("V");
    parameter.push_back("h");
    MakeFunctionEntry("Hill Cooperativity",
                      "V*substrate^h/(Shalve^h+substrate^h)",
                      FALSE,
                      modifier,
                      parameter,
                      functions);
    modifier.clear();
    parameter.clear();

    parameter.push_back("Keq");
    parameter.push_back("Vf");
    parameter.push_back("Shalve");
    parameter.push_back("Phalve");
    parameter.push_back("h");
    MakeFunctionEntry("Reversible Hill",
                      "Vf*substrate/Shalve*(1-product/(substrate*Keq))*(substrate/Shalve+product/Phalve)^(h-1)/(1+(substrate/Shalve+product/Phalve)^h)",
                      TRUE,
                      modifier,
                      parameter,
                      functions);
    modifier.clear();
    parameter.clear();

    modifier.push_back("Modifier");
    parameter.push_back("Keq");
    parameter.push_back("Vf");
    parameter.push_back("Shalve");
    parameter.push_back("Phalve");
    parameter.push_back("h");
    parameter.push_back("Mhalve");
    parameter.push_back("alpha");
    MakeFunctionEntry("Reversible Hill 1 modifier",
                      "Vf*substrate/Shalve*(1-product/(substrate*Keq))*(substrate/Shalve+product/Phalve)^(h-1)/((1+(Modifier/Mhalve)^h)/(1+alpha*(Modifier/Mhalve)^h)+(substrate/Shalve+product/Phalve)^h)",
                      TRUE,
                      modifier,
                      parameter,
                      functions);
    modifier.clear();
    parameter.clear();

    modifier.push_back("ModifierA");
    modifier.push_back("ModifierB");
    parameter.push_back("Keq");
    parameter.push_back("Vf");
    parameter.push_back("Shalve");
    parameter.push_back("Phalve");
    parameter.push_back("h");
    parameter.push_back("MAhalve");
    parameter.push_back("alphaA");
    parameter.push_back("MBhalve");
    parameter.push_back("alphaB");
    parameter.push_back("alphaAB");
    MakeFunctionEntry("Reversible Hill 2 modifiers",
                      "Vf*substrate/Shalve*(1-product/(substrate*Keq))*(substrate/Shalve+product/Phalve)^(h-1)/((1+(ModifierA/MAhalve)^h+(ModifierB/MBhalve)^h)/(1+alphaA*(ModifierA/MAhalve)^h+alphaB*(ModifierB/MBhalve)^h+alphaA*alphaB*alphaAB*(ModifierA/MAhalve)^h*(ModifierB/MBhalve)^h)+(substrate/Shalve+product/Phalve)^h)",
                      TRUE,
                      modifier,
                      parameter,
                      functions);
    modifier.clear();
    parameter.clear();

    parameter.push_back("Kms");
    parameter.push_back("Kmp");
    parameter.push_back("Vf");
    parameter.push_back("Keq");
    MakeFunctionEntry("Uni Uni",
                      "Vf*(substrate-product/Keq)/(substrate+Kms*(1+product/Kmp))",
                      TRUE,
                      modifier,
                      parameter,
                      functions);
    modifier.clear();
    parameter.clear();

    parameter.push_back("Kms");
    parameter.push_back("Kmp");
    parameter.push_back("Kii");
    parameter.push_back("Vf");
    parameter.push_back("Keq");
    MakeFunctionEntry("Iso Uni Uni",
                      "Vf*(substrate-product/Keq)/(substrate*(1+product/Kii)+Kms*(1+product/Kmp))",
                      TRUE,
                      modifier,
                      parameter,
                      functions);
    modifier.clear();
    parameter.clear();

    parameter.push_back("Kms");
    parameter.push_back("Kmp");
    parameter.push_back("Kmq");
    parameter.push_back("Kip");
    parameter.push_back("Keq");
    parameter.push_back("Vf");
    parameter.push_back("Vr");
    MakeFunctionEntry("Ordered Uni Bi",
                      "Vf*(substrate-productp*productq/Keq)/(Kms+substrate*(1+productp/Kip)+Vf/(Vr*Keq)*(Kmq*productp+Kmp*productq+productp*productq))",
                      TRUE,
                      modifier,
                      parameter,
                      functions);
    modifier.clear();
    parameter.clear();

    parameter.push_back("Kma");
    parameter.push_back("Kmb");
    parameter.push_back("Kmp");
    parameter.push_back("Kia");
    parameter.push_back("Keq");
    parameter.push_back("Vf");
    parameter.push_back("Vr");
    MakeFunctionEntry("Ordered Bi Uni",
                      "Vf*(substratea*substrateb-product/Keq)/(substratea*substrateb+Kma*substrateb+Kmb*substratea+Vf/(Vr*Keq)(Kmp+product*(1+substratea/Kia)))",
                      TRUE,
                      modifier,
                      parameter,
                      functions);
    modifier.clear();
    parameter.clear();

    parameter.push_back("Keq");
    parameter.push_back("Vf");
    parameter.push_back("Vr");
    parameter.push_back("Kma");
    parameter.push_back("Kmb");
    parameter.push_back("Kmp");
    parameter.push_back("Kmq");
    parameter.push_back("Kia");
    parameter.push_back("Kib");
    parameter.push_back("Kip");
    MakeFunctionEntry("Ordered Bi Bi",
                      "Vf*(substratea*substrateb-productp*productq/Keq)/(substratea*substrateb*(1+productp/Kip)+Kma*substrateb+Kmb*(substratea+Kia)+Vf/(Vr*Keq)*(Kmq*productp(1+substratea/Kia)+productq*(Kmp*(1+Kia*substrateb/(Kma*Kmb))+productp*(1+substrateb/Kib))))",
                      TRUE,
                      modifier,
                      parameter,
                      functions);
    modifier.clear();
    parameter.clear();

    parameter.push_back("Keq");
    parameter.push_back("Vf");
    parameter.push_back("Vr");
    parameter.push_back("Kma");
    parameter.push_back("Kmb");
    parameter.push_back("Kmp");
    parameter.push_back("Kmq");
    parameter.push_back("Kia");
    parameter.push_back("Kiq");
    MakeFunctionEntry("Ping Pong Bi Bi",
                      "Vf*(substratea*substrateb-productp*productq/Keq)/(substratea*substrateb*(1+productq/Kiq)+Kma*substrateb+Kmb*substratea+Vf/(Vr*Keq)*(Kmq*productp*(1+substratea/Kia)+productq*(Kmp+productp)))",
                      TRUE,
                      modifier,
                      parameter,
                      functions);
    modifier.clear();
    parameter.clear();

    CWriteConfig db("FunctionDB.gps");
    functions.Save(db);

    functions.Delete();
    
    return 0;
}

C_INT32 MakeFunctionEntry(const string &name,
                          const string &description,
                          short reversible,
                          vector < string > modifier,
                          vector < string > parameter,
                          CCopasiVector <CKinFunction> &functions)
{
    C_INT32 Index = functions.Size();
    C_INT32 i;
    
    CKinFunction f;

    functions.Add(f);
    functions[Index].Init();

    functions[Index].SetName(name);
    functions[Index].SetDescription(description);
    functions[Index].SetReversible(reversible);

    functions[Index].Parse();

    pair < C_INT32, C_INT32 > Tuple(0, 0);

    Tuple = functions[Index].FindIdentifier("substrate");
    if (0 <= Tuple.first && 0 <= Tuple.second )
        functions[Index].SetIdentifierType("substrate", N_SUBSTRATE);
        
    Tuple = functions[Index].FindIdentifier("substratea");
    if (0 <= Tuple.first && 0 <= Tuple.second )
        functions[Index].SetIdentifierType("substratea", N_SUBSTRATE);
        
    Tuple = functions[Index].FindIdentifier("substrateb");
    if (0 <= Tuple.first && 0 <= Tuple.second )
        functions[Index].SetIdentifierType("substrateb", N_SUBSTRATE);
        
    Tuple = functions[Index].FindIdentifier("product");
    if (0 <= Tuple.first && 0 <= Tuple.second )
        functions[Index].SetIdentifierType("product", N_PRODUCT);
        
    Tuple = functions[Index].FindIdentifier("productp");
    if (0 <= Tuple.first && 0 <= Tuple.second )
        functions[Index].SetIdentifierType("productp", N_PRODUCT);
        
    Tuple = functions[Index].FindIdentifier("productq");
    if (0 <= Tuple.first && 0 <= Tuple.second )
        functions[Index].SetIdentifierType("productq", N_PRODUCT);
        

    for (i = 0; i < modifier.size(); i++)
        functions[Index].SetIdentifierType(modifier[i], N_MODIFIER);

    for (i = 0; i < parameter.size(); i++)
        functions[Index].SetIdentifierType(parameter[i], N_KCONSTANT);
            
    return 0;
}

