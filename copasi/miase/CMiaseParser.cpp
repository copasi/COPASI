// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/miase/CMiaseParser.cpp,v $
//   $Revision: 1.14 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2009/10/27 16:52:48 $
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
  this->mDepth = 0;

  XML_SetXmlDeclHandler(myParser->mXmlParser, myParser->xmldecl_handler);
  XML_SetElementHandler(myParser->mXmlParser, myParser->start, myParser->end);
  XML_SetCharacterDataHandler(myParser->mXmlParser, myParser->charhndl);
}

CMiaseParser::~CMiaseParser()
{
  XML_ParserFree(myParser->mXmlParser);
  //  delete *myParser;
}

void CMiaseParser::createAllowedStateTags()
{
  std::vector<std::string> tmpAllowedTags;
  int i;

  for (i = 0; i <= (int)STATE_STOPPED; i++)
    {this->mAllowedStateTags.push_back(tmpAllowedTags);}

  tmpAllowedTags.push_back("Notes");
  tmpAllowedTags.push_back("Annotation");

  for (i = (int)STATE_MIASE; i < (int)STATE_LAST; i++)
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
{myParser->startElement(el, attr);}

void XMLCALL
CMiaseParser::end(void *data, const char *el)
{myParser->endElement(el);}

void XMLCALL
CMiaseParser::xmldecl_handler(void *userData, const XML_Char *version,
                              const XML_Char *encoding, int standalone)
{myParser->xmlDecl(version, encoding);}

void CMiaseParser::newContent(const XML_Char *s, int len)
{
  std::string tmpContent;

  if ((myParser->mActState == STATE_NOTES)
      || (myParser->mActState == STATE_ANNOTATION)
      || (myParser->mActState == STATE_OUTPUT))
    {
      tmpContent = s;
      tmpContent = tmpContent.substr(0, len);
      myParser->mContent += tmpContent;
    }
}

void CMiaseParser::newNotes(const char **attr)
{
  int i;
  myParser->mContent = "";
  myParser->mTmpDepth = 0;
  CMiaseBase * tmpMiaseObj;

  CMiaseNotes *newNotes = new CMiaseNotes();

  for (i = 0; attr[i]; i += 2)
    {
      if (strcmp(attr[i], "xmlns") == 0)
        {newNotes->setXmlNs(attr[i + 1]);}
    }

  switch (myParser->mActState)
    {
      case STATE_MIASE:
        myParser->mMiase->addNotes(newNotes);
        break;
      case STATE_SED:
        myParser->mMiase->getSed()->addNotes(newNotes);
        break;
      case STATE_LIST_OF_SIMULATIONS:
        tmpMiaseObj = myParser->mMiase->getSed()->getLastSimulation();

        if (tmpMiaseObj != NULL)
          {tmpMiaseObj->addNotes(new CMiaseNotes());}
        else
          {myParser->error("invalid Notes before Change");}

        break;
      case STATE_MODEL:
        myParser->mMiase->getSed()->getLastModel()->addNotes(newNotes);
        break;
      case STATE_LIST_OF_CHANGES:
        tmpMiaseObj = myParser->mMiase->getSed()->getLastModel()->getLastChange();

        if (tmpMiaseObj != NULL)
          {tmpMiaseObj->addNotes(newNotes);}
        else
          {myParser->error("invalid Notes before Change");}

        break;
      case STATE_TASK:
        myParser->mMiase->getSed()->getLastTask()->addNotes(newNotes);
        break;
      case STATE_LIST_OF_MEASUREMENT:
        tmpMiaseObj = myParser->mMiase->getSed()->getLastTask()->getLastMeasurement();

        if (tmpMiaseObj != NULL)
          {tmpMiaseObj->addNotes(newNotes);}
        else
          {myParser->error("invalid Notes before Measurement");}

        break;
      case STATE_OUTPUT:
        myParser->mMiase->getSed()->getLastOutput()->addNotes(newNotes);
        break;
      default:
        break;
    }

  myParser->newState(STATE_NOTES);
}

void CMiaseParser::newAnnotation(const char **attr)
{
  int i;
  myParser->mContent = "";
  myParser->mTmpDepth = 0;
  CMiaseBase * tmpMiaseObj;

  CMiaseAnnotation *newAnnotation = new CMiaseAnnotation();

  for (i = 0; attr[i]; i += 2)
    {
      if (strcmp(attr[i], "xmlns") == 0)
        {newAnnotation->setXmlNs(attr[i + 1]);}
    }

  switch (myParser->mActState)
    {
      case STATE_MIASE:
        myParser->mMiase->addAnnotation(newAnnotation);
        break;
      case STATE_SED:
        myParser->mMiase->getSed()->addAnnotation(newAnnotation);
        break;
      case STATE_LIST_OF_SIMULATIONS:
        tmpMiaseObj = myParser->mMiase->getSed()->getLastSimulation();

        if (tmpMiaseObj != NULL)
          {tmpMiaseObj->addAnnotation(newAnnotation);}
        else
          {myParser->error("invalid Annotation before Change");}

        break;
      case STATE_MODEL:
        myParser->mMiase->getSed()->getLastModel()->addAnnotation(newAnnotation);
        break;
      case STATE_LIST_OF_CHANGES:
        tmpMiaseObj = myParser->mMiase->getSed()->getLastModel()->getLastChange();

        if (tmpMiaseObj != NULL)
          {tmpMiaseObj->addAnnotation(newAnnotation);}
        else
          {myParser->error("invalid Annotation before Change");}

        break;
      case STATE_TASK:
        myParser->mMiase->getSed()->getLastTask()->addAnnotation(newAnnotation);
        break;
      case STATE_LIST_OF_MEASUREMENT:
        tmpMiaseObj = myParser->mMiase->getSed()->getLastTask()->getLastMeasurement();

        if (tmpMiaseObj != NULL)
          {tmpMiaseObj->addAnnotation(newAnnotation);}
        else
          {myParser->error("invalid Annotation before Measurement");}

        break;
      case STATE_OUTPUT:
        myParser->mMiase->getSed()->getLastOutput()->addAnnotation(newAnnotation);
        break;
      default:
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
          if (strcmp(attr[i], "id") == 0)
            {
              ((CMiaseUniformTimeCourse*)myParser->mMiase->getSed()
               ->getLastSimulation())->setId(attr[i + 1]);
            }
          else if (strcmp(attr[i], "name") == 0)
            {
              ((CMiaseUniformTimeCourse*)myParser->mMiase->getSed()
               ->getLastSimulation())->setName(attr[i + 1]);
            }
          else if (strcmp(attr[i], "initialTime") == 0)
            {
              ((CMiaseUniformTimeCourse*)myParser->mMiase->getSed()
               ->getLastSimulation())->setInitialTime(strToDouble(attr[i + 1], 0));
            }
          else if (strcmp(attr[i], "outputStartTime") == 0)
            {
              ((CMiaseUniformTimeCourse*)myParser->mMiase->getSed()
               ->getLastSimulation())->setOutputStartTime(strToDouble(attr[i + 1], 0));
            }
          else if (strcmp(attr[i], "outputEndTime") == 0)
            {
              ((CMiaseUniformTimeCourse*)myParser->mMiase->getSed()
               ->getLastSimulation())->setOutputEndTime(strToDouble(attr[i + 1], 0));
            }
          else if (strcmp(attr[i], "numberOfPoints") == 0)
            {
              ((CMiaseUniformTimeCourse*)myParser->mMiase->getSed()
               ->getLastSimulation())->setNumberOfPoints(strToDouble(attr[i + 1], 0));
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
            attr[i + 1]);
        }
      else if (strcmp(attr[i], "simulationReference") == 0)
        {
          myParser->mMiase->getSed()->getLastTask()->setSimulationReference(
            attr[i + 1]);
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
  myParser->mTmpDepth = 0;
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

void CMiaseParser::startElement(const char *el, const char **attr)
{
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
                myParser->addContent(el, attr);
                break;
              case STATE_ANNOTATION:
                myParser->addContent(el, attr);
                break;
              case STATE_OUTPUT:
                myParser->addContent(el, attr);
                break;
              default:
                break;
            }
        }

      /*          int i;
                for (i = 0; i < myParser->mDepth; i++)
                   printf("  ");

                printf("%s", el);
                for (i = 0; attr[i]; i += 2)
                  printf(" %s='%s'", attr[i], attr[i + 1]);

                printf("\n");
      */
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
    {
      myParser->mContent += " "; // + attr[i] + " " + attr[i + 1];
      myParser->mContent += attr[i];
      myParser->mContent += " ";
      myParser->mContent += attr[i + 1];
    }

  myParser->mContent += ">\n";
}

void CMiaseParser::endElement(const char *el)
{
  int i;
  CMiaseBase *tmpObj;

  myParser->mDepth--;
  myParser->mTmpDepth--;

  if ((strcmp(el, "Notes") == 0) && (myParser->mTmpDepth == 0))
    {
      tmpObj = myParser->getLastObj();
      tmpObj->getNotes()->setNotes(myParser->mContent);
      myParser->newState(myParser->mLastState);
    }
  else if (((myParser->mActState == STATE_NOTES)
            || (myParser->mActState == STATE_ANNOTATION)
            || (myParser->mActState == STATE_OUTPUT))
           && (myParser->mTmpDepth != 0))
    {
      for (i = 0; i < myParser->mTmpDepth; i++)
        myParser->mContent += "  ";

      myParser->mContent += "</";
      myParser->mContent += el;
      myParser->mContent += ">\n";
    }
  else if ((strcmp(el, "Annotation") == 0) && (myParser->mTmpDepth == 0))
    {
      tmpObj = myParser->getLastObj();
      tmpObj->getAnnotation()->setAnyNote(myParser->mContent);
      myParser->newState(myParser->mLastState);
    }
  else if (strcmp(el, "Model") == 0)
    {myParser->newState(STATE_LIST_OF_MODELS);}
  else if (strcmp(el, "listOfChanges") == 0)
    {myParser->newState(STATE_MODEL);}
  else if (strcmp(el, "listOfMeasurement") == 0)
    {myParser->newState(STATE_TASK);}
  else if ((strcmp(el, "listOfSimulations") == 0)
           || (strcmp(el, "listOfTasks") == 0)
           || (strcmp(el, "listOfModels") == 0)
           || (strcmp(el, "listOfOutputs") == 0))
    {myParser->newState(STATE_SED);}
  else if (strcmp(el, "Task") == 0)
    {myParser->newState(STATE_LIST_OF_TASKS);}
  else if (strcmp(el, "Output") == 0)
    {
      myParser->newState(STATE_LIST_OF_OUTPUTS);

      //TODO: addContent to Output
      myParser->mMiase->getSed()->getLastOutput()->saveWholeOutput(myParser->mContent);
    }
  else if ((strcmp(el, "Sed") == 0) || (strcmp(el, "Miase") == 0))
    {myParser->newState(STATE_LAST);}
}

CMiaseBase* CMiaseParser::getLastObj()
{
  switch (myParser->mLastState)
    {
      case STATE_OUTPUT:
        return myParser->mMiase->getSed()->getLastOutput();
        break;
      case STATE_LIST_OF_MEASUREMENT:
        return myParser->mMiase->getSed()->getLastTask()->getLastMeasurement();
        break;
      case STATE_TASK:
        return myParser->mMiase->getSed()->getLastTask();
        break;
      case STATE_LIST_OF_CHANGES:
        return myParser->mMiase->getSed()->getLastModel()->getLastChange();
        break;
      case STATE_MODEL:
        return myParser->mMiase->getSed()->getLastModel();
        break;
      case STATE_LIST_OF_SIMULATIONS:
        return myParser->mMiase->getSed()->getLastSimulation();
        break;
      case STATE_SED:
        return myParser->mMiase->getSed();
        break;
      case STATE_MIASE:
        return myParser->mMiase;
        break;
      default:
        break;
    }

  myParser->error("Last Obj is NULL");
  return NULL;
}

void CMiaseParser::newState(States newState)
{
  //myParser->mContent = "";
  myParser->mLastState = myParser->mActState;
  myParser->mActState = newState;
}

void CMiaseParser::xmlDecl(const XML_Char *version,
                           const XML_Char *encoding)
{

  unsigned int i;

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
}

bool CMiaseParser::isValid(const char *el)
{
  unsigned int i;

  if ((myParser->mActState == STATE_ANNOTATION)
      || (myParser->mActState == STATE_NOTES)
      || (myParser->mActState == STATE_OUTPUT))
    {return true;}
  else if (myParser->mActState == STATE_STOPPED)
    {
      myParser->error("PARSE ERROR");
      return false;
    }

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

void CMiaseParser::testDataStructure()
{
  int i;
  int j;
  //testing whether structure was loaded
  std::cout << "-------------------------DataStructure------------------------------- " << std::endl << std::endl << std::endl;

  if (myParser->mMiase)
    {
      std::cout <<
                myParser->mMiase->getSed()->getNotes()->getNotes() << std::endl;

      if (myParser->mMiase->getSed()->getNumOfSimulations() > 0)
        {
          std::cout << "NumOfSimulations: " <<
                    myParser->mMiase->getSed()->getNumOfSimulations() << std::endl << std::endl;

          for (i = 0 ; i < myParser->mMiase->getSed()->getNumOfSimulations() ; i++)
            {
              std::cout << "    Simulation nr. :" << i << std::endl;

              std::cout << "     id: " <<
                        ((CMiaseUniformTimeCourse*)myParser->mMiase->getSed()->getSimulation(i))->getId() << std::endl;
              std::cout << "     name: " <<
                        ((CMiaseUniformTimeCourse*)myParser->mMiase->getSed()->getSimulation(i))->getName() << std::endl;

              std::cout << "        InitialTime: " <<
                        ((CMiaseUniformTimeCourse*)myParser->mMiase->getSed()->getSimulation(i))->getInitialTime() << std::endl;
              std::cout << "        OutputStartTime: " <<
                        ((CMiaseUniformTimeCourse*)myParser->mMiase->getSed()->getSimulation(i))->getOutputStartTime() << std::endl;
              std::cout << "        OutputEndTime: " <<
                        ((CMiaseUniformTimeCourse*)myParser->mMiase->getSed()->getSimulation(i))->getOutputEndTime() << std::endl;
              std::cout << "        NumberOfPoints: " <<
                        ((CMiaseUniformTimeCourse*)myParser->mMiase->getSed()->getSimulation(i))->getNumberOfPoints() << std::endl;
            }
        }

      std::cout << std::endl << std::endl;

      if (myParser->mMiase->getSed()->getNumOfModels() > 0)
        {
          std::cout << "NumOfModels: " <<
                    myParser->mMiase->getSed()->getNumOfModels() << std::endl << std::endl;

          for (i = 0 ; i < myParser->mMiase->getSed()->getNumOfModels() ; i++)
            {
              std::cout << "    Model nr. :" << i << std::endl;

              std::cout << "     id: " <<
                        myParser->mMiase->getSed()->getModel(i)->getId() << std::endl;
              std::cout << "     name: " <<
                        myParser->mMiase->getSed()->getModel(i)->getName() << std::endl;

              std::cout << "        type: " <<
                        myParser->mMiase->getSed()->getModel(i)->getType() << std::endl;
              std::cout << "        source: " <<
                        myParser->mMiase->getSed()->getModel(i)->getSource() << std::endl;

              if (myParser->mMiase->getSed()->getModel(i)->getNumOfChanges() > 0)
                {
                  std::cout << "              NumOfChanges: " <<
                            myParser->mMiase->getSed()->getModel(i)->getNumOfChanges() << std::endl << std::endl;

                  for (j = 0 ; j < myParser->mMiase->getSed()->getModel(i)->getNumOfChanges() ; j++)
                    {
                      std::cout << "                  Change nr. :" << j << std::endl;

                      if (myParser->mMiase->getSed()->getModel(i)->getChange(j)->mType == CMiaseChange::ATTRIBUTE)
                        {
                          std::cout << "                   Change the ATTRIBUTE: " << std::endl;
                          std::cout << "                     NewValue: " <<
                                    ((CMiaseChangeAttribute*)myParser->mMiase->getSed()->getModel(i)->getChange(j))->getNewValue() << std::endl;
                          std::cout << "                     Target: " <<
                                    ((CMiaseChangeAttribute*)myParser->mMiase->getSed()->getModel(i)->getChange(j))->getTarget() << std::endl;
                        }

                      if (myParser->mMiase->getSed()->getModel(i)->getChange(j)->mType == CMiaseChange::MATH)
                        {
                          std::cout << "                   Change the MATH: " << std::endl;
                          std::cout << "                     NewMath: " <<
                                    ((CMiaseChangeMath*)myParser->mMiase->getSed()->getModel(i)->getChange(j))->getNewMath() << std::endl;
                          std::cout << "                     Target: " <<
                                    ((CMiaseChangeMath*)myParser->mMiase->getSed()->getModel(i)->getChange(j))->getTarget() << std::endl;
                        }
                    }
                }
            }
        }

      std::cout << std::endl << std::endl;

      if (myParser->mMiase->getSed()->getNumOfTasks() > 0)
        {
          std::cout << "NumOfTasks: " <<
                    myParser->mMiase->getSed()->getNumOfTasks() << std::endl << std::endl;

          for (i = 0 ; i < myParser->mMiase->getSed()->getNumOfTasks() ; i++)
            {
              std::cout << "    Task nr. :" << i << std::endl;

              std::cout << "     id: " <<
                        ((CMiaseUniformTimeCourse*)myParser->mMiase->getSed()->getTask(i))->getId() << std::endl;
              std::cout << "     name: " <<
                        ((CMiaseUniformTimeCourse*)myParser->mMiase->getSed()->getTask(i))->getName() << std::endl;

              std::cout << "     notes: " <<
                        myParser->mMiase->getSed()->getTask(i)->getNotes()->getNotes() << std::endl;

              if (myParser->mMiase->getSed()->getTask(i)->getNumberOfMeasurements() > 0)
                {
                  std::cout << "           NumberOfMeasurements: " <<
                            myParser->mMiase->getSed()->getTask(i) << std::endl << std::endl;

                  for (j = 0 ; j < myParser->mMiase->getSed()->getTask(i)->
                       getNumberOfMeasurements() ; j++)
                    {
                      std::cout << "                 Measurement nr. :" << j << std::endl;

                      std::cout << "     source: " <<
                                myParser->mMiase->getSed()->getTask(i)->getMeasurement(j)->getSource() << std::endl;
                      std::cout << "     name: " <<
                                myParser->mMiase->getSed()->getTask(i)->getMeasurement(j)->getName() << std::endl;
                    }
                }
            }
        }

      std::cout << std::endl << std::endl;

      if (myParser->mMiase->getSed()->getNumOfOutputs() > 0)
        {
          std::cout << "NumOfOutputs: " <<
                    myParser->mMiase->getSed()->getNumOfOutputs() << std::endl << std::endl;

          for (i = 0 ; i < myParser->mMiase->getSed()->getNumOfOutputs() ; i++)
            {
              std::cout << "output nr: " << i << std::endl;
              std::cout << myParser->mMiase->getSed()->getOutput(i)->getWholeOutput() << std::endl;
            }
        }
    }
}
