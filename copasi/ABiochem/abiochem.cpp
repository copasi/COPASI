/**
 *  ABiochem
 *
 *  This contains the common code for all network generators
 *  writen by Pedro Mendes, September 2002
 */

#define COPASI_MAIN // needed for anything with a main()

#include "copasi.h"

#include <iostream>
#include <fstream>
#include <string>
#include <strstream>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <stdio.h>
#include <time.h>

#include "utilities/utilities.h"
#include "elementaryFluxModes/CElementaryFluxModes.h"
#include "model/model.h"
#include "model/CSpec2Model.h"
#include "output/output.h"
#include "function/function.h"
#include "trajectory/trajectory.h"
#include "steadystate/steadystate.h"
#include "utilities/CGlobals.h"
#include "ABiochem/clo.h"
#include "ABiochem/CGene.h"
#include "ABiochem/ABiochem.h"

extern "C" void r250_init(int seed);
extern "C" unsigned int r250n(unsigned n);
extern "C" double dr250();

using namespace std;

void WriteDot(char *Title, CCopasiVector < CGene > &gene)
{
  unsigned C_INT32 i;
  C_INT32 j;
  char strtmp[1024];
  ofstream fout;

  sprintf(strtmp, "%s.dot", Title);
  fout.open(strtmp, ios::out);
  // dot file header
  fout << "digraph \"" << Title << "\" {\n";
  fout << "\tgraph\n\t[\n";
  fout << "\t\tcenter=\"true\"\n";
  fout << "\t\toverlap=\"false\"\n";
  fout << "\t\tDamping=0.999\n";
  fout << "\t\tfontname=\"Helvetica\"\n";
  fout << "\t\tmaxiter=1000000\n";
  fout << "\t\tsplines=\"true\"\n";
  fout << "\t\tsep=0.8\n";
  fout << "\t\tepsilon=0.0000001\n";
  fout << "\t\tlabel=\"" << Title << "\"\n";
  fout << "\t\tratio=\"auto\"\n";
  fout << "\t]\n\n";
  fout << "\tnode\n\t[\n";
  fout << "\t\tfontsize=9\n";
  fout << "\t\tfontname=\"Helvetica-bold\"\n";
  fout << "\t\tshape=\"circle\"\n";
  fout << "\t\tstyle=\"bold\"\n";
  fout << "\t]\n\n";
  fout << "\tedge\n\t[\n";
  fout << "\t\tfontsize=9\n";
  fout << "\t\tfontname=\"Helvetica\"\n";
  fout << "\t\tcolor=\"blue\"\n";
  fout << "\t\tarrowhead=\"normal\"\n";
  fout << "\t\tstyle=\"bold\"\n";
  fout << "\t\tlen=2.5\n";
  fout << "\t]\n\n";
  // graph description
  for (i = 0; i < gene.size(); i++)
    for (j = 0; j < gene[i]->getModifierNumber(); j++)
      {
        fout << "\t" << gene[i]->getModifier(j)->getName() << " -> " << gene[i]->getName() << endl;
        if (gene[i]->getModifierType(j) == 0)
          fout << "\t\t[arrowhead=\"tee\"\n\t\tcolor=\"red\"]" << endl;
      }
  fout << "\n}";
  fout.close();
}

void WritePajek(char *Title, CCopasiVector < CGene > &gene)
{
  C_INT32 i, j, l, size;
  char strtmp[1024];
  ofstream fout;

  size = gene.size();
  sprintf(strtmp, "%s.net", Title);
  fout.open(strtmp, ios::out & ~ios::binary);
  fout << "*Network " << Title << endl;
  fout << "*Vertices " << size << endl;
  for (i = 0; i < size; i++)
    fout << i + 1 << " \"" << gene[i]->getName() << "\"" << endl;
  fout << "*Arcs" << endl;
  for (i = 0; i < size; i++)
    for (j = 0; j < gene[i]->getModifierNumber(); j++)
      for (l = 0; l < size; l++)
        if (gene[i]->getModifier(j) == gene[l])
          fout << l + 1 << " " << i + 1 << " 1 c " << (gene[i]->getModifierType(j) == 0 ? "Red" : "Blue") << endl;
  fout.close();
}

