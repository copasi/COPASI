
// Main
//
// (C) Pedro Mendes 2000
//

#define COPASI_MAIN
#include "copasi.h"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
#include <algorithm>

#include "utilities/CCopasiMessage.h"
#include "utilities/CCopasiException.h"
#include "utilities/CVersion.h"
#include "utilities/CCopasiVector.h"
#include "utilities/CDependencyGraph.h"
#include "utilities/CIndexedPriorityQueue.h"

#include "utilities/readwrite.h"
#include "elementaryFluxModes/CElementaryFluxModes.h"
#include "model/model.h"
#include "model/CSpec2Model.h"
#include "output/output.h"
#include "function/CMassAction.h"
#include "function/CFunctionDB.h"
#include "optimization/COptMethod.h"
#include "optimization/CRealProblem.h"
#include "utilities/CGlobals.h"
#include "randomGenerator/CRandom.h"
#include "trajectory/CTrajectoryTask.h"
#include "steadystate/CSteadyStateTask.h"
#include "steadystate/CEigen.h"
#include "steadystate/CMca.h"
#include "randomGenerator/CRandom.h"
#include "utilities/CluX.h"
#include "report/CCopasiObjectName.h"

#include "mathmodel/CMathModel.h"
#include "utilities/CCopasiNode.h"
#include "utilities/CCopasiTree.h"
#include "mathmodel/CMathNode.h"
#include "xml/CCopasiXMLInterface.h"
#include "xml/CCopasiXML.h"

using namespace std;

C_INT32 TestReadConfig(void);
C_INT32 TestWriteConfig(void);
C_INT32 TestCompartment(void);
C_INT32 TestCopasiTree(void);
C_INT32 TestException(void);
C_INT32 TestDatum(void);
C_INT32 TestMetab(void);
C_INT32 TestMessage(void);
C_INT32 TestReadSample(void);
C_INT32 TestMoiety(void);
C_INT32 TestKinFunction(void);
C_INT32 TestFunctionDB(void);
C_INT32 TestMassAction(void);
C_INT32 TestBaseFunction(void);
C_INT32 TestModel(void);
C_INT32 TestMathModel(void);
C_INT32 TestLU();
C_INT32 TestLSODA(void (*f)(C_INT32, C_FLOAT64, C_FLOAT64 *, C_FLOAT64 *));
C_INT32 TestTrajectory(void);
C_INT32 TestTrajectoryTask(void);
C_INT32 TestNewton(void);
C_INT32 TestSSSolution(void);
C_INT32 TestEigen(void);
C_INT32 TestOptimization(void);     //yohe: new
C_INT32 TestElementaryFluxMode(void);
C_INT32 Testr250(void);
C_INT32 Testmt19937(void);
C_INT32 TestCopasiObject(void);
C_INT32 ConvertFunctionDB(void);
C_INT32 MakeFunctionDB(void);
C_INT32 MakeFunctionEntry(const string &name,
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
C_INT32 TestCopasiXML();

int main(int argc, char *argv[])
{
  cout << "Starting main program." << endl;
  CCopasiContainer::init();
  Copasi = new CGlobals;
  Copasi->setArguments(argc, argv);

  try
    {
#ifdef WIN32
      cout << "sizeof(long long) = " << sizeof(__int64) << endl;
#else

      cout << "sizeof(long long) = " << sizeof(long long) << endl;
#endif

      cout << "sizeof(long) = " << sizeof(long) << endl;
      cout << "sizeof(int) = " << sizeof(int) << endl;
      cout << "sizeof(short) = " << sizeof(short) << endl;
      cout << "sizeof(double) = " << sizeof(double) << endl;
      cout << "sizeof(float) = " << sizeof(float) << endl;

      //      TestException();
      //      TestMessage();

      //      TestWriteConfig();
      //      TestReadConfig();
      //      TestCompartment();
      //      TestDatum();
      //      TestMetab();
      //      TestReadSample();
      //      TestNewton();
      //      TestSSSolution();
      //YOHE: new test
      TestOptimization();
      //      TestEigen();
      //      TestCopasiTree();
      //      TestTrajectory();
      //      TestTrajectoryTask();
      //      TestMoiety();
      //      TestKinFunction();
      //      TestMassAction();
      //      TestFunctionDB();
      //      TestBaseFunction();
      //      TestModel();
      //      TestMathModel();
      //      TestLU();
      //      TestMCA();
      //      TestOutputEvent();
      //      MakeFunctionDB();
      //      ConvertFunctionDB();
      //      TestRandom(10000, 100);
      //      Testr250();
      //      Testmt19937();
      //      TestCopasiObject();

      //      TestDependencyGraph();
      //      TestIndexedPriorityQueue(7);
      //      TestSpec2Model();

      //      TestElementaryFluxMode();

      //      TestCopasiXML();
    }

  catch (CCopasiException Exception)
    {
      cout << Exception.getMessage().getText() << endl;
    }

  pdelete(Copasi);
  pdelete(CCopasiContainer::Root);

  cout << "Leaving main program." << endl;
  return 0;
}

C_INT32 TestMessage(void)
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

C_INT32 TestException()
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

  catch (char * C_UNUSED(str))
    {
      cout << "Caugth other exception" << endl;
    }

  cout << endl;
  return 0;
}

