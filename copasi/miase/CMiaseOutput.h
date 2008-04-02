// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/miase/CMiaseOutput.h,v $
//   $Revision: 1.5 $
//   $Name:  $
//   $Author: akoenig $
//   $Date: 2008/04/02 12:14:39 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#ifndef CMIASEOUTPUT
#define CMIASEOUTPUT

#include "CMiaseBase.h"
#include <string>

class CMiaseColumn : public CMiaseBase
  {

  public:

    CMiaseColumn();

    ~CMiaseColumn();

    std::string getId();
    std::string getName();

    void setId(std::string id);
    void setName(std::string name);

  private:

    std::string mId;
    std::string mName;
  };

class CMiasePlot2D : public CMiaseBase
  {

  public:

    CMiasePlot2D();

    ~CMiasePlot2D();

    std::string getId();
    std::string getName();
    std::string getXData();
    std::string getVData();

    void setId(std::string id);
    void setName(std::string name);
    void setXData(std::string xData);
    void setVData(std::string vData);

  private:

    std::string mId;
    std::string mName;
    std::string mXData;
    std::string mVData;
  };

class CMiaseOutput : public CMiaseBaseEnhanced
  {

  public:

    CMiaseOutput();

    ~CMiaseOutput();

    void addColumn (CMiaseColumn* column);
    void addPlot2D (CMiasePlot2D* plot);

    CMiaseColumn* getColumn(int num);
    CMiaseColumn* getLastColumn();

    CMiasePlot2D* getPlot2D(int num);
    CMiasePlot2D* getLastPlot2D();

    void saveWholeOutput(std::string output);
    std::string getWholeOutput();

  private:

    std::vector < CMiaseColumn* > mListOfColumns;
    std::vector < CMiasePlot2D* > mListOfPlots;
    std::string mWholeOutput;
  };

#endif //CMIASEOUTPUT