void WriteDistri(char *Title, CCopasiVector < CGene > &gene)
{
  C_INT32 i, size;
  char strtmp[1024];
  ofstream fout;
  vector < C_INT32 > idegree, odegree, tdegree;

  size = gene.size();
  // create a vector to count all the degrees
  // there are N or less degrees
  // (this could be more efficient on memory done in a different way...)
  idegree.resize(size + 1);
  odegree.resize(size + 1);
  tdegree.resize(size + 1);
  for (i = 0; i <= size; i++)
    {
      idegree[i] = 0;
      odegree[i] = 0;
      tdegree[i] = 0;
    }
  // count!
  for (i = 0; i < size; i++)
    {
      idegree[gene[i]->getInDegree()]++;
      odegree[gene[i]->getOutDegree()]++;
      tdegree[gene[i]->getTotalDegree()]++;
    }
  // now write the data in a gnuplot file
  sprintf(strtmp, "%s.distri.plt", Title);
  fout.open(strtmp, ios::out);
  fout << "set data style linespoints" << endl;
  fout << "set linestyle 1 lw 2\nset linestyle 2 lw 2\nset linestyle 3 lw 2" << endl;
  fout << "set title \'degree distribution for " << Title << "'" << endl;
  fout << "set xlabel \'# of links\'" << endl;
  fout << "set ylabel \'comulative distribution\'" << endl;
  fout << "plot \'-\' t \'in-degree\' ls 1, \'-\' t \'out-degree\' ls 2, \'-\' t \'all-degree\' ls 3" << endl;
  for (i = 0; i <= size; i++)
    fout << i << "\t" << idegree[i] << endl;
  fout << "e" << endl;
  for (i = 0; i <= size; i++)
    fout << i << "\t" << odegree[i] << endl;
  fout << "e" << endl;
  for (i = 0; i <= size; i++)
    fout << i << "\t" << tdegree[i] << endl;
  fout << "e" << endl;
  fout.close();
}

void MakeModel(char *Title, char *comments, CCopasiVector < CGene > &gene, C_INT32 n, C_INT32 k, CModel &model)
{
  C_INT32 i, j, r, s, pos, neg;
  char strname[512], strname2[512], streq[512];
  string compname = "cell", rname, rchemeq, kiname;
  CReaction *react;
  CReaction::CId2Metab id2metab;
  CReaction::CId2Param id2param;
  // two reactions per gene
  r = 2 * n;
  // set the title and comments
  model.setTitle(Title);
  sprintf(comments, "Model of a random gene network following a Erdos-Renyi topology\nwith %ld genes and %ld input connections each.\n\nCreated automatically by the A-Biochem system", n, k);
  model.setComments(comments);
  // add one compartment to the model
  model.addCompartment(compname, 1.0);
  // create one metabolite for each gene
  for (i = 0; i < n; i++)
    model.addMetabolite(compname, gene[i]->getName(), 1.0, 1);
  model.initializeMetabolites();
  // create two reactions for each gene
  for (i = 0; i < n; i++)
    {
      // transcription
      sprintf(strname, "%s synthesis", gene[i]->getName().data());
      sprintf(streq, "-> %s", gene[i]->getName().data());
      rname = strname;
      rchemeq = streq;
      react = new CReaction(rname);
      if (react == NULL)
        {
          fprintf(stderr, "Failed to create a CReaction object");
          abort();
        }
      react->setChemEq(streq);
      react->compileChemEq(model.getCompartments());
      sprintf(strname, "basal %ld inh %ld act (indp)", gene[i]->getNegativeModifiers(),
              gene[i]->getPositiveModifiers());
      kiname = strname;
      react->setFunction(kiname);
      s = gene[i]->getModifierNumber();
      id2metab.setCompartmentName(compname);
      for (j = 0, pos = neg = 1; j < s; j++)
        {
          if (gene[i]->getModifierType(j) == 0)
            sprintf(strname, "I%ld", neg++);
          else
            sprintf(strname, "A%ld", pos++);
          id2metab.setIdentifierName(strname);
          id2metab.setMetaboliteName(gene[i]->getModifier(j)->getName());
          react->getId2Modifiers().add(id2metab);
        }
      // first the basal rate
      id2param.setIdentifierName("V");
      id2param.setValue(gene[i]->getRate());
      react->getId2Parameters().add(id2param);
      // we have two more constants per modifier
      for (j = 0, pos = neg = 1; j < s; j++)
        {
          if (gene[i]->getModifierType(j) == 0)
            {
              sprintf(strname, "Ki%ld", neg);
              sprintf(strname2, "ni%ld", neg++);
            }
          else
            {
              sprintf(strname, "Ka%ld", pos);
              sprintf(strname2, "na%ld", pos++);
            }
          id2param.setIdentifierName(strname);
          id2param.setValue(gene[i]->getK(j));
          react->getId2Parameters().add(id2param);
          id2param.setIdentifierName(strname2);
          id2param.setValue(gene[i]->getn(j));
          react->getId2Parameters().add(id2param);
        }
      model.addReaction(react);
      // mRNA degradation
      sprintf(strname, "%s degradation", gene[i]->getName().data());
      sprintf(streq, "%s ->", gene[i]->getName().data());
      rname = strname;
      rchemeq = streq;
      react = new CReaction(rname);
      if (react == NULL)
        {
          fprintf(stderr, "Failed to create a CReaction object");
          abort();
        }
      react->setChemEq(streq);
      react->compileChemEq(model.getCompartments());
      kiname = "Mass action (irreversible)";
      react->setFunction(kiname);
      // first the kinetic constant
      id2param.setIdentifierName("k1");
      id2param.setValue(gene[i]->getDegradationRate());
      react->getId2Parameters().add(id2param);
      // now the substrate
      id2metab.setIdentifierName("substrate_0");
      id2metab.setMetaboliteName(gene[i]->getName());
      react->getId2Substrates().add(id2metab);
      model.addReaction(react);
    }
  // structural analysis (moieties, etc.)
  model.compile();
}