C_INT32 TestReadConfig(void)
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

C_INT32 TestWriteConfig(void)
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

C_INT32 TestCopasiObject(void)
{
  std::map< const std::string, CMetab * > myMap;
  CMetab m1, m2;
  myMap[m1.getName()] = &m1;
  myMap[m1.getName()] = &m1;
  myMap[m2.getName()] = &m2;

  CCopasiObjectName Name("CN=Root,Vector=Metabolites\\[ADH\\],Metabolite=ADH");
  cout << Name << endl;
  cout << CCopasiObjectName::unescape(Name) << endl;

  Name = (std::string) "CN=Root\\,Vector=Metabolites[ADH],Metabolite=ADH";
  cout << Name.getPrimary() << endl;
  cout << Name.getRemainder() << endl;

  Name = (std::string) "CN=Root\\\\,Vector=Metabolites[ADH],Metabolite=ADH";
  cout << Name.getPrimary() << endl;
  cout << Name.getRemainder() << endl;

  Name = (std::string) "Vector=Metabolites[ADH],Metabolite=ADH";
  cout << Name.getPrimary() << endl;
  cout << Name.getObjectType() << endl;
  cout << Name.getObjectName() << endl;
  cout << Name.getName() << endl;
  cout << Name.getIndex() << endl;
  cout << Name.getRemainder() << endl;

  Name = (std::string) "Vector=Metabolites[7A],Metabolite=ADH";
  cout << Name.getPrimary() << endl;
  cout << Name.getObjectType() << endl;
  cout << Name.getObjectName() << endl;
  cout << Name.getName() << endl;
  cout << Name.getIndex() << endl;
  cout << Name.getRemainder() << endl;

  Name = (std::string) "Vector=Metabolites[A 7],Metabolite=ADH";
  cout << Name.getPrimary() << endl;
  cout << Name.getObjectType() << endl;
  cout << Name.getObjectName() << endl;
  cout << Name.getName() << endl;
  cout << Name.getIndex() << endl;
  cout << Name.getRemainder() << endl;

  Name = (std::string) "Vector=Metabolites[27],Metabolite=ADH";
  cout << Name.getPrimary() << endl;
  cout << Name.getObjectType() << endl;
  cout << Name.getObjectName() << endl;
  cout << Name.getName() << endl;
  cout << Name.getIndex() << endl;
  cout << Name.getName(1) << endl;
  cout << Name.getIndex(1) << endl;
  cout << Name.getRemainder() << endl;

  Name = (std::string) "Vector=Metabolites[2][7],Metabolite=ADH";
  cout << Name.getPrimary() << endl;
  cout << Name.getObjectType() << endl;
  cout << Name.getObjectName() << endl;
  cout << Name.getName() << endl;
  cout << Name.getIndex() << endl;
  cout << Name.getName(1) << endl;
  cout << Name.getIndex(1) << endl;
  cout << Name.getRemainder() << endl;

  Name = (std::string) "Vector=Metabolites,Metabolite=ADH";
  cout << Name.getPrimary() << endl;
  cout << Name.getObjectType() << endl;
  cout << Name.getObjectName() << endl;
  cout << Name.getName() << endl;
  cout << Name.getIndex() << endl;
  cout << Name.getRemainder() << endl;

  CReadConfig inbuf("gps/NewtonTest.gps");
  inbuf.getDefaults();

  CModel model;
  model.load(inbuf);
  model.compile();

  CCopasiObjectName cn = model.getCompartments()["compartment"]->getCN();

  cout << cn << endl;

  CCompartment * pCompartment =
    (CCompartment *) (CCopasiContainer *) CCopasiContainer::Root->getObject(cn);

  cout << *pCompartment << endl;
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

  CCopasiVectorNS < CCompartment > d;
  d.add(&c);

  CCompartment g;
  g.setName("test2");
  g.setVolume(1.1e-2);

  d.add(&g);
  d[1]->save(of);
  of.flush();

  CReadConfig Specific("TestCompartment.txt");

  CCopasiVectorNS < CCompartment > ListOut;

  ListOut.load(Specific, 2);

  CWriteConfig VectorOut((string) "TestCompartmentVector.txt");
  ListOut.save(VectorOut);
  VectorOut.flush();

  CCopasiVectorNS < CCompartment > ListIn;

  CReadConfig VectorIn((string) "TestCompartmentVector.txt");

  ListIn.load(VectorIn, 2);

  cout << endl;
  return 0;
}

