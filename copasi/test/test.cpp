// Main 
// 
// (C) Pedro Mendes 2000
//

#include <iostream>
#include <fstream>
#include <string>
#include <strstream>
#include <vector>
#include <iomanip>
#include <algorithm>

#define COPASI_MAIN

#include "copasi.h"

#include "utilities/utilities.h"
#include "model/model.h"
#include "output/output.h"
#include "function/function.h"
#include "trajectory/trajectory.h"
#include "steadystate/steadystate.h"
//#include "optimization/optimization.h"
#include "utilities/CGlobals.h"
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
C_INT32  TestFunctionDB(void);
C_INT32  TestMassAction(void);
C_INT32  TestBaseFunction(void);
C_INT32  TestModel(void);
C_INT32  TestLU();
C_INT32  TestLSODA(void (*f)(C_INT32, C_FLOAT64, C_FLOAT64 *, C_FLOAT64 *));
C_INT32  TestTrajectory(void);
C_INT32  TestNewton(void);
C_INT32  TestSSSolution(void);
C_INT32  TestEigen(void);
//C_INT32  TestOptimization(void);     //yohe: new

C_INT32  CovertFunctionDB(void);
C_INT32  MakeFunctionDB(void);
C_INT32  MakeFunctionEntry(const string &name,
                           const string &description,
                           TriLogic reversible,
                           vector < string > modifier,
                           vector < string > parameter,
                           CCopasiVectorNS <CKinFunction> &functions);

vector < CMetab * >
InitMetabolites(CCopasiVector < CCompartment > & compartment);
C_INT32 TestMCA(void);
C_INT32 TestOutputEvent(void);

C_INT32 TestRandom(C_INT32 num_points, C_INT32 num_bins);
C_INT32 TestDependencyGraph();
C_INT32 TestIndexedPriorityQueue(C_INT32);
C_INT32 TestSpec2Model();

C_INT main(C_INT argc, char *argv[])
{
  cout << "Starting main program." << endl;
  Copasi = new CGlobals;
  Copasi->setArguments(argc, argv);
  
  try
    {
      cout << "sizeof(long) = " << sizeof(long) << endl;
      cout << "sizeof(int) = " << sizeof(int) << endl;
      cout << "sizeof(short) = " << sizeof(short) << endl;
      cout << "sizeof(double) = " << sizeof(double) << endl;
      cout << "sizeof(float) = " << sizeof(float) << endl;

        
//      TestException();
//      TestMessage();
       
//       TestWriteConfig();
//       TestReadConfig();
        
//      TestCompartment();
//      TestDatum();
//      TestMetab();
//      TestReadSample();
//      TestNewton();
//      TestSSSolution();
//YOHE: new test
//      TestOptimization();
      TestEigen();

//       TestTrajectory();
//       TestMoiety();
//       TestKinFunction();
//       TestMassAction();
//       TestFunctionDB();
//       TestBaseFunction();
//       TestModel();
//       TestLU();
//       TestMCA();
//       TestOutputEvent();        

//       MakeFunctionDB();
//       CovertFunctionDB();
      
//      TestRandom(10000, 100);
//      TestDependencyGraph();
//      TestIndexedPriorityQueue(7);
//      TestSpec2Model();
    }

  catch (CCopasiException Exception)
    {
      cout << Exception.getMessage().getText() << endl;
    }

  delete Copasi;
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
        std::cout << Exception.getMessage().getText() << std::endl;
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
  Specific.flush();
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
    
  CCopasiVectorNS < CCompartment > ListOut;

  ListOut.load(Specific,2);

  CWriteConfig VectorOut((string) "TestCompartmentVector.txt");
  ListOut.save(VectorOut);
  VectorOut.flush();

  CCopasiVectorNS < CCompartment > ListIn;

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

  Copasi->FunctionDB.cleanup();
  Copasi->FunctionDB.initialize();

  CReadConfig inbuf2("copasi.gps");
  CModel model2;
  model2.load(inbuf2);
    
  CWriteConfig outbuf2("copasi2.gps");
  model2.save(outbuf2);
  outbuf2.flush();
    
  return 0;
}

