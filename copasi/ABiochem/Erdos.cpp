/**
 *  Erdos
 *
 *  Program to generate random gene networks following an 
 *  Erdos topology
 *  
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
#include "tnt/tnt.h"
#include "tnt/luX.h"
#include "tnt/cmat.h"
#include "tnt/vec.h"
#include "tnt/subscript.h"

#include "ABiochem/CGene.h"

extern "C" void r250_init(int seed);
extern "C" unsigned int r250n(unsigned n);
extern "C" double dr250();

using namespace std;

void Erdos(C_INT32 n, C_INT32 k, CCopasiVector < CGene > &gene)
{
  C_INT32 i, j, l, m;
  char gn[1024];

  // create and name genes
  gene.resize(n);
  for (i = 0; i < n; i++)
    {
      sprintf(gn, "G%d", i + 1);
      gene[i]->setName(gn);
    }
  for (i = 0; i < n; i++)
    for (j = 0; j < k; j++)
      {
        for (l = -1; l < 0; )
          {
            l = r250n(n);
            for (m = 0; m < gene[i]->getModifierNumber(); m++)
              if (gene[l] == gene[i]->getModifier(m))
                {
                  l = -1;
                  break;
                }
          }
        gene[i]->addModifier(gene[l], r250n(2), dr250()*10.0 + 1e-5);
      }
}

void WriteDot(ofstream &fout, char *Title, CCopasiVector < CGene > &gene)
{
  unsigned C_INT32 i;
  C_INT32 j;

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
}

void MakeModel(char *Title, CCopasiVector < CGene > &gene, C_INT32 n, C_INT32 k, CModel &model)
{
  C_INT32 i, r;
  char comments[2048], strname[512], streq[512];
  string compname = "cell", rname, rchemeq, kiname;
  CReaction *react;
  // two reactions per gene
  r = 2 * n;
  // set the title and comments
  model.setTitle(Title);
  sprintf(comments, "Model of a random gene network following a Erdos-Renyi topology\nwith %d genes and %d input connections each.\n\nCreated automatically by the A-Biochem system", n, k);
  model.setComments(comments);
  // add one compartment to the model
  model.addCompartment(compname, 1.0);
  // create one metabolite for each gene
  for (i = 0; i < n; i++)
    model.addMetabolite(compname, (const string) gene[i]->getName(), 1.0, 1);
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
      sprintf(strname, "basal %d inh %d act (indp)", gene[i]->getNegativeModifiers(),
               gene[i]->getPositiveModifiers());
      kiname = strname;
      react->setFunction(kiname);
      //     react->setReactantsFromChemEq();
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
      //     react->setReactantsFromChemEq();
      model.addReaction(react);
    }
}

void MakeKinType(CFunctionDB &db, C_INT32 k, C_INT32 p)
{
  C_INT32 i, j;
  CKinFunction *funct;
  char tmpstr[2048];
  string kiname, pname;
  string equation;

  // make name
  sprintf(tmpstr, "basal %d inh %d act (indp)", k - p, p);
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
            sprintf(tmpstr, "(1+Ka%d/A%d)^na%d", j, j, j);
          else
            sprintf(tmpstr, "*(1+Ka%d/A%d)^na%d", j, j, j);
          equation += tmpstr;
        }
      for (j = 1; i < k; i++, j++)
        {
          if (i == 0)
            sprintf(tmpstr, "(1+I%d/Ki%d)^ni%d", j, j, j);
          else
            sprintf(tmpstr, "*(1+I%d/Ki%d)^ni%d", j, j, j);
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
          sprintf(tmpstr, "Ka%d", j);
          pname = tmpstr;
          funct->addParameter(pname, CFunctionParameter::FLOAT64, "PARAMETER");
          sprintf(tmpstr, "na%d", j);
          pname = tmpstr;
          funct->addParameter(pname, CFunctionParameter::FLOAT64, "PARAMETER");
          sprintf(tmpstr, "A%d", j);
          pname = tmpstr;
          funct->addParameter(pname, CFunctionParameter::FLOAT64, "MODIFIER");
        }
      for (j = 1; i < k; i++, j++)
        {
          sprintf(tmpstr, "Ki%d", j);
          pname = tmpstr;
          funct->addParameter(pname, CFunctionParameter::FLOAT64, "PARAMETER");
          sprintf(tmpstr, "ni%d", j);
          pname = tmpstr;
          funct->addParameter(pname, CFunctionParameter::FLOAT64, "PARAMETER");
          sprintf(tmpstr, "I%d", j);
          pname = tmpstr;
          funct->addParameter(pname, CFunctionParameter::FLOAT64, "MODIFIER");
        }
      //  funct->addParametersUsage("PRODUCT",1,CRange::NoRange);
      funct->compile();
      db.add(funct);
    }
}

C_INT main(C_INT argc, char *argv[])
{
  C_INT32 n, k, i, tot;
  CCopasiVector < CGene > GeneList;
  char NetTitle[512];
  char strtmp[1024];
  CModel model;

  Copasi = new CGlobals;
  Copasi->setArguments(argc, argv);

  r250_init(((int) time(NULL)) | 12783579);

  tot = 10;
  n = 10;
  k = 2;
  // create appropriate kinetic types, including
  // all combinations of activators and inhibitors
  for (i = 0; i < k; i++)
    MakeKinType(Copasi->FunctionDB, k, i + 1);
  // generate tot networks of n genes with k random outputs each
  for (i = 0; i < tot; i++)
    {
      // build the gene network
      Erdos(n, k, GeneList);
      // create GraphViz file
      sprintf(NetTitle, "Net%03d", i + 1);
      sprintf(strtmp, "%s.dot", NetTitle);
      ofstream fo(strtmp);
      WriteDot(fo, NetTitle, GeneList);
      fo.close();
      // create COPASI model
      MakeModel(NetTitle, GeneList, n, k, model);
      // cleanup model and vectors
      model.cleanup();
      GeneList.cleanup();
    }

  return 0;
}