C_INT32 TestDatum(void)
{
  cout << "Entering TestDatum." << endl;
  C_FLOAT64 doublevariable;
  cout << "creating a CDatum object..." << endl;
  CDatum d((string)"[medicarpin]t",
           &doublevariable,
           D_TCONC,
           (string)"medicarpin");
  cout << "Opening an output stream" << endl;
  CWriteConfig of("TestDatum1.txt");
  d.save(of);
  of.flush();

  CReadConfig Specific((string) "TestDatum1.txt");

  CDatum e0;
  e0.load(Specific);

  CDatum e1(e0);
  cout << "Opening another output stream" << endl;
  CWriteConfig of2("TestDatum2.txt");
  e1.save(of2);

  cout << endl;
  return 0;
}

C_INT32 TestReadSample(void)
{
  C_INT32 size = 0;
  CMatrix< C_FLOAT64 > LU;
  CReadConfig inbuf("gps/bakker.gps");
  CModel model;
  model.load(inbuf);
  model.buildStoi();
  model.lUDecomposition(LU);
  model.setMetabolitesStatus(LU);
  model.buildRedStoi();
  model.buildMoieties();

  size = model.getMetabolitesInd().size();
  C_FLOAT64 *y;
  y = new double[size];

  CWriteConfig outbuf("copasi.gps");
  model.save(outbuf);
  outbuf.flush();

  Copasi->pFunctionDB->cleanup();

  CReadConfig inbuf2("copasi.gps");
  CModel model2;
  model2.load(inbuf2);

  CWriteConfig outbuf2("copasi2.gps");
  model2.save(outbuf2);
  outbuf2.flush();

  return 0;
}

C_INT32 TestCopasiTree(void)
{
  CCopasiTree< CMathNode > * tree = new CCopasiTree< CMathNode >;
  CCopasiTree< CMathNode >::iterator it;
  CCopasiTree< CMathNode >::iterator end = tree->end();

  CMathNode * n0 = new CMathNode();
  CMathNode * n1 = new CMathNode();
  CMathNode * n2 = new CMathNode();
  CMathNode * n3 = new CMathNode();
  CMathNode * n4 = new CMathNode();

  std::cout << tree->attachNode(n0) << std::endl;
  std::cout << tree->attachNode(n1) << std::endl;
  std::cout << tree->attachNode(n4, n0) << std::endl;
  std::cout << tree->attachNode(n2, n0, n0) << std::endl;
  std::cout << tree->attachNode(n3, n0, n2) << std::endl;

  for (it = tree->begin(); it != end; ++it)
    std::cout << &*it << " ";
  std::cout << std::endl;

  std::cout << tree->moveNode(n0) << std::endl;

  for (it = tree->begin(); it != end; ++it)
    std::cout << &*it << " ";
  std::cout << std::endl;

  delete tree;

  return 0;
}

C_INT32 TestTrajectory(void)
{
  string InputFile(Copasi->Arguments[1]);
  string OutputFile(Copasi->Arguments[2]);
  CReadConfig inbuf(InputFile);
  inbuf.getDefaults();
  CWriteConfig outbuf(OutputFile);
  outbuf.setDefaults();
  CModel model;

  // COutput output;
  // output.load(inbuf);

  model.load(inbuf);
  model.compile();
  model.save(outbuf);

  CMathModel MathModel;
  MathModel.setModel(&model);

  Copasi->pOutputList->load(inbuf);
  Copasi->pOutputList->save(outbuf);

  CTrajectoryTask traj;
  //traj.setModel(&model);
  traj.load(inbuf);
  traj.save(outbuf);
  //  traj.initialize();
  // traj.getODESolver()->load(inbuf);
  //  ofstream output("output.txt");

  //  cout << "Running trajectory\n";
  //  traj.process(output);
  //traj.cleanup();

  return 0;
}