C_INT32 TestOutputEvent(void)
{
//  C_INT32 size = 0;

  cout << "Entering TestOutputEvent." << endl;

  ofstream  fout, fout1, fout2;
  //fout.open("TestSS.out");
  fout1.open("TestDyn.out");
  //fout2.open("TestRep.out");

  CReadConfig inbuf("c:/wsun/copasi_dev/copasi/gps/DANNY.gps");

  CModel model;
  model.load(inbuf);
  model.buildStoi();
  model.lUDecomposition();
  model.setMetabolitesStatus();
  model.buildRedStoi();
  model.buildL();
  model.buildMoieties();
    
  COutputList oList;

  oList.load(inbuf);

  CWriteConfig outbuf("wei.gps");
  oList.save(outbuf);

  //  oList.setModel(model);

  string SS = "Steady-state output";
  //  oList.compile(SS);

  //oList.CCopasi_SS(fout);
  //oList.CCopasi_Dyn(fout1);
  //oList.CCopasi_Rep(fout2);

  CTrajectory traj(&model, 20, 10.0, 1);

  //  COutputEvent event(traj, 0, &oList, fout1);

  traj.cleanup();
  cout << "Leaving TestOutputEvent..." << endl;

  //fout.close();
  fout1.close();
  //fout2.close();

  return 0;
}


C_INT32 TestTrajectory(void)
{
  string InputFile(Copasi->Arguments[1]);
  string OutputFile(Copasi->Arguments[2]);
  CReadConfig inbuf(InputFile);
  CWriteConfig outbuf(OutputFile);
  CModel model;

  // COutput output;
  // output.load(inbuf);
  
  model.load(inbuf);
  model.buildStoi();
  model.lUDecomposition();
  model.setMetabolitesStatus();
  model.buildRedStoi();
  model.buildL();
  model.buildMoieties();
  model.save(outbuf);
  
  Copasi->OutputList.load(inbuf);
  Copasi->OutputList.save(outbuf);

  CTrajectory traj(&model, 20, 10.0, 1);

  traj.load(inbuf);
  traj.save(outbuf);
  traj.getODESolver()->load(inbuf);
  traj.getODESolver()->loadLSODAParameters(inbuf);
  ofstream output("output.txt");
  
  traj.process(output);
  traj.cleanup();

  return 0;
}

C_INT32 TestMCA(void)
{
    cout << "Entering TestReport." << endl;

    CReadConfig inbuf("gps/DANNY.gps");

    CModel model;
    model.load(inbuf);
    model.buildStoi();
    model.lUDecomposition();
    model.setMetabolitesStatus();
    model.buildRedStoi();        
    
    CMca mMCA();
    return 0;
}


// by YH
C_INT32  TestNewton(void)
{
//    C_INT32 size = 0;
//    C_INT32 i;
 
    CReadConfig inbuf("gps/NewtonTest.gps");
    //   CReadConfig inbuf("gps/NewtonTest_yhtest.gps"); //dos format
    CModel model;
    model.load(inbuf);
    model.compile();
 
    model.getReactions().size();
    
    //set up CNewton object and pass to CSS_Solution
    CNewton newton;
    newton.setModel(model);
    // newton.initialize();
 
    //get mDerivFactor, mSSRes, and mNewtonLimit,
    //or may use their default values
    //YOHE: new test 03/22/02
    //newton.setDerivFactor(0.1);
    newton.setDerivFactor(0.003);
    cout << "setDerivFactor(0.003)" <<endl;
    newton.setSSRes(1.0e-9);
    newton.setNewtonLimit(50);
    //cout << "newton DerivFactor, SSRes, and NewtonLimit are: " 
    //     << newton.getDerivFactor()<<", "<<newton.getSSRes()<<", "
    //     << newton.getNewtonLimit()<<endl;

    //how to get ss_nfunction?
    newton.setSs_nfunction(0);
 
    //how to get mSs_x, mSs_new, mSs_dxdt, mSs_h, mSs_jacob, mSs_ipvt
    //and mSs_solution??? or don't need to care about them here??
    newton.init_Ss_x();
 
    newton.process();
 
    return 0;
}
 
 
// by YH
C_INT32  TestSSSolution(void)
{
//    C_INT32 size = 0;
//    C_INT32 i;
 
    //CReadConfig inbuf("gps/BakkerComp.gps");
    CReadConfig inbuf("gps/NewtonTest.gps");
    //CReadConfig inbuf("gps/NewtonTest_yhtest.gps"); //dos format
    CModel model;
    model.load(inbuf);
    model.compile();
 
    model.getReactions().size();

    //set up CNewton object and pass to CSS_Solution
    CNewton newton;
    newton.setModel(model);
    // newton.initialize();
    newton.setDerivFactor(0.1);
    newton.setSSRes(1.0e-9);
    newton.setNewtonLimit(50);
    newton.setSs_nfunction(0);
    newton.init_Ss_x();

    CTrajectory traj(&model, 20, 10.0, 1);
    traj.load(inbuf);
    traj.getODESolver()->load(inbuf);
    traj.getODESolver()->loadLSODAParameters(inbuf);
 
    CSS_Solution ss_soln;

    ss_soln.setModel(&model);

    //Yohe: new change 03/22/02 
    ss_soln.setSSRes(1.0e-9);  //I cannot get it from load, I don't know why


    //yohe: new added on 03/15/02
    ss_soln.initialize();

    ss_soln.setNewton(&newton);
    ss_soln.setTrajectory(&traj);
 
    //do we need set ss_soln.mJacob model here????
 
    ofstream output("output.txt");
    
    ss_soln.process(output);
 
    return 0;
}

