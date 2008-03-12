// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/testxppaut/tablediff.cpp,v $
//   $Revision: 1.2 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2008/03/12 02:18:23 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <iterator>
#include <math.h>

class Table : private std::vector< std::vector<double> >
  {
  public:

    bool readFromFile(const std::string & s, char sep);
    bool readFromStream(std::istream & is, char sep);

    void print() const;

    int getNumColumns() const {return size();};
    std::vector<double> & getColumn(int n) {return (*this)[n];};

    int getNumRows() const
      {
        if (getNumColumns())
          return (*this)[0].size();
        else
          return 0;
      };

  private:

    static std::vector<double> readLineOfNumbers(std::istream & is, char sep);
  };

//static
std::vector<double> Table::readLineOfNumbers(std::istream & is, char sep)
{
  std::string tmpstring;
  std::getline(is, tmpstring);
  //std::cout << tmpstring << std::endl;

  std::istringstream iss(tmpstring);
  std::vector<double> ret;

  std::string field;
  while (std::getline(iss, field, sep))
    {
      std::istringstream fss(field);
      double ttt; fss >> ttt;
      if (!fss) break;
      ret.push_back(ttt);
    }

  /*  std::copy(std::istream_iterator<double>(iss),
                    std::istream_iterator<double>(),
                    std::back_inserter(ret));*/

  return ret;
}

bool Table::readFromFile(const std::string & s, char sep)
{
  std::ifstream is(s.c_str());
  if (!is)
    {
      return false;
    }
  return readFromStream(is, sep);
}

bool Table::readFromStream(std::istream & is, char sep)
{
  std::vector<double> tmpv;

  while (is.good() && tmpv.size() == 0)
    {
      tmpv = readLineOfNumbers(is, sep);
    }

  if (tmpv.size() == 0) return false;

  resize(0); //clear
  resize(tmpv.size());

  while (is.good() && tmpv.size() == size())
    {
      int i;
      for (i = 0; i < size(); ++i)
        (*this)[i].push_back(tmpv[i]);

      tmpv = readLineOfNumbers(is, sep);
    }

  if (tmpv.size() != 0) return false;
  return true;
}

void Table::print() const
  {
    int i, j;
    for (i = 0; i < getNumRows(); ++i)
      {
        for (j = 0; j < getNumColumns(); ++j)
          std::cout << (*this)[j][i] << " ";
        std::cout << "\n";
      }
  }

//****************************************************

/**
 * checks if c2 can be interpreted as c1 scaled with a factor
 * c2 = c1 * f
 * m is the potential scaling factor, sd is the relative error when using m as scaling factor
 */
bool compareColumns(const std::vector<double> & c1, const std::vector<double> & c2,
                    double & mean, double & sd)
{
  if (c1.size() != c2.size()) return false;

  std::vector<double>::const_iterator c1it, c1itEnd = c1.end();
  std::vector<double>::const_iterator c2it;

  //check for only small numbers
  bool allzero = true;
  for (c1it = c1.begin(), c2it = c2.begin(); c1it != c1itEnd; ++c1it, ++c2it)
    {
      if (fabs(*c1it) > 1e-20 || fabs(*c2it) > 1e-20)
      {allzero = false; break;}
    }
  if (allzero)
  {mean = 0; sd = 0; return true;}

  //calculate mean of c2/c1
  int n = 0;
  double m = 0;
  double w = 0;
  for (c1it = c1.begin(), c2it = c2.begin(); c1it != c1itEnd; ++c1it, ++c2it)
    {
      ++n;
      m += *c2it;
      w += *c1it;
    }
  if (n == 0) return false;
  mean = m / w;

  // now the standard deviation
  m = 0;
  for (c1it = c1.begin(), c2it = c2.begin(); c1it != c1itEnd; ++c1it, ++c2it)
    {
      //m += (*c2it/mean - *c1it)*(*c2it/mean - *c1it);
      m += fabs(*c2it / mean - *c1it);
      //std::cout << *c2it << " " << *c1it << " " << (*c2it/mean - *c1it) << std::endl;
    }
  sd = /*sqrt*/(m / n) / fabs(w / n);

  return true;
}

int main(int argc, char * argv[])
{
  if (argc != 3)
    {
      //std::cout << argc;
      std::cout << "usage: " << argv[0] << " first_file second_file " << std::endl;
      std::cout << "It is checked whether the first file is scaled version of the second," << std::endl;
      std::cout << "possibly with rearranged columns." << std::endl;
      return - 1;
    }

  std::cout << "<h3>" << argv[1] << " -> " << argv[2] << "</h3>\n";

  Table t1;
  if (!t1.readFromFile(argv[1], ' '))
    {
      std::cout << "problem reading first file." << std::endl;
      return - 1;
    }
  //std::cout << t1.getNumColumns() << " " << t1.getNumRows() << std::endl;

  Table t2;
  if (!t2.readFromFile(argv[2], ','))
    {
      std::cout << "problem reading second file." << std::endl;
      return - 1;
    }
  //std::cout << t2.getNumColumns() << " " << t2.getNumRows() << std::endl;
  //t2.print();

  if (t1.getNumRows() != t2.getNumRows())
    {
      std::cout << "<font color=\"#A00000\">";
      std::cout << "mismatch in number of rows ("
      << t1.getNumRows() << " != "
      << t2.getNumRows() << ")" << std::endl;
      std::cout << "</font>";

      return - 1;
    }

  double m, sd;

  int i, j;

  for (i = 0; i < t1.getNumColumns(); ++i)
    {
      double smallestError = 1e100;
      int matchingColumn = -999;
      double bestFactor = -999;
      for (j = 0; j < t2.getNumColumns(); ++j)
        {
          bool flag = compareColumns(t2.getColumn(j), t1.getColumn(i), m, sd);
          //std::cout << m << " " << sd << "  :  ";

          if (!flag) continue;
          if (sd < smallestError)
          {smallestError = sd; matchingColumn = j; bestFactor = m;}
        }
      // std::cout << std::endl;
      std::string color;
      if (smallestError < 1e-5) color = "\"#00A000\"";
      else if (smallestError < 1e-3) color = "\"#60A000\"";
      else if (smallestError < 0.01) color = "\"#A0A000\"";
      else if (smallestError < 0.05) color = "\"#A07000\"";
      else color = "\"#A00000\"";
      std::cout << "<font color=" << color << ">";
      std::cout << "Best match:  " << i << " -> " << matchingColumn
      << " \t      Factor: " << bestFactor << ", Error: " << smallestError
      << "<br>"
      << std::endl;
      std::cout << "</font>";
    }

  // t.print();
}