C_INT32 TestTrajectoryTask(void)
{
  string InputFile(Copasi->Arguments[1]);
  string OutputFile(Copasi->Arguments[2]);

  CReadConfig inbuf(InputFile);
  CWriteConfig outbuf(OutputFile);

  CModel model;

  model.load(inbuf);
  model.compile();
  model.save(outbuf);

  Copasi->pOutputList->load(inbuf);

  // COutput Output;
  // Output.resetConfiguration();
  // Output.setDynConfiguration(1);
  // Output.addDatum("Time-course output", "X(t)", 3, "X");
  // Output.addDatum("Time-course output", "Y(t)", 3, "Y");
  // Output.addDatum("Time-course output", "time", 14);
  // Copasi->OutputList.addOutput(Output);

  Copasi->pOutputList->save(outbuf);

  CTrajectoryTask traj;
  traj.load(inbuf);
  traj.save(outbuf);

  // define a task without loading
  // CTrajectoryTask traj(&model, 0, 1000, 2000, CTrajectoryMethod::stochastic);
  // traj.save(outbuf);

  outbuf.flush();

  ofstream output("output.txt");
  traj.initializeReporting(output);
  traj.process();
  //traj.cleanup();

  ofstream output2("output2.txt");
  traj.initializeReporting(output2);
  traj.process();
  //traj.cleanup();

  return 0;
}

C_INT32 TestMCA(void)
{
  CMatrix< C_FLOAT64 > LU;
  cout << "Entering TestReport." << endl;

  CReadConfig inbuf("gps/DANNY.gps");

  CModel model;
  model.load(inbuf);
  model.buildStoi();
  model.lUDecomposition(LU);
  model.setMetabolitesStatus(LU);
  model.buildRedStoi();

  CMca mMCA();
  return 0;
}

// by YH
C_INT32 TestSSSolution(void)
{
  string InputFile(Copasi->Arguments[1]);
  string OutputFile(Copasi->Arguments[2]);

  CReadConfig inbuf(InputFile);
  CWriteConfig outbuf(OutputFile);

  CModel model;
  model.load(inbuf);
  model.compile();

  Copasi->pOutputList->load(inbuf);

  CSteadyStateTask ss_soln;
  ss_soln.load(inbuf);
  //  ss_soln.setModel(&model);

  ofstream output("output.txt");
  ss_soln.initializeReporting(output);
  ss_soln.getMethod()->getValue(0);

  ss_soln.process();

  return 0;
}

//by YH
//first, test matrix A = [-1 4 -2; -3 4 0; -3 1 3].
//the eig(A)=[1.0 2.0 3.0].
//
C_INT32 TestEigen(void)
{
  cout << endl << "Begin to TestEigen ..." << endl << endl;
  cout << "Note: Testing Sample: matrix[-1 4 -2; -3 4 0; -3 1 3]" << endl;
  cout << "Note: According MatLab, the result for the sample: eig(A)=[1.0 2.0 3.0]" << endl;
  cout << "--- The results from my program are  shown below:" << endl;

  CEigen myEigen;

  CMatrix< C_FLOAT64 > matrix(3, 3);
  matrix[0][0] = -1; matrix[0][1] = 4; matrix[0][2] = -2;
  matrix[1][0] = -3; matrix[1][1] = 4; matrix[1][2] = 0;
  matrix[2][0] = -3; matrix[2][1] = 1; matrix[2][2] = 3;
  //initialize matrix
  //TNT::Matrix<C_FLOAT64> matrix=[-1 4 -2; -3 4 0; -3 1 3];
  // SSResoltion=1.000000e-009 (from NewtonTest_yhtest.gps)
  C_FLOAT64 ssRes = 0.0;

  myEigen.calcEigenValues(matrix);
  myEigen.stabilityAnalysis(ssRes);

  cout << "!!! Yongqun Testing: the max eigenvalue real part is: " << myEigen.getEigen_maxrealpart() << endl;
  cout << "!!! Yongqun Testing: the max eigenvalue imag part is: " << myEigen.getEigen_maximagpart() << endl;
  cout << "!!! Yongqun Testing: the stiffness  is: " << myEigen.getEigen_stiffness() << endl;
  cout << "!!! Yongqun Testing: the eigen hierarchy is: " << myEigen.getEigen_hierarchy() << endl;
  cout << "!!! Yongqun Testing: the number of positive real  is: " << myEigen.getEigen_nposreal() << endl;
  cout << "!!! Yongqun Testing: the num of negative real is: " << myEigen.getEigen_nnegreal() << endl << endl;

  cout << "Leaving TestEigen() function ..." << endl << endl;

  return 0;
}

