// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/miase/CMiaseParser.cpp,v $
//   $Revision: 1.9 $
//   $Name:  $
//   $Author: aruff $
//   $Date: 2008/03/21 20:06:54 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#include "CMiaseParser.h"
#include "CMiaseBase.h"
#include "CMiaseSimulation.h"
#include "CMiaseTask.h"
#include "CMiaseModel.h"
#include "CMiaseOutput.h"
#include <vector>

//#include "/Users/anton/copasi/copasi_dev/copasi/utilities/utility.cpp"

XML_Char CMiaseParser::mVersion_1_0[] = {'1', '.', '0', 0};
XML_Char CMiaseParser::mNameSpace[] = "http://www.miase.org/";
XML_Char CMiaseParser::mEncoding[] = {'u', 't', 'f', '-', 8};

CMiaseParser::CMiaseParser()
{
  myParser = this;
  this->mXmlParser = XML_ParserCreate(NULL);
  this->mActState = STATE_READY_TO_READ;
  this->mLastState = STATE_READY_TO_READ;
  this->mMiase = NULL;
  this->mContent = "";
  this->createAllowedStateTags();
  this->mTmpDepth = 0;

  XML_SetXmlDeclHandler(myParser->mXmlParser, myParser->xmldecl_handler);
  XML_SetElementHandler(myParser->mXmlParser, myParser->start, myParser->end);
  XML_SetCharacterDataHandler(myParser->mXmlParser, myParser->charhndl);
}

CMiaseParser::~CMiaseParser()
{
  XML_ParserFree(myParser->mXmlParser);
  delete *myParser;
}

void CMiaseParser::createAllowedStateTags()
{
  std::vector<std::string> tmpAllowedTags;
  int i;
  for (i = 0; i <= (int)STATE_STOPPED; i++)
  {this->mAllowedStateTags.push_back(tmpAllowedTags);}

  tmpAllowedTags.push_back("Notes");
  tmpAllowedTags.push_back("Annotation");

  for (i = (int)STATE_MIASE; i < (int)LAST; i++)
  {this->mAllowedStateTags.push_back(tmpAllowedTags);}

  this->mAllowedStateTags[STATE_READY_TO_READ].push_back("MiaseML");

  this->mAllowedStateTags[STATE_MIASE].push_back("Sed");

  this->mAllowedStateTags[STATE_SED].push_back("listOfSimulations");
  this->mAllowedStateTags[STATE_SED].push_back("listOfModels");
  this->mAllowedStateTags[STATE_SED].push_back("listOfTasks");
  this->mAllowedStateTags[STATE_SED].push_back("listOfOutputs");

  this->mAllowedStateTags[STATE_LIST_OF_SIMULATIONS].push_back("UniformTimeCourse");
  this->mAllowedStateTags[STATE_LIST_OF_SIMULATIONS].push_back("SteadyStateAnalysis");
  this->mAllowedStateTags[STATE_LIST_OF_SIMULATIONS].push_back("AnySimulationType");

  this->mAllowedStateTags[STATE_LIST_OF_MODELS].push_back("Model");

  this->mAllowedStateTags[STATE_MODEL].push_back("listOfChanges");

  this->mAllowedStateTags[STATE_LIST_OF_CHANGES].push_back("ChangeAttribute");
  this->mAllowedStateTags[STATE_LIST_OF_CHANGES].push_back("ChangeMath");

  this->mAllowedStateTags[STATE_LIST_OF_TASKS].push_back("Task");

  this->mAllowedStateTags[STATE_TASK].push_back("listOfMeasurement");

  this->mAllowedStateTags[STATE_LIST_OF_MEASUREMENT].push_back("MeasurementData");

  this->mAllowedStateTags[STATE_LIST_OF_OUTPUTS].push_back("Output");

  tmpAllowedTags.clear();
  this->mAllowedStateTags.push_back(tmpAllowedTags);
  /*Only for testing
  int k, l, size;
  for (k=0;k<=(int)LAST;k++)
  {
    size = myParser->mAllowedStateTags[k].size();
    for (l=0;l<size;l++)
    {
      printf("%s\n", this->mAllowedStateTags[k][l].c_str());
    }
    printf("\n");
  } */
}

void XMLCALL
CMiaseParser::charhndl(void *userData, const XML_Char *s, int len)
{myParser->newContent(s, len);}