//by YH
//first, test matrix A = [-1 4 -2; -3 4 0; -3 1 3].
//the eig(A)=[1.0 2.0 3.0].
// 
C_INT32  TestEigen(void)
{
  
  CEigen myEigen;

  //initialize matrix
  TNT::Matrix<C_FLOAT64> matrix(3, 3, 
                           " -1 4 -2 "
                           " -3 4  0 "
                           " -3 1  3 ");
  //TNT::Matrix<C_FLOAT64> matrix=[-1 4 -2; -3 4 0; -3 1 3] ;
  // SSResoltion=1.000000e-009 (from NewtonTest_yhtest.gps)
  C_FLOAT64 ssRes = 0.0;


  myEigen.setN(3);
  myEigen.initialize();
  myEigen.CalcEigenvalues(ssRes, matrix);

  cout << "!!! YH: the max eigenvalue real part is: "<<myEigen.getEigen_maxrealpart() << endl<<endl;

  
  return 0;
}


/*
//yohe: test optimization -- 03/27/02
//
C_INT32  TestOptimization(void)
{
  cout << "TestOptimization() begins --- " << endl;
    C_INT32 size = 0;
    C_INT32 i;
 
    //CReadConfig inbuf("gps/BakkerComp.gps");
    //CReadConfig inbuf("gps/NewtonTest.gps");
    //CModel model;
    //model.load(inbuf);
    //model.compile();
 
    //model.getReactions().size();
   
    COptimizer * opt = new COptimizer();
    opt->Optimise();

    //polymorphism, late binding
    CGA ga;
    COptimizer * optPtr = &ga;
    cout << "TestOptimization() begins new test --- " << endl;
    opt->Optimise();
    optPtr->Optimise();

    //CGA ga;
    //opt.Set_nparam (100);
    //opt.Set_mn(-10.0);
    //opt.Set_mx(10.0);
    //ga.Optimise();
 
    return 0;

}

*/


C_INT32 TestMoiety()
{
  CMoiety mo("test");
  CCompartment c("comp", 1.0);
  CCopasiVectorN < CMetab > mv;
    
  mv = c.metabolites();
    
  mv.add(CMetab("metab 1"));

  c.metabolites().add(CMetab("metab 1"));
  c.metabolites().add(CMetab("metab 2"));
    
  c.metabolites()[0]->setConcentration(5.2);
  c.metabolites()[1]->setConcentration(2.0);
  CMetab m;
  m = *c.metabolites()["metab 2"];
    
  mo.add(-2000, c.metabolites()[0]);
  mo.add(3, c.metabolites()[1]);
  mo.add(0, c.metabolites()[1]);
    
  //    C_FLOAT64 Value=mo.value();
  string Description = mo.getDescription();
    
  // mo.change("metab 2", 2);
    
  mo.cleanup();
  //    Value=mo.value();
    
  return 0;
}