//rohan: test optimization -- 09/20/02
//
C_INT32 TestOptimization(void)
{
  int i;
  int NumParameter = 5;
  int MethodType;
  //double RangeParameter[NumParameter][2];
  cout << "TestOptimization() begins --- " << endl;
  // COptMethod * CRand = COptMethod::createMethod();
  //  COptMethod * CRand = COptMethod::createMethod(COptMethod::SimulatedAnnealing);
  COptMethod * CRand = COptMethod::createMethod(COptMethod::GeneticAlgorithm);

  CRealProblem *CReal = new CRealProblem();
  CRand->setProblem(CReal);
  //CRandom *testRand = new CRandom(2);
  //CRandom *rand;
  //CRandom::Type t;
  //t=CRandom::r250;
  //rand = CRandom::createGenerator(t,2);

  // set parameter numbers....
  CReal->setParameterNum(NumParameter);

  // set the individual parameters

  //CRand->setValue(0, 100000.0);
  CRand->setValue(0, 10000000.0);

  for (i = 0; i < NumParameter; i++)
    {
      CReal->setParameterMin(i, -10);
      CReal->setParameterMax(i, 10);
    }

  CRand->optimise();

  MethodType = CRand->GetMethodType();
  char filename[20];
  if (MethodType == 0) sprintf(filename, "best_result.%s", "RS");
  if (MethodType == 1) sprintf(filename, "best_result.%s", "RSM");
  if (MethodType == 2) sprintf(filename, "best_result.%s", "SA");
  if (MethodType == 3) sprintf(filename, "best_result.%s", "GA");

  ofstream bestout(filename);
  if (!bestout)
    {
      cout << " output file  cannot be set!" << endl;
      exit(0);
    }

  cout << endl << "Final result and the best object function value:" << CReal->getBestValue() << endl;
  bestout << endl << "Final result and the best object function value:" << CReal->getBestValue() << endl;
  cout << NumParameter << " Parameters are as follow:" << endl;
  bestout << NumParameter << " Parameters are as follow:" << endl;
  for (i = 0; i < NumParameter; i++)
    {
      cout << CReal->getBestValue(i) << endl;
      bestout << CReal->getBestValue(i) << endl;
    }

  bestout.close();
  pdelete(CRand);
  return 0;
}

/*
 
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
 
 */

C_INT32 TestMoiety()
{
  CMoiety mo("test");
  CCompartment c;
  c.setName("comp");
  c.setVolume(1.0);

  c.getMetabolites().add(CMetab());
  c.getMetabolites().add(CMetab());

  c.getMetabolites()[0]->setName("metab 1");
  c.getMetabolites()[0]->setConcentration(5.2);
  c.getMetabolites()[1]->setName("metab 2");
  c.getMetabolites()[1]->setConcentration(2.0);

  CMetab m(*c.getMetabolites()["metab 2"]);

  mo.add(-2000, c.getMetabolites()[0]);
  mo.add(3, c.getMetabolites()[1]);
  mo.add(0, c.getMetabolites()[1]);

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
  f.setDescription("(a-b)*(a+b)/<laber>");
  f.getParameters().add("a", CFunctionParameter::FLOAT64, "UNKNOWN");
  f.getParameters().add("b", CFunctionParameter::FLOAT64, "UNKNOWN");

  f.compile();
  cout << "f(a,b) = (a-b)*(a+b)/5" << endl;

  //  f.setIdentifierType("a", N_SUBSTRATE);
  //  f.setIdentifierType("b", N_PRODUCT);

  C_FLOAT64 a = 4;
  C_FLOAT64 b = 1;

  CCallParameterPointers CallParameters;

  CallParameters.resize(2);

  CallParameters[0] = &a;
  CallParameters[1] = &b;

  C_FLOAT64 r = f.calcValue(CallParameters);

  cout << "f(a,b) = " << f.getDescription() << endl;
  cout << "f(" << a << "," << b << ") = " << r << endl;

  CWriteConfig out("TestKinFunction.gps");
  f.save(out);
  f.cleanup();

  out.flush();

  CReadConfig in("TestKinFunction.gps");
  CKinFunction g;

  g.load(in);

  a = 5;
  r = g.calcValue(CallParameters);
  cout << "f(" << a << "," << b << ") = " << r << endl;

  return 0;
}

