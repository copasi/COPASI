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
      sprintf(gn, "G%ld", i + 1);
      gene[i]->setName(gn);
    }
  for (i = 0; i < n; i++)
    {
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
          gene[i]->addModifier(gene[l], r250n(2), dr250()*100.0 + 1e-5, dr250()*6.0 + 0.1);
        }
      gene[i]->setRate(dr250()*9.99 + 1e-2);
      gene[i]->setDegradationRate(gene[i]->getRate()*(dr250()*5.83 + 0.17));
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
  C_INT32 i, j, r, s, pos, neg;
  char comments[2048], strname[512], strname2[512], streq[512];
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

void WriteGepasi(ofstream &fout, char *Title, CModel &model)
{
  string linein;
  linein.reserve(100);
  // first part of the file come from a template
  ifstream fin("templategps");
  getline(fin, linein);
  do
    {
      fout << linein << endl;
      getline(fin, linein);
    }
  while (linein.find_first_of("----") != 0);
  // output the model
  // model.saveold();
  // last part also comes from the template
  getline(fin, linein);
  do
    {
      fout << linein << endl;
      getline(fin, linein);
    }
  while (!fin.eof());
  fin.close();
}

C_INT main(C_INT argc, char *argv[])
{
  C_INT32 n, k, i, tot;
  CCopasiVector < CGene > GeneList;
  char NetTitle[512];
  char strtmp[1024];
  CModel model;
  ofstream fo;

  Copasi = new CGlobals;
  Copasi->setArguments(argc, argv);

  r250_init(((int) time(NULL)) | 12783579);

  tot = 10;
  n = 10;
  k = 2;
  // create appropriate kinetic types, including
  // all combinations of activators and inhibitors
  for (i = 0; i <= k; i++)
    MakeKinType(Copasi->FunctionDB, k, i);
  // generate tot networks of n genes with k random outputs each
  for (i = 0; i < tot; i++)
    {
      // build the gene network
      Erdos(n, k, GeneList);
      // create GraphViz file
      sprintf(NetTitle, "Net%03ld", i + 1);
      sprintf(strtmp, "%s.dot", NetTitle);
      fo.open(strtmp, ios_base::out);
      WriteDot(fo, NetTitle, GeneList);
      fo.close();
      // create COPASI model
      MakeModel(NetTitle, GeneList, n, k, model);
      // save Gepasi model
      sprintf(strtmp, "%s.gps", NetTitle);
      fo.open(strtmp, ios_base::out);
      WriteGepasi(fo, NetTitle, model);
      fo.close();
      // cleanup model and vectors
      model.cleanup();
      GeneList.cleanup();
    }

  return 0;
}