C_INT32 TestKinFunction()
{
  cout << "Testing CKinFunction\n";
  CKinFunction f;
    
  f.setName("test");
  f.setDescription("(a-b)*(a+b)/5");
  f.getParameters().add("a", CFunctionParameter::FLOAT64, "UNKNOWN");
  f.getParameters().add("b", CFunctionParameter::FLOAT64, "UNKNOWN");
  
  f.compile();
  
  //  f.setIdentifierType("a", N_SUBSTRATE);
  //  f.setIdentifierType("b", N_PRODUCT);

  C_FLOAT64 a = 4;
  C_FLOAT64 b = 1;
    
  CCallParameters CallParameters;

  CallParameters.resize(2);
    
  CallParameters[0] = &a;
  CallParameters[1] = &b;
    
  C_FLOAT64 r = f.calcValue(CallParameters);
  cout << "Value obtained = " << r << " Should be = " << (a-b)*(a+b)/5 << endl;
    
  CWriteConfig out("TestKinFunction.gps");
  f.save(out);
  f.cleanup();
    
  out.flush();
    
  CReadConfig in("TestKinFunction.gps");
  CKinFunction g;
    
  g.load(in);
    
  a = 5;
  r = g.calcValue(CallParameters);

  return 0;
}

/*
vector < CMetab * > 
InitMetabolites(CCopasiVectorN < CCompartment > & compartments)
{
  vector < CMetab * > Metabolites;

  for (unsigned C_INT32 i = 0; i < compartments.size(); i++)
    for (unsigned C_INT32 j = 0;
         j < compartments[i]->metabolites().size(); j++)
      Metabolites.push_back(compartments[i]->metabolites()[j]);
    
  return Metabolites;
}
*/

C_INT32 TestBaseFunction()
{
  CFunction BaseFunction;
    
  //  BaseFunction.callParameters().resize(3);
    
  BaseFunction.cleanup();
    
  return 0;
}