/*
vector < CMetab * > 
InitMetabolites(CCopasiVectorN < CCompartment > & compartments)
{
  vector < CMetab * > Metabolites;
 
  for (unsigned C_INT32 i = 0; i < compartments.size(); i++)
    for (unsigned C_INT32 j = 0;
         j < compartments[i]->getMetabolites().size(); j++)
      Metabolites.push_back(compartments[i]->getMetabolites()[j]);
    
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

  if (0 <= Tuple.first && 0 <= Tuple.second)
    functions[Index]->setIdentifierType("substrate", N_SUBSTRATE);

  Tuple = functions[Index]->findIdentifier("substratea");

  if (0 <= Tuple.first && 0 <= Tuple.second)
    functions[Index]->setIdentifierType("substratea", N_SUBSTRATE);

  Tuple = functions[Index]->findIdentifier("substrateb");

  if (0 <= Tuple.first && 0 <= Tuple.second)
    functions[Index]->setIdentifierType("substrateb", N_SUBSTRATE);

  Tuple = functions[Index]->findIdentifier("product");

  if (0 <= Tuple.first && 0 <= Tuple.second)
    functions[Index]->setIdentifierType("product", N_PRODUCT);

  Tuple = functions[Index]->findIdentifier("productp");

  if (0 <= Tuple.first && 0 <= Tuple.second)
    functions[Index]->setIdentifierType("productp", N_PRODUCT);

  Tuple = functions[Index]->findIdentifier("productq");

  if (0 <= Tuple.first && 0 <= Tuple.second)
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

C_INT32 TestMathModel(void)
{
  CReadConfig inbuf("gps/YeastGlycolysis.gps");
  CModel m;
  m.load(inbuf);

  CMathModel math;
  math.setModel(&m);

  return 0;
}
C_INT32 TestLU()
{
  unsigned C_INT32 i;
  C_INT32 t;

  CMatrix < C_FLOAT64 > A(4, 3);
  CFortranAccess < CMatrix < C_FLOAT64 > > fA(A);

  fA(1, 1) = 1.0;
  fA(1, 2) = -2.0;
  fA(1, 3) = 0.0;
  fA(2, 1) = -1.0;
  fA(2, 2) = 2.0;
  fA(2, 3) = 1.0;
  fA(3, 1) = 0.0;
  fA(3, 2) = 0.0;
  fA(3, 3) = 2.0;
  fA(4, 1) = 0.0;
  fA(4, 2) = 0.0;
  fA(4, 3) = -3.0;

  vector < unsigned C_INT32 > rowLU(4);
  vector < unsigned C_INT32 > colLU(3);

  vector < C_INT32 > row(4);

  for (i = 0; i < row.size(); i++)
    row[i] = i;

  vector < C_INT32 > rowi = row;

  vector < C_INT32 > col(3);

  for (i = 0; i < col.size(); i++)
    col[i] = i;

  vector < C_INT32 > coli = col;

  cout << A << endl;

  LUfactor(A, rowLU, colLU);

  //colLU(3) = 2;

  cout << A << endl;

  //  cout << rowLU << endl;

  //  cout << colLU << endl;

  for (i = 0; i < row.size(); i++)
    {
      if (rowLU[i] > i)
        {
          t = row[i];
          row[i] = row[rowLU[i]];
          row[rowLU[i]] = t;
        }
    }

  for (i = rowi.size(); 0 < i--;)
    {
      if (rowLU[i] > i)
        {
          t = rowi[i];
          rowi[i] = rowi[rowLU[i]];
          rowi[rowLU[i]] = t;
        }
    }

  for (i = col.size(); 0 < i--;)
    {
      if (colLU[i] < i)
        {
          t = col[i];
          col[i] = col[colLU[i]];
          col[colLU[i]] = t;
        }
    }

  for (i = 0; i < coli.size(); i++)
    {
      if (colLU[i] < i)
        {
          t = coli[i];
          coli[i] = coli[colLU[i]];
          coli[colLU[i]] = t;
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

C_INT32 TestLSODA(void (*f)(C_INT32, C_FLOAT64, C_FLOAT64 *, C_FLOAT64 *))
{
  C_INT32 n = 99;
  C_FLOAT64 d = 99.99;
  C_FLOAT64 * pd = &d;

  (*f)(n, d, pd, pd);

  return 0;
}

C_INT32 TestMassAction(void)
{
  string Usage;

  CUsageRange Src;
  Src.setRange(1, 0);
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

C_INT32 ConvertFunctionDB(void)
{
  CCopasiXML xml;

  ((CCopasiXMLInterface *) &xml)->load("FunctionDB.xml");

#ifdef XXXX
  CFunctionDB FunctionDB;

  FunctionDB.setFilename("FunctionDB.gps");

  FunctionDB.findLoadFunction("Allosteric inhibition (MWC)");
  FunctionDB.findLoadFunction("Allosteric inhibition (empirical)");
  FunctionDB.findLoadFunction("Catalytic activation (irrev)");
  FunctionDB.findLoadFunction("Catalytic activation (rev)");
  FunctionDB.findLoadFunction("Competitive inhibition (irr)");
  FunctionDB.findLoadFunction("Competitive inhibition (rev)");
  FunctionDB.findLoadFunction("Constant flux (irreversible)");
  FunctionDB.findLoadFunction("Constant flux (reversible)");
  FunctionDB.findLoadFunction("Henri-Michaelis-Menten (irreversible)");
  FunctionDB.findLoadFunction("Hill Cooperativity");
  FunctionDB.findLoadFunction("Hyperbolic modifier (irrev)");
  FunctionDB.findLoadFunction("Hyperbolic modifier (rev)");
  FunctionDB.findLoadFunction("Iso Uni Uni");
  FunctionDB.findLoadFunction("Mass action (irreversible)");
  FunctionDB.findLoadFunction("Mass action (reversible)");
  FunctionDB.findLoadFunction("Mixed activation (irrev)");
  FunctionDB.findLoadFunction("Mixed activation (rev)");
  FunctionDB.findLoadFunction("Mixed inhibition (irr)");
  FunctionDB.findLoadFunction("Mixed inhibition (rev)");
  FunctionDB.findLoadFunction("Noncompetitive inhibition (irr)");
  FunctionDB.findLoadFunction("Noncompetitive inhibition (rev)");
  FunctionDB.findLoadFunction("Ordered Bi Bi");
  FunctionDB.findLoadFunction("Ordered Bi Uni");
  FunctionDB.findLoadFunction("Ordered Uni Bi");
  FunctionDB.findLoadFunction("Ping Pong Bi Bi");
  FunctionDB.findLoadFunction("Reversible Hill 1 modifier");
  FunctionDB.findLoadFunction("Reversible Hill 2 modifiers");
  FunctionDB.findLoadFunction("Reversible Hill");
  FunctionDB.findLoadFunction("Reversible Michaelis-Menten");
  FunctionDB.findLoadFunction("Specific activation (irrev)");
  FunctionDB.findLoadFunction("Specific activation (rev)");
  FunctionDB.findLoadFunction("Substrate activation (irr)");
  FunctionDB.findLoadFunction("Substrate inhibition (irr)");
  FunctionDB.findLoadFunction("Substrate inhibition (rev)");
  FunctionDB.findLoadFunction("Uncompetitive inhibition (irr)");
  FunctionDB.findLoadFunction("Uncompetitive inhibition (rev)");
  FunctionDB.findLoadFunction("Uni Uni");

  //  CWriteConfig out("FunctionDBnew.gps");
  //  FunctionDB.save(out);

  xml.setFunctionList(FunctionDB.loadedFunctions());
#endif // XXXX

  ofstream os("FunctionDB.new.xml");

  cout << "Writing XML ... ";
  xml.save(os);
  cout << "done!" << endl;
  return 0;
}

#ifdef XXXX
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

      if (k >= nbins)
      {cout << " k too big \n"; exit(2);}
      else if (k < 0.0)
      {cout << " k too small \n"; exit(2);}

      store[k] += 1;
      random_nums.push_back(rnd);
    }

  ofstream fout("test_random.dat");
  cout << "Generated " << j << " points\n";
  fout << "# Generated " << j << " points\n";
  C_FLOAT64 min = pow(2.0, 63), max = 0, mean = 0;

  for (C_INT32 l = 0; l < nbins; l++)
    {
      fout << l << "  " << store[l] << endl;

      if (store[l] > max)
        max = store[l];

      if (store[l] < min)
        min = store[l];

      mean += store[l];
    }

  cout << "Total points = " << setprecision (12) << mean << endl,
  mean = mean / nbins;
  C_FLOAT64 deviation = ((max - mean) > (mean - min)) ? (max - mean) : (mean - min);
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
#endif // XXXX

/* //-- commented out because of error...8/22
=======
 
 
C_INT32 TestDependencyGraph()
{
  cout << "Testing dependency graph\n";
  const unsigned C_INT32 NNODES = 4;
  const unsigned C_INT32 NDEPS = 4;
  C_INT32 inarr[NNODES][NDEPS] = {{0, 1, 2, 0},
                                  {1, 1, 3, 0},
                                  {2, 3, 0, 1},
                                  {3, 0, 1, 2}};
  CDependencyGraph dg;
  unsigned C_INT32 i = 0, j = 0;
 
  for (i = 0; i < NNODES; i++)
    {
      cout << "Adding node " << i << " with dependents ";
      dg.addNode(i);
 
      for (j = 0; j < NDEPS; j++)
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
      const set <C_INT32> depvec = dg.getDependents(i);
      set <C_INT32>::const_iterator jit = depvec.begin();
 
      while (jit != depvec.end())
        {
          cout << *jit << " ";
          jit++;
        }
 
      cout << endl;
    }
 
  cout << "Done testing dependency graph\n\n";
  return 0;
}
 
 */