void MakeKinType(CFunctionDB &db, C_INT32 k, C_INT32 p)
{
  C_INT32 i, j;
  CKinFunction *funct;
  char tmpstr[2048];
  string kiname, pname;
  string equation;

  // make name
  sprintf(tmpstr, "basal %ld inh %ld act (indp)", k - p, p);
  kiname = tmpstr;
  if (db.findFunction(kiname) == NULL)
    {
      // not yet in the DB, so add it
      funct = new CKinFunction();
      if (funct == NULL)
        return;
      funct->setName(kiname);
      funct->setReversible(TriFalse);
      equation = "V/(";
      for (i = 0, j = 1; i < p; i++, j++)
        {
          if (i == 0)
            sprintf(tmpstr, "(1+Ka%ld/A%ld)^na%ld", j, j, j);
          else
            sprintf(tmpstr, "*(1+Ka%ld/A%ld)^na%ld", j, j, j);
          equation += tmpstr;
        }
      for (j = 1; i < k; i++, j++)
        {
          if (i == 0)
            sprintf(tmpstr, "(1+I%ld/Ki%ld)^ni%ld", j, j, j);
          else
            sprintf(tmpstr, "*(1+I%ld/Ki%ld)^ni%ld", j, j, j);
          equation += tmpstr;
        }
      equation += ")";
      funct->setDescription(equation);
      funct->addUsage("SUBSTRATES", 0, CRange::NoRange);
      funct->addUsage("PRODUCTS", 1, CRange::NoRange);
      pname = "V";
      funct->addParameter(pname, CFunctionParameter::FLOAT64, "PARAMETER");
      for (i = 0, j = 1; i < p; i++, j++)
        {
          sprintf(tmpstr, "Ka%ld", j);
          pname = tmpstr;
          funct->addParameter(pname, CFunctionParameter::FLOAT64, "PARAMETER");
          sprintf(tmpstr, "na%ld", j);
          pname = tmpstr;
          funct->addParameter(pname, CFunctionParameter::FLOAT64, "PARAMETER");
          sprintf(tmpstr, "A%ld", j);
          pname = tmpstr;
          funct->addParameter(pname, CFunctionParameter::FLOAT64, "MODIFIER");
        }
      for (j = 1; i < k; i++, j++)
        {
          sprintf(tmpstr, "Ki%ld", j);
          pname = tmpstr;
          funct->addParameter(pname, CFunctionParameter::FLOAT64, "PARAMETER");
          sprintf(tmpstr, "ni%ld", j);
          pname = tmpstr;
          funct->addParameter(pname, CFunctionParameter::FLOAT64, "PARAMETER");
          sprintf(tmpstr, "I%ld", j);
          pname = tmpstr;
          funct->addParameter(pname, CFunctionParameter::FLOAT64, "MODIFIER");
        }
      funct->compile();
      db.add(funct);
    }
}