#ifdef XXXX
C_INT32 MakeFunctionDB()
{
  CCopasiVectorNS <CKinFunction> functions;
  vector <string> modifier;
  vector <string> parameter;

  parameter.push_back("v");
  MakeFunctionEntry("Constant flux (irreversible)",
                    "v",
                    TriFalse,
                    modifier,
                    parameter,
                    functions);
  modifier.clear();
  parameter.clear();

  parameter.push_back("v");
  MakeFunctionEntry("Constant flux (reversible)",
                    "v",
                    TriTrue,
                    modifier,
                    parameter,
                    functions);
  modifier.clear();
  parameter.clear();

  parameter.push_back("Km");
  parameter.push_back("V");
  MakeFunctionEntry("Henri-Michaelis-Menten (irreversible)",
                    "V*substrate/(Km+substrate)",
                    TriFalse,
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
                    TriTrue,
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
                    TriTrue,
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
                    TriFalse,
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
                    TriFalse,
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
                    TriTrue,
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
                    TriFalse,
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
                    TriTrue,
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
                    TriFalse,
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
                    TriFalse,
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
                    TriFalse,
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
                    TriTrue,
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
                    TriFalse,
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
                    TriTrue,
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
                    TriFalse,
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
                    TriTrue,
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
                    TriFalse,
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
                    TriTrue,
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
                    TriFalse,
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
                    TriFalse,
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
                    TriTrue,
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
                    "V*substrate*(Ks+substrate)^(n-1)/(L*(Ks*(1+Inhibitor/Ki))^n+(Ks+substrate)^n)",
                    TriFalse,
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
                    TriTrue,
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
                    TriFalse,
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
                    TriTrue,
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
                    TriTrue,
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
                    TriTrue,
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
                    TriTrue,
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
                    TriTrue,
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
                    TriTrue,
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
                    TriTrue,
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
                    TriTrue,
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
                    TriTrue,
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
                          TriLogic reversible,
                          vector < string > modifier,
                          vector < string > parameter,
                          CCopasiVectorNS <CKinFunction> &functions)
{
  C_INT32 Index = functions.size();
  unsigned C_INT32 i;
    
  CKinFunction f;

  functions.add(f);

  functions[Index]->setName(name);
  functions[Index]->setDescription(description);
  functions[Index]->setReversible(reversible);

  functions[Index]->parse();

  pair < C_INT32, C_INT32 > Tuple(0, 0);

  Tuple = functions[Index]->findIdentifier("substrate");
  if (0 <= Tuple.first && 0 <= Tuple.second )
    functions[Index]->setIdentifierType("substrate", N_SUBSTRATE);
        
  Tuple = functions[Index]->findIdentifier("substratea");
  if (0 <= Tuple.first && 0 <= Tuple.second )
    functions[Index]->setIdentifierType("substratea", N_SUBSTRATE);
        
  Tuple = functions[Index]->findIdentifier("substrateb");
  if (0 <= Tuple.first && 0 <= Tuple.second )
    functions[Index]->setIdentifierType("substrateb", N_SUBSTRATE);
        
  Tuple = functions[Index]->findIdentifier("product");
  if (0 <= Tuple.first && 0 <= Tuple.second )
    functions[Index]->setIdentifierType("product", N_PRODUCT);
        
  Tuple = functions[Index]->findIdentifier("productp");
  if (0 <= Tuple.first && 0 <= Tuple.second )
    functions[Index]->setIdentifierType("productp", N_PRODUCT);
        
  Tuple = functions[Index]->findIdentifier("productq");
  if (0 <= Tuple.first && 0 <= Tuple.second )
    functions[Index]->setIdentifierType("productq", N_PRODUCT);
        

  for (i = 0; i < modifier.size(); i++)
    functions[Index]->setIdentifierType(modifier[i], N_MODIFIER);

  for (i = 0; i < parameter.size(); i++)
    functions[Index]->setIdentifierType(parameter[i], N_KCONSTANT);
            
  return 0;
}
#endif // XXXX

C_INT32 TestModel()
{
  CReadConfig inbuf("gps/BakkerComp.gps");

  CModel m;
  m.load(inbuf);

  return 0;
}

C_INT32 TestLU()
{
  unsigned C_INT32 i;
  C_INT32 t;
    
  TNT::Matrix < C_FLOAT64 > A(4,3);
    
  A(1,1) =  1.0; A(1,2) = -2.0; A(1,3) =  0.0;
  A(2,1) = -1.0; A(2,2) =  2.0; A(2,3) =  1.0;
  A(3,1) =  0.0; A(3,2) =  0.0; A(3,3) =  2.0;
  A(4,1) =  0.0; A(4,2) =  0.0; A(4,3) = -3.0;
    
  TNT::Vector < unsigned C_INT32 > rowLU(4);
  TNT::Vector < unsigned C_INT32 > colLU(3);
    
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
    
  for (i = rowi.size(); 0 < i--; ) 
    {
      if (rowLU[i]-1 > i)
        {
          t = rowi[i];
          rowi[i] = rowi[rowLU[i]-1];
          rowi[rowLU[i]-1] = t;
        }
    }
    
  for (i = col.size(); 0 < i--; ) 
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

C_INT32  TestMassAction(void)
{
  string Usage;
  
  CUsageRange Src;
  Src.setRange(1,0);
  Src.setUsage("parameter");

  CUsageRange Copy(Src);
  Usage = Copy.getUsage();

  CUsageRange * pCopy = new CUsageRange(Src);
  Usage = "";
  Usage = pCopy->getUsage();
  
  CMassAction Reversible(TriTrue);
  CMassAction Irreversible(TriFalse);

  CWriteConfig WriteBuffer("TestMassAction.gps");
  Reversible.save(WriteBuffer);
  Irreversible.save(WriteBuffer);

  delete pCopy;
  return 0;
}

C_INT32  TestFunctionDB(void) 
{
  CFunctionDB FunctionDB;
  
  FunctionDB.setFilename("FunctionDB.gps");
  FunctionDB.initialize();

  CFunction * pFunction;
  pFunction = FunctionDB.findFunction("Henri-Michaelis-Menten (irreversible)");
  
  return 0;
}

C_INT32 CovertFunctionDB(void)
{
  CFunctionDB FunctionDB;
  
  FunctionDB.setFilename("FunctionDB.gps");
  FunctionDB.initialize();

  FunctionDB.findFunction("Mass action (reversible)");
  FunctionDB.findFunction("Mass action (irreversible)");

  FunctionDB.findFunction("Constant flux (irreversible)");
  FunctionDB.findFunction("Constant flux (reversible)");
  FunctionDB.findFunction("Henri-Michaelis-Menten (irreversible)");
  FunctionDB.findFunction("Reversible Michaelis-Menten");
  FunctionDB.findFunction("Substrate inhibition (rev)");
  FunctionDB.findFunction("Substrate inhibition (irr)");
  FunctionDB.findFunction("Substrate activation (irr)");
  FunctionDB.findFunction("Competitive inhibition (rev)");
  FunctionDB.findFunction("Competitive inhibition (irr)");
  FunctionDB.findFunction("Uncompetitive inhibition (rev)");
  FunctionDB.findFunction("Uncompetitive inhibition (irr)");
  FunctionDB.findFunction("Noncompetitive inhibition (rev)");
  FunctionDB.findFunction("Noncompetitive inhibition (irr)");
  FunctionDB.findFunction("Mixed inhibition (rev)");
  FunctionDB.findFunction("Mixed inhibition (irr)");
  FunctionDB.findFunction("Specific activation (rev)");
  FunctionDB.findFunction("Specific activation (irrev)");
  FunctionDB.findFunction("Catalytic activation (rev)");
  FunctionDB.findFunction("Catalytic activation (irrev)");
  FunctionDB.findFunction("Mixed activation (rev)");
  FunctionDB.findFunction("Mixed activation (irrev)");
  FunctionDB.findFunction("Hyperbolic modifier (irrev)");
  FunctionDB.findFunction("Hyperbolic modifier (rev)");
  FunctionDB.findFunction("Allosteric inhibition (MWC)");
  FunctionDB.findFunction("Allosteric inhibition (empirical)");
  FunctionDB.findFunction("Hill Cooperativity");
  FunctionDB.findFunction("Reversible Hill");
  FunctionDB.findFunction("Reversible Hill 1 modifier");
  FunctionDB.findFunction("Reversible Hill 2 modifiers");
  FunctionDB.findFunction("Uni Uni");
  FunctionDB.findFunction("Iso Uni Uni");
  FunctionDB.findFunction("Ordered Uni Bi");
  FunctionDB.findFunction("Ordered Bi Uni");
  FunctionDB.findFunction("Ordered Bi Bi");
  FunctionDB.findFunction("Ping Pong Bi Bi");

  CWriteConfig out("FunctionDBnew.gps");
  FunctionDB.save(out);
  return 0;
}

C_INT32 TestRandom(C_INT32 num_points, C_INT32 num_bins)
{
    C_INT32 npoints = num_points;
    C_INT32 nbins = num_bins;
    cout << "Testing random number generator\n\n";
    cout << "Dropping " << npoints << " points into " << nbins << " bins.\n";

    // initialize the rng
    CRandom generator;
    vector <C_INT32> store;
    for (C_INT32 i = 0; i < nbins; i++)
    {
        store.push_back(0);
    }
    vector <C_FLOAT64> random_nums;
    C_INT32 j = 0;
    for (j = 0; j < npoints; j++)
    {
        C_FLOAT64 rnd = generator.getUniformRandom();
        C_INT32 k = static_cast<C_INT32> (rnd * nbins);
        if (k >= nbins) {cout << " k too big \n"; exit(2);}
        else if (k < 0.0) {cout << " k too small \n"; exit(2);}
        store[k] += 1;
        random_nums.push_back(rnd);
    }
    ofstream fout("test_random.dat");
    cout << "Generated " << j << " points\n";
    fout << "# Generated " << j << " points\n";
    C_FLOAT64 min = pow(2.0,63), max = 0, mean = 0;
    for (C_INT32 l = 0; l < nbins; l++)
    {
        fout << l << "  " << store[l] << endl;
        if (store[l] > max) max = store[l];
        if (store[l] < min) min = store[l];
        mean += store[l];
    }
    cout << "Total points = " << setprecision (12) << mean << endl,
    mean = mean / nbins;
    C_FLOAT64 deviation = ((max - mean) > (mean - min))?(max-mean):(mean-min);
    deviation = deviation / mean;
    cout << "Average = " << setprecision (12) << mean << "  Deviation = " << deviation << endl;
    fout << "#Average = " << setprecision (12) << mean << "  Deviation = " << deviation << endl;

    // Check for repeats
    cout << "Searching for repeats...\n";
    vector<C_FLOAT64>::iterator it = random_nums.begin();
    C_FLOAT64 tmp;
    C_INT32 repeats = 0;
    C_INT32 cnt = 0;
    while (it != random_nums.end())
    {
        tmp = *it;
        if (find(random_nums.begin(), random_nums.end(), tmp) != it)
        {
            repeats++;
            CCopasiMessage(CCopasiMessage::WARNING, " Testing random generator: found %d'th repeat value = %g at  pos %d", repeats, *it, cnt);
        }
        cnt++;
        it++;
    }
    if (repeats)
    {
        CCopasiMessage(CCopasiMessage::ERROR, "Testing random number generator: found %d repeats in %d numbers\n", repeats, npoints);
    }
    else
    {
        cout << "Random number generator test: Success - No repeats found" << endl;
    }
    return 0;
}

C_INT32 TestDependencyGraph()
{
    cout << "Testing dependency graph\n";
    const unsigned C_INT32 NNODES = 4;
    const unsigned C_INT32 NDEPS = 4;
    C_INT32 inarr[NNODES][NDEPS] = {{0,1,2,0},
                                     {1,1,3,0},
                                     {2,3,0,1},
                                     {3,0,1,2}};
    CDependencyGraph dg;
    unsigned C_INT32 i=0, j=0;
    for (i = 0; i < NNODES; i++)
    {
        cout << "Adding node " << i << " with dependents ";
        dg.addNode(i);
        for(j = 0; j < NDEPS; j++)
        {
            cout << inarr[i][j] << " ";
            dg.addDependent(i, inarr[i][j]);
        }
        cout << endl;
    }
    // Display the vector of dependents for each node
    for (i = 0; i < NNODES; i++)
    {
        j = 0;
        cout << "Node: " << i << " Dependents: ";
        vector<C_INT32> depvec = dg.getDependents(i);
        while (j < depvec.size())
        {
            cout << depvec[j] << " ";
            j++;
        }
        cout << endl;
    }
    cout <<  "Done testing dependency graph\n\n";
    return 0;
}

C_INT32 TestIndexedPriorityQueue(C_INT32 in_size)
{
    cout << "Testing CIndexedPriorityQueue\n";
    int size = in_size;
    cout << "Creating priority queue of size " << size << endl;
    CIndexedPriorityQueue pq;
    CRandom *rand = new CRandom(1);
    C_FLOAT64 rndval;
    cout << "Unordered input:\n";
    for (int i = 0; i < size ; i++)
    {
        rndval = rand->getUniformRandom();
        cout << "element " << i << ":" << rndval << endl;
        pq.pushPair(i, rndval);
    }
    cout << "Building heap\n";
    pq.buildHeap();
    // Display the priority queue
    cout << "\nPriority Queue:\n";
    for (int j = 0; j < size; j++) 
    {
        cout << " " << j << "-" << setprecision (5) << pq[j];
    }
    cout << endl;
    cout << "Testing update node\n";
    for (int i = 0; i < size; i++)
    {
        cout << "Reset node at top index: ";
        pq.updateNode(pq.topIndex(), 10000);
        cout << "New queue = ";
        for (int j = 0; j < size; j++) cout << " " << j << "-" << setprecision(5) << pq[j] << setprecision(6);
        cout << endl;
    }
    cout << "Done testing CIndexedPriorityQueue\n\n";    
    return 0;
}

C_INT32 TestSpec2Model()
{
    cout << "Testing CSpec2Model\n";
    string filename = "exampleinput";
    CSpec2Model specreader(filename);
    CModel *model;
    // create a model
    model = specreader.createModel();
    // Test that we read the input file correctly
    specreader.printInput();
    cout << "Done testing CSpec2Model\n";
    return 0;
}