#ifdef XXXX
C_INT32 TestIndexedPriorityQueue(C_INT32 in_size)
{
  cout << "Testing CIndexedPriorityQueue\n";
  int size = in_size;
  int i, j;
  cout << "Creating priority queue of size " << size << endl;
  CIndexedPriorityQueue pq;
  CRandom *rand = new CRandom(1);
  C_FLOAT64 rndval;
  cout << "Unordered input:\n";

  for (i = 0; i < size; i++)
    {
      rndval = rand->getUniformRandom();
      cout << "element " << i << ":" << rndval << endl;
      pq.pushPair(i, rndval);
    }

  cout << "Building heap\n";
  pq.buildHeap();
  // Display the priority queue
  cout << "\nPriority Queue:\n";

  for (j = 0; j < size; j++)
    {
      cout << " " << j << "-" << setprecision (5) << pq[j];
    }

  cout << endl;
  cout << "Testing update node\n";

  for (i = 0; i < size; i++)
    {
      cout << "Reset node at top index: ";
      pq.updateNode(pq.topIndex(), 10000);
      cout << "New queue = ";

      for (j = 0; j < size; j++)
        cout << " " << j << "-" << setprecision(5) << pq[j] << setprecision(6);

      cout << endl;
    }

  cout << "Done testing CIndexedPriorityQueue\n\n";
  return 0;
}
#endif // XXXX

