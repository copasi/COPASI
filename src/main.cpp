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
#include "CModel.h"
#include "CODESolver.h"
#include "CTrajectory.h"
#include "tnt/tnt.h"
#include "tnt/luX.h"
#include "tnt/cmat.h"
#include "tnt/vec.h"
#include "tnt/subscript.h"

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
C_INT32  TestModel(void);
C_INT32  TestLU();
C_INT32  TestLSODA(void (*f)(C_INT32, C_FLOAT64, C_FLOAT64 *, C_FLOAT64 *));
C_INT32  TestTrajectory(void);

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
        // TestTrajectory();
        // TestMoiety();
        // TestKinFunction();
        // TestBaseFunction();
        // MakeFunctionDB();
        // TestModel();
        // TestLU();

    }

    catch (CCopasiException Exception)
    {
        cout << Exception.getMessage().getText() << endl;
    }

    cout << "Leaving main program." << endl;
    return 0;
}

C_INT32  TestMessage(void)
{
    try
    {
        CCopasiMessage(CCopasiMessage::WARNING, "Test %s %d", "string", 5, 3);
        fatalError();
    }

    catch (CCopasiException Exception)
    {
        cout << Exception.getMessage().getText() << endl;
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
        cout << Exception.getMessage().getText() << endl;
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
    Specific.getVariable((string) "Compartment", 
                         (string) "string", 
                         (void *) &outstring);
    C_FLOAT64 outdouble = 0;
    Specific.getVariable((string) "Volume", 
                         (string) "C_FLOAT64", 
                         (void *) &outdouble);
    Specific.getVariable((string) "Compartment", 
                         (string) "string", 
                         (void *) &outstring);
    Specific.getVariable((string) "Volume", 
                         (string) "C_FLOAT64", 
                         (void *) &outdouble);
    // Default.free();
    // Specific.free();
    
    cout << endl;
    return 0;
}
 
C_INT32  TestWriteConfig(void)
{
    cout << "Entering TestWriteConfig." << endl;
    // CWriteConfig Default;
    CWriteConfig Specific((string) "TestWriteConfig.txt");
    string outstring = "Laber";
    Specific.setVariable((string) "Compartment", 
                         (string) "string", 
                         (void *) &outstring);
    C_FLOAT64 outdouble = 1.03e3;
    Specific.setVariable((string) "Volume", 
                         (string) "C_FLOAT64", 
                         (void *) &outdouble);
    Specific.flush();
    
    outstring = "Blubber";
    Specific.setVariable((string) "Compartment", 
                         (string) "string", 
                         (void *) &outstring);
    outdouble = 1.03e3;
    Specific.setVariable((string) "Junk", 
                         (string) "C_FLOAT64", 
                         (void *) &outdouble);
    Specific.flush();
    
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
    c.save(of);
    of.flush();

    CCompartment *d = NULL;
    d = new CCompartment[1];

    CCompartment g((string) "test2", 1.1e-2);
    d[0] = g;
    d[0].save(of);
    of.flush();

    c=d[0];

    delete [] d;

    CReadConfig Specific((string) "TestCompartment.txt");
    
    CCopasiVector < CCompartment > ListOut;

    ListOut.load(Specific,2);

    CWriteConfig VectorOut((string) "TestCompartmentVector.txt");
    ListOut.save(VectorOut);
    VectorOut.flush();

    CCopasiVector < CCompartment > ListIn;

    CReadConfig VectorIn((string) "TestCompartmentVector.txt");

    ListIn.load(VectorIn,2);

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
    d.save(of);
    of.flush();
    
    CReadConfig Specific((string) "TestDatum1.txt");
    CDatum* e;
    e = new CDatum[2];
    e[0].load(Specific);

    e[1] = e[0];
    cout << "Opening another output stream" << endl;
    CWriteConfig of2("TestDatum2.txt");
    e[1].save(of2);

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
    ListIn.load(VectorIn);

    CMetab c((string) "MetabTest", 1, ListIn[0]);

    cout << "Opening an output stream" << endl;
    CWriteConfig of("TestMetab.txt");
    c.save(of,ListIn);
    of.flush();

    CMetab d;
    CReadConfig inf("TestMetab.txt");
    d.load(inf,ListIn);
    
    cout << endl;
    return 0;
}
#endif

C_INT32 TestReadSample(void)
{
    C_INT32 size = 0;
    C_INT32 i;
    
    CReadConfig inbuf("gps/bakker.gps");
    CModel model;
    model.load(inbuf);
    model.buildStoi();
    model.lUDecomposition();
    model.setMetabolitesStatus();
    model.buildRedStoi();
    model.buildMoieties();

    CODESolver odeSolver;
    size = model.getMetabolitesInd().size();
    C_FLOAT64 *y;
    y = new double[size];
    
    odeSolver.initialize(model, y, size);
    odeSolver.step(0.0, 1.0);
    
    CWriteConfig outbuf("copasi.gps");
    model.save(outbuf);
    outbuf.flush();

    Copasi.FunctionDB.cleanup();
    Copasi.FunctionDB.initialize();

    CReadConfig inbuf2("copasi.gps");
    CModel model2;
    model2.load(inbuf2);
    
    CWriteConfig outbuf2("copasi2.gps");
    model2.save(outbuf2);
    outbuf2.flush();
    
    return 0;
}

C_INT32 TestTrajectory(void)
{
    C_INT32 size = 0;
    C_INT32 i;
    
    CReadConfig inbuf("gps/BakkerComp.gps");
    CModel model;
    model.load(inbuf);
    model.buildStoi();
    model.lUDecomposition();
    model.setMetabolitesStatus();
    model.buildRedStoi();
    model.buildConsRel();
    model.buildMoieties();
    
    CTrajectory traj(&model, 20, 10.0, 1);
    traj.getODESolver()->loadLSODAParameters(inbuf);
    traj.process();
    traj.cleanup();

    return 0;
}

C_INT32 TestMoiety()
{
    CMoiety mo("test");
    CCompartment c("comp", 1.0);
    CCopasiVector < CMetab > mv;
    
    mv = c.metabolites();
    
    mv.add(CMetab("metab 1"));

    c.metabolites().add(CMetab("metab 1"));
    c.metabolites().add(CMetab("metab 2"));
    
    c.metabolites()[0].setConcentration(5.2);
    c.metabolites()[1].setConcentration(2.0);
    CMetab m = c.metabolites()["metab 2"];
    
    mo.add(-2000, c.metabolites()[0]);
    mo.add(3, c.metabolites()[1]);
    mo.add(0, c.metabolites()[1]);
    
//    C_FLOAT64 Value=mo.value();
    string Description = mo.getDescription();
    
    mo.change("metab 2", 2);
    
    mo.cleanup("metab 1");
//    Value=mo.value();
    
    return 0;
}

C_INT32 TestKinFunction()
{
    CKinFunction f;
    f.initialize();
    
    f.setName("test");
    f.setDescription("(a-b)*(a+b)/5");
    
    f.parse();
    f.setIdentifierType("a", N_SUBSTRATE);
    f.setIdentifierType("b", N_PRODUCT);

    C_FLOAT64 a = 4;
    C_FLOAT64 b = 1;
    
    vector < CCallParameter > CallParameters;

    CallParameters.resize(1);
    
    CallParameters[0].setType(CCallParameter::VECTOR_DOUBLE);
    CallParameters[0].identifiers().resize(2);
    
    CallParameters[0].identifiers()[0] = &a;
    CallParameters[0].identifiers()[1] = &b;
    
    C_FLOAT64 r = f.calcValue(CallParameters);
    
    CWriteConfig out("TestKinFunction");
    f.save(out);
    f.cleanup();
    
    out.flush();
    
    CReadConfig in("TestKinFunction");
    CKinFunction g;
    
    g.load(in);
    
    a = 5;
    r = g.calcValue(CallParameters);

    return 0;
}

vector < CMetab * > 
InitMetabolites(CCopasiVector < CCompartment > & compartments)
{
    vector < CMetab * > Metabolites;

    for (C_INT32 i = 0; i < compartments.size(); i++)
        for (C_INT32 j = 0; j < compartments[i].metabolites().size(); j++)
            Metabolites.push_back(&compartments[i].metabolites()[j]);
    
    return Metabolites;
}

C_INT32 TestBaseFunction()
{
    CBaseFunction BaseFunction;
    
    BaseFunction.callParameters().resize(3);
    
    BaseFunction.cleanup();
    
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
    functions.save(db);

    functions.cleanup();
    
    return 0;
}

C_INT32 MakeFunctionEntry(const string &name,
                          const string &description,
                          short reversible,
                          vector < string > modifier,
                          vector < string > parameter,
                          CCopasiVector <CKinFunction> &functions)
{
    C_INT32 Index = functions.size();
    C_INT32 i;
    
    CKinFunction f;
    f.initialize();
    
    functions.add(f);

    functions[Index].setName(name);
    functions[Index].setDescription(description);
    functions[Index].setReversible(reversible);

    functions[Index].parse();

    pair < C_INT32, C_INT32 > Tuple(0, 0);

    Tuple = functions[Index].findIdentifier("substrate");
    if (0 <= Tuple.first && 0 <= Tuple.second )
        functions[Index].setIdentifierType("substrate", N_SUBSTRATE);
        
    Tuple = functions[Index].findIdentifier("substratea");
    if (0 <= Tuple.first && 0 <= Tuple.second )
        functions[Index].setIdentifierType("substratea", N_SUBSTRATE);
        
    Tuple = functions[Index].findIdentifier("substrateb");
    if (0 <= Tuple.first && 0 <= Tuple.second )
        functions[Index].setIdentifierType("substrateb", N_SUBSTRATE);
        
    Tuple = functions[Index].findIdentifier("product");
    if (0 <= Tuple.first && 0 <= Tuple.second )
        functions[Index].setIdentifierType("product", N_PRODUCT);
        
    Tuple = functions[Index].findIdentifier("productp");
    if (0 <= Tuple.first && 0 <= Tuple.second )
        functions[Index].setIdentifierType("productp", N_PRODUCT);
        
    Tuple = functions[Index].findIdentifier("productq");
    if (0 <= Tuple.first && 0 <= Tuple.second )
        functions[Index].setIdentifierType("productq", N_PRODUCT);
        

    for (i = 0; i < modifier.size(); i++)
        functions[Index].setIdentifierType(modifier[i], N_MODIFIER);

    for (i = 0; i < parameter.size(); i++)
        functions[Index].setIdentifierType(parameter[i], N_KCONSTANT);
            
    return 0;
}

C_INT32 TestModel()
{
    CReadConfig inbuf("gps/BakkerComp.gps");

    CModel m;
    
    m.load(inbuf);
}

C_INT32 TestLU()
{
    C_INT32 i;
    C_INT32 t;
    
    TNT::Matrix < C_FLOAT64 > A(4,3);
    
    A(1,1) =  1.0; A(1,2) = -2.0; A(1,3) =  0.0;
    A(2,1) = -1.0; A(2,2) =  2.0; A(2,3) =  1.0;
    A(3,1) =  0.0; A(3,2) =  0.0; A(3,3) =  2.0;
    A(4,1) =  0.0; A(4,2) =  0.0; A(4,3) = -3.0;
    
    TNT::Vector < TNT::Subscript > rowLU(4);
    TNT::Vector < TNT::Subscript > colLU(3);
    
    vector < C_INT32 > row(4);
    for (i = 0; i < row.size(); i++) row[i] = i;
    vector < C_INT32 > rowi = row;
    
    vector < C_INT32 > col(3);
    for (i = 0; i < col.size(); i++) col[i] = i;
    vector < C_INT32 > coli = col;

    cout << A << endl;

    TNT::LUX_factor(A, rowLU, colLU);
    
    //colLU(3) = 2;
    
    cout << A << endl;
    cout << rowLU << endl;
    cout << colLU << endl;

    for (i = 0; i < row.size(); i++) 
    {
        if (rowLU[i] - 1 > i)
        {
            t = row[i];
            row[i] = row[rowLU[i]-1];
            row[rowLU[i]-1] = t;
        }
    }
    
    for (i = rowi.size() - 1; 0 <= i; i--) 
    {
        if (rowLU[i]-1 > i)
        {
            t = rowi[i];
            rowi[i] = rowi[rowLU[i]-1];
            rowi[rowLU[i]-1] = t;
        }
    }
    
    for (i = col.size() - 1; 0 <= i; i--) 
    {
        if (colLU[i]-1 < i)
        {
            t = col[i];
            col[i] = col[colLU[i]-1];
            col[colLU[i]-1] = t;
        }
    }
    
    for (i = 0; i < coli.size(); i++) 
    {
        if (colLU[i] - 1 < i)
        {
            t = coli[i];
            coli[i] = coli[colLU[i]-1];
            coli[colLU[i]-1] = t;
        }
    }
    
    for (i = 0; i < row.size(); i++)
        cout << row[i] << ' ';
    cout << endl;
    for (i = 0; i < rowi.size(); i++)
        cout << rowi[i] << ' ';
    cout << endl;
    
    for (i = 0; i < col.size(); i++)
        cout << col[i] << ' ';
    cout << endl;
    for (i = 0; i < coli.size(); i++)
        cout << coli[i] << ' ';
    cout << endl;
    
    return 0;
}

C_INT32  TestLSODA(void (*f)(C_INT32, C_FLOAT64, C_FLOAT64 *, C_FLOAT64 *))
{
    C_INT32 n = 99;
    C_FLOAT64 d = 99.99;
    C_FLOAT64 * pd = &d;
    
    (*f)(n, d, pd, pd);

    return 0;
}


