void WriteGepasi(char *Title, CModel &model)
{
  string linein;
  linein.reserve(100);
  char strtmp[1024], mtitle[512];
  ofstream fout;
  CWriteConfig *modelBuff;
  C_INT32 i, nmetab;
  vector < CMetab * > Metab;

  nmetab = model.getTotMetab();
  Metab = model.getMetabolites();
  sprintf(mtitle, "%s.gps", Title);
  // first part of the file come from a template
  ifstream fin("template.gps");
  if (!fin.is_open())
    return;
  fout.open(mtitle, ios::out | ios::trunc);
  getline(fin, linein);
  do
    {
      fout << linein << endl;
      getline(fin, linein);
    }
  while (linein.find("ReportFile=") != 0);
  sprintf(strtmp, "ReportFile=%s.txt", Title);
  fout << strtmp << endl;
  sprintf(strtmp, "DynamicsFile=%s.dyn", Title);
  fout << strtmp << endl;
  sprintf(strtmp, "SSFile=%s.ss", Title);
  fout << strtmp << endl;
  //  fout.flush();
  fout.close();
  // output the model
  modelBuff = new CWriteConfig (mtitle, ios::app);
  model.saveOld(*modelBuff);
  delete modelBuff;
  // last part also comes from the template
  do
    {
      getline(fin, linein);
    }
  while (linein.find("PlotType=") != 0);
  fout.open(mtitle, ios::app);
  do
    {
      fout << linein << endl;
      getline(fin, linein);
    }
  while (linein.find("PlotXEntry=") != 0);
  // plot entries are coded dynamically (to plot all metabolites)
  fout << "PlotXEntry=0" << endl;
  sprintf(strtmp, "PlotYTotal=%ld\nPlotZTotal=1", nmetab);
  fout << strtmp << endl;
  for (i = 0; i < nmetab; i++)
    {
      sprintf(strtmp, "PlotY%ld=%ld", i, i + 1);
      fout << strtmp << endl;
    }
  fout << "PlotZ0=-1" << endl;
  do
    {
      getline(fin, linein);
    }
  while (linein.find("User-defined functions") != 0);
  do
    {
      fout << linein << endl;
      getline(fin, linein);
    }
  while (linein.find("Time-course output") != 0);
  // output entries are coded dynamically (to plot all metabolites)
  fout << "Time-course output" << endl;
  sprintf(strtmp, "Items=%ld\nTitle=time\nType=14", nmetab + 1);
  fout << strtmp << endl;
  for (i = 0; i < nmetab; i++)
    {
      sprintf(strtmp, "Title=[%s]t\nType=3\nI=%s", Metab[i]->getName().data(), Metab[i]->getName().data());
      fout << strtmp << endl;
    }
  fout << "Steady-state output" << endl;
  sprintf(strtmp, "Items=%ld", nmetab);
  fout << strtmp << endl;
  for (i = 0; i < nmetab; i++)
    {
      sprintf(strtmp, "Title=[%s]ss\nType=2\nI=%s", Metab[i]->getName().data(), Metab[i]->getName().data());
      fout << strtmp << endl;
    }
  do
    {
      getline(fin, linein);
    }
  while (linein.find("Scan") != 0);
  do
    {
      fout << linein << endl;
      getline(fin, linein);
    }
  while (!fin.eof());
  fout.close();
  fin.close();
}

C_INT main(C_INT argc, char *argv[])
{
  C_INT32 n, k, i, tot, seed;
  CCopasiVector < CGene > GeneList;
  string prefix;
  CModel model;
  C_FLOAT64 positive;
  char NetTitle[512], comments[2048];

  // parse command line
  try
    {
      clo::parser cmdl;
      cmdl.parse(argc, argv);
      // get options from command line parser
      const clo::options &options = cmdl.get_options();
      seed = options.seed;
      tot = options.total;
;
      n = options.genes;
      k = options.inputs;
      prefix = options.prefix;
      positive = options.positive;
    }
  catch (clo::autoexcept &e)
    {
      switch (e.get_autothrow_id())
        {
        case clo::autothrow_help:
          std::cout << "Usage: " << argv[0] << " [options]" << endl;
          std::cout << e.what();
          return 0;
        }
    }
  catch (std::exception &e)
    {
      std::cout << argv[0] << ": " << e.what() << endl;
      return 1;
    }

  Copasi = new CGlobals;

  if (seed)
    r250_init(seed);
  else
    r250_init(((int) time(NULL)) | 12783579);

  // create appropriate kinetic types, including
  // all combinations of activators and inhibitors
  for (i = 0; i <= k; i++)
    MakeKinType(Copasi->FunctionDB, k, i);
  // generate tot networks of n genes with k random outputs each
  for (i = 0; i < tot; i++)
    {
      // build the gene network
      MakeGeneNetwork(n, k, positive, GeneList, comments);
      sprintf(NetTitle, "%s%03ld", prefix.data(), i + 1);
      // create graph files
      WriteDot(NetTitle, GeneList);
      WritePajek(NetTitle, GeneList);
      // create distribution graph file
      WriteDistri(NetTitle, GeneList);
      // create COPASI model
      MakeModel(NetTitle, comments, GeneList, n, k, model);
      // save Gepasi model
      WriteGepasi(NetTitle, model);
      // cleanup model and vectors
      model.cleanup();
      GeneList.cleanup();
    }

  return 0;
}