C_INT32 TestSpec2Model()
{
  cout << "Testing CSpec2Model\n";
  string filename = "./copasi/model/exampleinput";
  CSpec2Model specreader(filename);
  CModel *model;

  model = specreader.createModel();

  //specreader.printInput();
  //cout << "Done testing CSpec2Model\n";

  string InputFile = "specreader_in.gps";
  string OutputFile = "specreader_out.gps";

  //CReadConfig inbuf(InputFile);
  CWriteConfig outbuf(OutputFile);

  model->compile();
  model->save(outbuf);

  COutput Output;
  Output.resetConfiguration();
  Output.setDynConfiguration(1);
  Output.addDatum("Time-course output", "X(t)", 3, "X");
  Output.addDatum("Time-course output", "Y(t)", 3, "Y");
  Output.addDatum("Time-course output", "time", 14);
  Copasi->pOutputList->addOutput(Output);

  //Copasi->OutputList.save(outbuf);

  // define a task without loading
  CTrajectoryTask traj(model, 0, 1000, 2000, CTrajectoryMethod::stochastic);
  //traj.save(outbuf);

  outbuf.flush();

  ofstream output("output.txt");
  traj.initializeReporting(output);
  traj.process();
  //traj.cleanup();

  return 0;
}

C_INT32 TestElementaryFluxMode(void)
{
  CReadConfig inbuf("gps/TestKinetics/ElementaryFluxModes.gps");
  inbuf.getDefaults();

  CModel Model;
  Model.load(inbuf);
  Model.compile();

  CElementaryFluxModes FluxModes;

  FluxModes.calculate(&Model);

  ofstream output("ElementaryFluxModes.txt");
  output << FluxModes;

  return 0;
}

C_INT32 Testr250(void)
{
  CRandom * rand = CRandom::createGenerator(CRandom::r250, 12345);

  C_INT32 i, j = 0;
  for (i = 0; i < 2000; i++)
    {
      cout << rand->getRandomU(10) << ", ";
      if (j++ == 4)
        {
          j = 0;
          cout << endl;
        }
    }

  delete rand;
  return 0;
}

C_INT32 Testmt19937(void)
{
  /*
    CRandom * rand = CRandom::createGenerator();
   
    int i;
    unsigned C_INT32 init[4] = {0x123, 0x234, 0x345, 0x456}, length = 4;
    ((Cmt19937*)rand)->init_by_array(init, length);
    printf("1000 outputs of getRandomU()\n");
    for (i = 0; i < 1000; i++)
      {
        printf("%10lu ", rand->getRandomU());
        if (i % 5 == 4)
          printf("\n");
      }
    printf("\n1000 outputs of genrand_real2()\n");
    for (i = 0; i < 1000; i++)
      {
        printf("%10.8f ", rand->getRandomCO());
        if (i % 5 == 4)
          printf("\n");
      }
  */
  return 0;
}

C_INT32 TestCopasiXML()
{
  CMetab *pM = new CMetab();
  pM = new CMetab();

  string tmp = CCopasiXMLInterface::encode("a&sdhjkl<>\"'");
  tmp = CCopasiXMLInterface::encode("мнопр");

  return 0;
}