void XMLCALL
CMiaseParser::start(void *data, const char *el, const char **attr)
{myParser->startElement(data, el, attr);}

void XMLCALL
CMiaseParser::end(void *data, const char *el)
{myParser->endElement(data, el);}

void XMLCALL
CMiaseParser::xmldecl_handler(void *userData, const XML_Char *version,
                              const XML_Char *encoding, int standalone)
{myParser->xmlDecl(userData, version, encoding, standalone);}

void CMiaseParser::newContent(const XML_Char *s, int len)
{myParser->mContent += s /*c_str()*/;}

void CMiaseParser::newNotes(const char **attr)
{
  myParser->mContent = "";
  CMiaseBase * tmpMiaseObj;

  CMiaseNotes newNotes = new CMiaseNotes();
  for (i = 0; attr[i]; i += 2)
    {
      if (strcmp(attr[i], "xmlns") == 0)
      {newNotes->setXmlNs(attr[i + 1]);}
    }

  switch (myParser->mLastState)
    {
    case STATE_MIASE:
      myParser->mMiase->addNotes(newNotes);
      break;
    case STATE_SED:
      myParser->mMiase->getSed()->addNotes(newNotes);
      break;
    case STATE_LIST_OF_SIMULATIONS:
      {
        tmpMiaseObj = myParser->mMiase->getSed()->getLastSimulation();
        if (tmpMiaseObj != null)
        {tmpMiaseObj->addNotes(new CMiaseNotes());}
        else
        {myParser->error("invalid Notes before Change");}
        break;
      case STATE_MODEL:
        tmpMiaseObj = myParser->mMiase->getSed()->getLastModel()->addNotes(newNotes);
        break;
      case STATE_LIST_OF_CHANGES:
        tmpMiaseObj = myParser->mMiase->getSed()->getLastModel()->getLastChange();
        if (tmpMiaseObj != null)
        {tmpMiaseObj->addNotes(newNotes);}
        else
        {myParser->error("invalid Notes before Change");}
        break;
      case STATE_TASK:
        tmpMiaseObj = myParser->mMiase->getSed()->getLastTask()->addNotes(newNotes);
        break;
      case STATE_LIST_OF_MEASUREMENT:
        tmpMiaseObj = myParser->mMiase->getSed()->getLastModel()->getLastMeasurement();
        if (tmpMiaseObj != null)
        {tmpMiaseObj->addNotes(newNotes);}
        else
        {myParser->error("invalid Notes before Measurement");}
        break;
      case STATE_OUTPUT:
        tmpMiaseObj = myParser->mMiase->getSed()->getLastOutput()->addNotes(newNotes);
        break;
      }
      myParser->newState(STATE_NOTES);
    }

  void CMiaseParser::newAnnotation(const char **attr)
  {
    myParser->mContent = "";
    CMiaseBase * tmpMiaseObj;

    CMiaseAnnotation newAnnotation = new CMiaseAnnotation();
    for (i = 0; attr[i]; i += 2)
      {
        if (strcmp(attr[i], "xmlns") == 0)
        {newAnnotation->setXmlNs(attr[i + 1]);}
      }

    switch (myParser->mLastState)
      {
      case STATE_MIASE:
        myParser->mMiase->addAnnotation(newAnnotation);
        break;
      case STATE_SED:
        myParser->mMiase->getSed()->addAnnotation(newAnnotation);
        break;
      case STATE_LIST_OF_SIMULATIONS:
        tmpMiaseObj = myParser->mMiase->getSed()->getLastSimulation();
        if (tmpMiaseObj != null)
        {tmpMiaseObj->addAnnotation(new CMiaseNotes());}
        else
        {myParser->error("invalid Annotation before Change");}
        break;
      case STATE_MODEL:
        tmpMiaseObj = myParser->mMiase->getSed()->getLastModel()->addAnnotation(newAnnotation);
        break;
      case STATE_LIST_OF_CHANGES:
        tmpMiaseObj = myParser->mMiase->getSed()->getLastModel()->getLastChange();
        if (tmpMiaseObj != null)
        {tmpMiaseObj->addAnnotation(newAnnotation);}
        else
        {myParser->error("invalid Annotation before Change");}
        break;
      case STATE_TASK:
        tmpMiaseObj = myParser->mMiase->getSed()->getLastTask()->addAnnotation(newAnnotation);
        break;
      case STATE_LIST_OF_MEASUREMENT:
        tmpMiaseObj = myParser->mMiase->getSed()->getLastModel()->getLastMeasurement();
        if (tmpMiaseObj != null)
        {tmpMiaseObj->addAnnotation(newAnnotation);}
        else
        {myParser->error("invalid Annotation before Measurement");}
        break;
      case STATE_OUTPUT:
        tmpMiaseObj = myParser->mMiase->getSed()->getLastOutput()->addAnnotation(newAnnotation);
        break;
      }
    myParser->newState(STATE_ANNOTATION);
  }

  void CMiaseParser::newModel(const char **attr)
  {
    int i;
    myParser->newState(STATE_MODEL);

    myParser->mMiase->getSed()->addModel(new CMiaseModel());
    for (i = 0; attr[i]; i += 2)
      {
        if (strcmp(attr[i], "id") == 0)
        {myParser->mMiase->getSed()->getLastModel()->setId(attr[i + 1]);}
        else if (strcmp(attr[i], "name") == 0)
        {myParser->mMiase->getSed()->getLastModel()->setName(attr[i + 1]);}
        else if (strcmp(attr[i], "type") == 0)
        {myParser->mMiase->getSed()->getLastModel()->setType(attr[i + 1]);}
        else if (strcmp(attr[i], "source") == 0)
        {myParser->mMiase->getSed()->getLastModel()->setSource(attr[i + 1]);}
      }
  }

  void CMiaseParser::newSimulation(const char *el, const char **attr)
  {
    int i;
    if (strcmp(el, "UniformTimeCourse") == 0)
      {
        myParser->mMiase->getSed()->addSimulation(new CMiaseUniformTimeCourse());
        for (i = 0; attr[i]; i += 2)
          {
            if (strcmp(attr[i], "initialTime") == 0)
              {
                ((CMiaseUniformTimeCourse*)myParser->mMiase->getSed()
                 ->getLastSimulation())->setInitialTime(strtod(attr[i + 1], 0));
              }
            else if (strcmp(attr[i], "outputStartTime") == 0)
              {
                ((CMiaseUniformTimeCourse*)myParser->mMiase->getSed()
                 ->getLastSimulation())->setOutputStartTime(strtod(attr[i + 1], 0));
              }
            else if (strcmp(attr[i], "outputEndTime") == 0)
              {
                ((CMiaseUniformTimeCourse*)myParser->mMiase->getSed()
                 ->getLastSimulation())->setOutputEndTime(strtod(attr[i + 1], 0));
              }
            else if (strcmp(attr[i], "numberOfPoints") == 0)
              {
                ((CMiaseUniformTimeCourse*)myParser->mMiase->getSed()
                 ->getLastSimulation())->setNumberOfPoints(strtod(attr[i + 1], 0));
              }
          }
      }
    else if (strcmp(el, "SteadyStateAnalysis") == 0)
      {
        //TODO
      }
    else if (strcmp(el, "AnySimulationType") == 0)
      {
        //TODO
      }
  }

  void CMiaseParser::newChange(const char *el, const char **attr)
  {
    int i;
    if (strcmp(el, "ChangeAttribute") == 0)
      {
        myParser->mMiase->getSed()->getLastModel()
        ->addChange(new CMiaseChangeAttribute());
        for (i = 0; attr[i]; i += 2)
          {
            if (strcmp(attr[i], "newValue") == 0)
              {
                ((CMiaseChangeAttribute*)myParser->mMiase->getSed()->getLastModel()
                 ->getLastChange())->setNewValue(attr[i + 1]);
              }
            else if (strcmp(attr[i], "target") == 0)
              {
                ((CMiaseChangeAttribute*)myParser->mMiase->getSed()->getLastModel()
                 ->getLastChange())->setTarget(attr[i + 1]);
              }
          }
      }
    else if (strcmp(el, "ChangeMath") == 0)
      {
        myParser->mMiase->getSed()->getLastModel()
        ->addChange(new CMiaseChangeMath());
        for (i = 0; attr[i]; i += 2)
          {
            if (strcmp(attr[i], "newMath") == 0)
              {
                ((CMiaseChangeMath*)myParser->mMiase->getSed()->getLastModel()
                 ->getLastChange())->setNewMath(attr[i + 1]);
              }
            else if (strcmp(attr[i], "target") == 0)
              {
                ((CMiaseChangeMath*)myParser->mMiase->getSed()->getLastModel()
                 ->getLastChange())->setTarget(attr[i + 1]);
              }
          }
      }
  }

  void CMiaseParser::newTask(const char **attr)
  {
    int i;
    myParser->newState(STATE_TASK);

    myParser->mMiase->getSed()->addTask(new CMiaseTask());
    for (i = 0; attr[i]; i += 2)
      {
        if (strcmp(attr[i], "id") == 0)
          {
            myParser->mMiase->getSed()->getLastTask()->setId(attr[i + 1]);
          }
        else if (strcmp(attr[i], "name") == 0)
          {
            myParser->mMiase->getSed()->getLastTask()->setName(attr[i + 1]);
          }
        else if (strcmp(attr[i], "modelReference") == 0)
          {
            myParser->mMiase->getSed()->getLastTask()->setModelReference(
              myParser->mMiase->getSed()->getModel(attr[i + 1]));
          }
        else if (strcmp(attr[i], "simulationReference") == 0)
          {
            myParser->mMiase->getSed()->getLastTask()->setSimulationReference(
              myParser->mMiase->getSed()->getSimulation(attr[i + 1]));
          }
      }
  }

  void CMiaseParser::newMeasurementData(const char **attr)
  {
    int i;
    myParser->mMiase->getSed()->getLastTask()
    ->addMeasurement(new CMiaseMeasurementData());
    for (i = 0; attr[i]; i += 2)
      {
        if (strcmp(attr[i], "name") == 0)
          {
            myParser->mMiase->getSed()->getLastTask()
            ->getLastMeasurement()->setName(attr[i + 1]);
          }
        else if (strcmp(attr[i], "source") == 0)
          {
            myParser->mMiase->getSed()->getLastTask()
            ->getLastMeasurement()->setSource(attr[i + 1]);
          }
      }
  }

  void CMiaseParser::newOutput(const char **attr)
  {
    myParser->mContent = "";
    int i;
    myParser->newState(STATE_OUTPUT);

    myParser->mMiase->getSed()->addOutput(new CMiaseOutput());
    for (i = 0; attr[i]; i += 2)
      {
        if (strcmp(attr[i], "id") == 0)
        {myParser->mMiase->getSed()->getLastOutput()->setId(attr[i + 1]);}
        else if (strcmp(attr[i], "name") == 0)
        {myParser->mMiase->getSed()->getLastOutput()->setName(attr[i + 1]);}
      }
  }

  void CMiaseParser::newMiase(const char **attr)
  {
    int i;
    myParser->newState(STATE_MIASE);

    myParser->mMiase = new CMiaseML();
    for (i = 0; attr[i]; i += 2)
      {
        if (strcmp(attr[i], "xmlns") == 0)
        {myParser->mMiase->setXmlns(attr[i + 1]);}
        else if (strcmp(attr[i], "version") == 0)
        {myParser->mMiase->setVersion(attr[i + 1]);}
      }
  }

  void CMiaseParser::startElement(void *data, const char *el, const char **attr)
  {
    std::string tmpTag = el;

    if (myParser->isValid(el))
      {
        if ((strcmp(el, "Notes") == 0) && (myParser->mActState != STATE_NOTES))
        {myParser->newNotes(attr);}
        else if ((strcmp(el, "Annotation") == 0)
                 && (myParser->mActState != STATE_ANNOTATION))
        {myParser->newAnnotation(attr);}
        else
          {
            switch (myParser->mActState)
              {
              case STATE_LIST_OF_MODELS:
                if (strcmp(el, "Model") == 0)
                {myParser->newModel(attr);}
                break;
              case STATE_MODEL:
                if (strcmp(el, "listOfChanges") == 0)
                {myParser->newState(STATE_LIST_OF_CHANGES);}
                break;
              case STATE_LIST_OF_CHANGES:
                if ((strcmp(el, "ChangeAttribute") == 0)
                    || (strcmp(el, "ChangeMath") == 0))
                {myParser->newChange(el, attr);}
                break;
              case STATE_LIST_OF_SIMULATIONS:
                if ((strcmp(el, "UniformTimeCourse") == 0)
                    || (strcmp(el, "SteadyStateAnalysis") == 0)
                    || (strcmp(el, "AnySimulationType") == 0))
                {myParser->newSimulation(el, attr);}
                break;
              case STATE_LIST_OF_TASKS:
                if (strcmp(el, "Task") == 0)
                {myParser->newTask(attr);}
                break;
              case STATE_TASK:
                if (strcmp(el, "listOfMeasurement") == 0)
                {myParser->newState(STATE_LIST_OF_MEASUREMENT);}
                break;
              case STATE_LIST_OF_MEASUREMENT:
                if (strcmp(el, "MeasurementData") == 0)
                {myParser->newMeasurementData(attr);}
                break;
              case STATE_LIST_OF_OUTPUTS:
                if (strcmp(el, "Output") == 0)
                {myParser->newOutput(attr);}
                break;
              case STATE_SED:
                if (strcmp(el, "listOfSimulations") == 0)
                {myParser->newState(STATE_LIST_OF_SIMULATIONS);}
                else if (strcmp(el, "listOfOutputs") == 0)
                {myParser->newState(STATE_LIST_OF_OUTPUTS);}
                else if (strcmp(el, "listOfTasks") == 0)
                {myParser->newState(STATE_LIST_OF_TASKS);}
                else if (strcmp(el, "listOfModels") == 0)
                {myParser->newState(STATE_LIST_OF_MODELS);}
                break;
              case STATE_MIASE:
                if (strcmp(el, "Sed") == 0)
                  {
                    myParser->mMiase->setMiaseSed(new CMiaseSed());
                    myParser->newState(STATE_SED);
                  }
                break;
              case STATE_READY_TO_READ:
                if (strcmp(el, "MiaseML") == 0)
                {myParser->newMiase(attr);}
                break;
              case STATE_NOTES:
                myParser->mTmpDepth = 0;
                myParser->addContent(el, attr);
                break;
              case STATE_ANNOTATION:
                myParser->mTmpDepth = 0;
                myParser->addContent(el, attr);
                break;
              case STATE_OUTPUT:
                myParser->mTmpDepth = 0;
                myParser->addContent(el, attr);
                break;
              }

            int i;
            for (i = 0; i < myParser->mDepth; i++)
              printf("  ");

            printf("%s", el);
            for (i = 0; attr[i]; i += 2)
              printf(" %s='%s'", attr[i], attr[i + 1]);

            printf("\n");
          }
      }
    myParser->mDepth++;
    myParser->mTmpDepth++;
  }

  void CMiaseParser::addContent(const char *el, const char **attr)
  {
    //myParser->mContent += "\n";
    int i;
    for (i = 0; i < myParser->mTmpDepth; i++)
      myParser->mContent += "  ";
    myParser->mContent += "<";
    myParser->mContent += el /*c_str()*/;
    for (i = 0; attr[i]; i += 2)
      myParser->mContent += (" " + attr[i] + " " + attr[i + 1]);
    myParser->mContent += ">\n";
  }

  void CMiaseParser::endElement(void *data, const char *el)
  {
    CMiaseBase tmpObj;
    if (((myParser->mActState == STATE_NOTES) && (strcmp(el, "Notes") != 0))
        || ((myParser->mActState == STATE_ANNOTATION) && (strcmp(el, "Annotation") != 0))
        || ((myParser->mActState == STATE_OUTPUT) && (strcmp(el, "Output") != 0)))
      {
        for (i = 0; i < myParser->mTmpDepth; i++)
          myParser->mContent += "  ";
        myParser->mContent += ("</" + el + ">\n");
      }
    else if ((strcmp(el, "listOfSimulations") == 0)
             || (strcmp(el, "listOfModels") == 0)
             || (strcmp(el, "listOfOutputs") == 0)
             || (strcmp(el, "listOfTasks") == 0))
      || (strcmp(el, "Model") == 0)
      || (strcmp(el, "listOfChanges") == 0)
      || (strcmp(el, "Task") == 0)
      || (strcmp(el, "listOfMeasurement") == 0))
    {myParser->newState(myParser->mLastState);}
    else if (strcmp(el, "Output") == 0)
      {
        myParser->newState(myParser->mLastState);
        //TODO: addContent to Output
      }
    if (strcmp(el, "Notes") == 0)
      {
        tmpObj = myParser->getLastObj(el);
        tmpObj->getNotes->setNotes(myParser->mContent);
        myParser->newState(myParser->mLastState);
        myParser->mContent = "";
      }
    else if (strcmp(el, "Annotation") == 0)
      {
        tmpObj = myParser->getLastObj(el);
        tmpObj->getAnnotation->setAnyNote(myParser->mContent);
        myParser->newState(myParser->mLastState);
        myParser->mContent = "";
      }
    else if ((strcmp(el, "Sed") == 0) || (strcmp(el, "Miase") == 0))
    {myParser->newState(STATE_LAST);}
    myParser->mDepth--;
    myParser->mTmpDepth--;
  }

  void CMiaseParser::getLastObj(const char *el)
  {
    switch (myParser->mActState)
      {
      case STATE_OUTPUT:
        return myParser->mMiase->getSed()->getLastOutput();
        break;
      case STATE_LIST_OF_MEASUREMENT:
        return myParser->mMiase->getSed()->getLastTask()->getLastMeasurement();
        break;
      case STATE_LIST_OF_TASKS:
        return myParser->mMiase->getSed()->getLastTask();
        break;
      case STATE_LIST_OF_CHANGES:
        return myParser->mMiase->getSed()->getLastModel()->getLastChange();
        break;
      case STATE_MODEL:
        return myParser->mMiase->getSed()->getLastModel();
        break;
      case STATE_LIST_OF_SIMULATION:
        return myParser->mMiase->getSed()->getLastSimulation();
        break;
      case STATE_SED:
        return myParser->mMiase->getSed();
        break;
      case STATE_MIASE:
        return myParser->mMiase;
        break;
      }
  }

  void CMiaseParser::newState(States newState)
  {
    //myParser->mContent = "";
    myParser->mLastState = myParser->mActState;
    myParser->mActState = newState;
  }

  void CMiaseParser::xmlDecl(void *userData, const XML_Char *version,
                             const XML_Char *encoding, int standalone)
  {

    int i;
    for (i = 0; i < (sizeof(myParser->mVersion_1_0) /
                     sizeof(myParser->mVersion_1_0[0])); ++i)
      {
        if (version[i] != myParser->mVersion_1_0[i])
          {
            XML_StopParser(myParser->mXmlParser, false);
            fprintf(stderr, "Read error\n");
          }
      }

    for (i = 0; i < std::min(sizeof(myParser->mEncoding), sizeof(encoding)); i++)
      {
        if (encoding[i] != myParser->mEncoding[i])
          {
            XML_StopParser(myParser->mXmlParser, false);
            fprintf(stderr, "Read error\n");
          }
      }
  }

  void CMiaseParser::load(std::string filename)
  {
    FILE * file = fopen(filename.c_str(), "r");

    if (! myParser->mXmlParser)
      {
        fprintf(stderr, "Couldn't allocate memory for parser\n");
        exit(-1);
      }

    for (;;)
      {

        int done;
        int len;

        len = (int)fread(myParser->mBuff, 1, BUFFSIZE, file);
        if (ferror(file))
          {
            fprintf(stderr, "Read error\n");
            exit(-1);
          }
        done = feof(file);

        if (XML_Parse(myParser->mXmlParser, myParser->mBuff, len, done)
            == XML_STATUS_ERROR)
          {
            fprintf(stderr, "Parse error at line %" XML_FMT_INT_MOD "u:\n%s\n",
                    XML_GetCurrentLineNumber(myParser->mXmlParser),
                    XML_ErrorString(XML_GetErrorCode(myParser->mXmlParser)));
            exit(-1);
          }

        if (done)
          break;
      }
    XML_ParserFree(myParser->mXmlParser);
  }

  void CMiaseParser::error(std::string errorString)
  {
    myParser->newState(STATE_STOPPED);
    printf("%s", errorString);
    XML_StopParser(myParser->mXmlParser, false);
  }

  bool CMiaseParser::isValid(const char *el)
  {
    int i;
    if (myParser->mActState == STATE_ANNOTATION)
      || (myParser->mActState == STATE_NOTES)
      || (myParser->mActState == STATE_OUTPUT))
    {return true;}
    else if (myParser->mActState == STATE_STOPPED)
  {return false;}

  std::vector<std::string> tmpAllowedStateTags =
    myParser->mAllowedStateTags[myParser->mActState];

  for (i = 0; i < tmpAllowedStateTags.size(); i++)
    {
      if (strcmp(el, tmpAllowedStateTags[i].c_str()) == 0)
      {return true;}
    }
    myParser->error("PARSE ERROR");
    return false;
  }
