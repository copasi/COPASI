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

C_INT32 Erdos(C_INT32 n, C_INT32 k, CCopasiVector < CGene > &gene)
{
  C_INT i, j, l;
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
        l = r250n(n);
        gene[i]->addModifier(gene[l], r250n(2), dr250()*10.0 + 1e-5);
      }
  return 0;
}

void WriteDot(ofstream &fout, string &Title, CCopasiVector < CGene > &gene)
{
  unsigned C_INT32 i;
  C_INT32 j;

  // dot file header
  fout << "digraph \"" << Title << "\" {\n";
  fout << "\tgraph\n\t[\n";
  fout << "\t\tpage=\"8,11\"\n";
  fout << "\t\tcenter=\"true\"\n";
  fout << "\t\toverlap=\"false\"\n";
  fout << "\t\tDamping=0.999\n";
  fout << "\t\tfontsize=14\n";
  fout << "\t\tfontname=\"Helvetica\"\n";
  fout << "\t\tmaxiter=1000000\n";
  // fprintf(fo, "\t\tsplines=\"true\"\n");
  // if(rndstart)
  fout << "\t\tstart=\"random\"\n";
  // else
  //  fprintf(fo, "\t\tstart=\"regular\"\n");
  fout << "\t\tepsilon=0.0000001\n";
  fout << "\t\tsep=0.5\n";
  // fprintf(fo, "\t\tlabel=\"%s\"", title.c_str());
  fout << "\t]\n\n";
  fout << "\tnode\n\t[\n";
  fout << "\t\tfontsize=10\n";
  fout << "\t\tfontname=\"Times-Roman\"\n";
  fout << "\t\tshape=\"circle\"\n";
  fout << "\t\tlabel=\"\"\n";
  fout << "\t]\n\n";
  fout << "\tedge\n\t[\n";
  fout << "\t\tfontsize=11\n";
  fout << "\t\tfontname=\"Times-Roman\"\n";
  fout << "\t]\n\n";

  for (i = 0; i < gene.size(); i++)
    for (j = 0; j < gene[i]->getModifierNumber(); j++)
      {
        fout << "\t" << gene[i]->getModifier(j)->getName() << " -> " << gene[i]->getName() << endl;
      }

  // end the file
  fout << "\n}";
}

C_INT main(C_INT argc, char *argv[])
{
  C_INT32 n, k;
  CCopasiVector < CGene > GeneList;
  string NetworkTitle = "FirstNet";
  char strtmp[1024];

  cout << "Starting main program." << endl;
  Copasi = new CGlobals;
  Copasi->setArguments(argc, argv);

  r250_init((int) time(NULL));

  // generate a network of n genes with k random outputs each
  n = 20;
  k = 2;
  Erdos(n, k, GeneList);
  sprintf(strtmp, "%s.dot", NetworkTitle.data());
  ofstream fo(strtmp);
  WriteDot(fo, NetworkTitle, GeneList);
  fo.close();

  GeneList.cleanup();

  return 0;
}
