// Copyright (C) 2019 - 2024 by Pedro Mendes, Rector and Visitors of the 
// University of Virginia, University of Heidelberg, and University 
// of Connecticut School of Medicine. 
// All rights reserved. 

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc., University of Heidelberg, and University of 
// of Connecticut School of Medicine. 
// All rights reserved. 

// Copyright (C) 2010 - 2016 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc., University of Heidelberg, and The University 
// of Manchester. 
// All rights reserved. 

// Copyright (C) 2008 - 2009 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc., EML Research, gGmbH, University of Heidelberg, 
// and The University of Manchester. 
// All rights reserved. 

// Copyright (C) 2006 - 2007 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc. and EML Research, gGmbH. 
// All rights reserved. 


%include exception.i

%{
#include <exception>
#include "copasi/utilities/CTaskEnum.h"
#include "copasi/utilities/CCopasiTask.h"
#include "copasi/utilities/CCopasiException.h"
%}

%catches(CCopasiException) CCopasiTask::process();

%ignore CCopasiTask::getDescription() const;
%ignore CCopasiTask::getResult() const;
%ignore CCopasiTask::XMLType;
%ignore CCopasiTask::TypeName;
%ignore CCopasiTask::ValidMethods;
%ignore CCopasiTask::process(bool const &);
//%ignore CCopasiTask::getCallBack;
//%ignore CCopasiTask::setCallBack;
%ignore CCopasiTask::isValidMethod;
%ignore CCopasiTask::initialize(const OutputFlag & of,
                          COutputHandler * pOutputHandler,
                          std::ostream * pOstream);

#if (defined SWIGJAVA || defined SWIGCSHARP)
// remove some const methods to get rid of warnings
%ignore CCopasiTask::getProblem() const;
%ignore CCopasiTask::getMethod() const;

// SWIG does not wrap this correctly in JAVA 
%ignore CCopasiTask::OutputFlagBase;
#endif // SWIGJAVA || SWIGCSHARP                      


%ignore CCopasiTask::getReport() const;

#ifdef SWIGR
// we ignore the method that takes an int and create a new method that takes
// the enum from CCopasiTask
%ignore CCopasiTask::setMethodType(const int& type);
#endif // SWIGR


// suppress warnings on nested structures
%warnfilter(325) CDescription;
%warnfilter(325) CResult;

#if (!defined SWIGJAVA)
%template(TaskSubTypeVector) std::vector<CTaskEnum::Task>;
%template(MethodSubTypeVector) std::vector<CTaskEnum::Method>;
#endif

%include "copasi/utilities/CTaskEnum.h"
%include "copasi/utilities/CCopasiTask.h"

%extend CCopasiTask{
  virtual bool setCallBack(CProcessReport *pHandler)
  {
    return self->setCallBack(CProcessReportLevel(pHandler));
  }

  std::vector<C_INT32> getValidMethods() const
    {
      const CTaskEnum::Method *methods = $self->getValidMethods();
      
      std::vector<C_INT32> validMethods;
      unsigned int i=0;
      while(methods[i]!=CTaskEnum::Method::UnsetMethod)
      {
        validMethods.push_back(static_cast< C_INT32>(methods[i]));
        ++i;
      }
      return validMethods;
    } 

    std::string getProcessError()
    {
      return self->Error;
    }
    
    std::string getProcessWarning()
    {
      return self->Warning;
    }
  
    bool initializeRaw(CCopasiTask::OutputFlag outputFlags)
    {
        bool success;
        CDataModel* pDataModel=self->getObjectDataModel();
        assert(pDataModel!=NULL);

        // Initialize the task
        try
        {
          success = self->initialize(outputFlags, pDataModel, NULL);
        }
        
        catch (CCopasiException &)
        {
          success = false;
        }
        
        catch (...) {}

        return success;
    }

    bool initializeRawWithOutputHandler(CCopasiTask::OutputFlag outputFlags, COutputHandler *pHandler)
    {
        bool success;

        // Initialize the task
        try
        {
          success = self->initialize(outputFlags, pHandler, NULL);
        }
        
        catch (CCopasiException &)
        {
          success = false;
        }
        
        catch (...) {}

        return success;
    }

    bool initialize(CCopasiTask::OutputFlag outputFlags)
    {
         bool success = true;
        CCopasiMessage::clearDeque();
        self->Warning = "";
        self->Error = "";
        CDataModel* pDataModel=self->getObjectDataModel();
        // Initialize the task
        try
        {
          if (!self->initialize(outputFlags, pDataModel, NULL))
          {
            throw CCopasiException(CCopasiMessage::peekLastMessage());
          }
        }

        catch (CCopasiException &)
        {
          if (CCopasiMessage::peekLastMessage().getNumber() != MCCopasiMessage + 1)
          {
            self->Error = CCopasiMessage::getAllMessageText();
            success = false;
            
          }
        }
        return success;
    }
  
    bool processRaw(bool useInitialValues)
    {
        bool success;
        CDataModel* pDataModel=self->getObjectDataModel();
        assert(pDataModel!=NULL);

        // Process the task
        try
        {
          success = self->process(useInitialValues);
        }
        
        catch (CCopasiException &)
        {
          success = false;
        }
        
        catch (...) {}

        self->restore();

        pDataModel->finish();

        return success;
    }

    bool processWithOutputFlags(bool useInitialValues, CCopasiTask::OutputFlag outputFlags) 
      {
        bool success = true;
        
        CCopasiMessage::clearDeque();
        CDataModel* pDataModel=self->getObjectDataModel();
        assert(pDataModel!=NULL);
        
        self->Warning = "";
        self->Error = "";
        
        // Initialize the task
        try
        {
          if (!self->initialize(outputFlags, pDataModel, NULL))
          {
            throw CCopasiException(CCopasiMessage::peekLastMessage());
          }
        }

        catch (CCopasiException &)
        {
          if (CCopasiMessage::peekLastMessage().getNumber() != MCCopasiMessage + 1)
          {
            self->Error = CCopasiMessage::getAllMessageText();
            success = false;
            
            goto restore;
          }
        }

        if (CCopasiMessage::getHighestSeverity() >= CCopasiMessage::COMMANDLINE)
        {
          self->Error = CCopasiMessage::getAllMessageText();
          success = true;
          if (
          CCopasiMessage::getHighestSeverity() == CCopasiMessage::ERROR ||
          CCopasiMessage::getHighestSeverity() == CCopasiMessage::EXCEPTION)
          {
            success = false;
            
            goto restore;
          }
        }

        CCopasiMessage::clearDeque();
        
        try 
        {
          success = self->process(useInitialValues);
        }
        
        catch (CCopasiException &)
        {
          success = false;
        }
        
        if (!success && CCopasiMessage::size() != 0)
        {
          self->Error = CCopasiMessage::getAllMessageText();
          success = false;
        }
        else if (CCopasiMessage::getHighestSeverity() >= CCopasiMessage::COMMANDLINE)
        {
          self->Warning = CCopasiMessage::getAllMessageText();
          success = true;
        }
        
        restore:
        
        CCopasiMessage::clearDeque();

        try 
        {
          self->restore();
        }

        catch (CCopasiException &)
        {
          if (CCopasiMessage::peekLastMessage().getNumber() != MCCopasiMessage + 1)
          { 
            self->Error = CCopasiMessage::getAllMessageText();
          }
        }

        catch (...) {}

        if (CCopasiMessage::getHighestSeverity() >= CCopasiMessage::COMMANDLINE)
        {
          self->Warning = CCopasiMessage::getAllMessageText();
        }

        CCopasiMessage::clearDeque();

        pDataModel->finish();
        
        if (self->getMathContainer() != NULL)
        {
           self->getMathContainer()->updateTransientDataValues();
           self->getMathContainer()->pushAllTransientValues();
        }
        
        return success;
      }  
     
    virtual bool process(bool useInitialValues) 
      {
        bool success = true;
        
        CCopasiMessage::clearDeque();
        CDataModel* pDataModel=self->getObjectDataModel();
        assert(pDataModel!=NULL);
        
        self->Warning = "";
        self->Error = "";
        
        // Initialize the task
        try
        {
          if (!self->initialize(CCopasiTask::OUTPUT_UI, pDataModel, NULL))
          {
            throw CCopasiException(CCopasiMessage::peekLastMessage());
          }
        }

        catch (CCopasiException &)
        {
          if (CCopasiMessage::peekLastMessage().getNumber() != MCCopasiMessage + 1)
          {
            self->Error = CCopasiMessage::getAllMessageText();
            success = false;
            
            goto restore;
          }
        }

        if (CCopasiMessage::getHighestSeverity() >= CCopasiMessage::COMMANDLINE)
        {
          self->Error = CCopasiMessage::getAllMessageText();
          success = true;
          if (
          CCopasiMessage::getHighestSeverity() == CCopasiMessage::ERROR ||
          CCopasiMessage::getHighestSeverity() == CCopasiMessage::EXCEPTION)
          {
            success = false;
            
            goto restore;
          }
        }

        CCopasiMessage::clearDeque();
        
        try 
        {
          success = self->process(useInitialValues);
        }
        
        catch (CCopasiException &)
        {
          success = false;
        }
        
        if (!success && CCopasiMessage::size() != 0)
        {
          self->Error = CCopasiMessage::getAllMessageText();
          success = false;
        }
        else if (CCopasiMessage::getHighestSeverity() >= CCopasiMessage::COMMANDLINE)
        {
          self->Warning = CCopasiMessage::getAllMessageText();
          success = true;
        }
        
        restore:
        
        CCopasiMessage::clearDeque();

        try 
        {
          self->restore();
        }

        catch (CCopasiException &)
        {
          if (CCopasiMessage::peekLastMessage().getNumber() != MCCopasiMessage + 1)
          { 
            self->Error = CCopasiMessage::getAllMessageText();
          }
        }

        catch (...) {}

        if (CCopasiMessage::getHighestSeverity() >= CCopasiMessage::COMMANDLINE)
        {
          self->Warning = CCopasiMessage::getAllMessageText();
        }

        CCopasiMessage::clearDeque();

        pDataModel->finish();
        
        if (self->getMathContainer() != NULL)
        {
           self->getMathContainer()->updateTransientDataValues();
           self->getMathContainer()->pushAllTransientValues();
        }
        
        
        return success;
      }

#ifdef SWIGR
   bool setMethodType(const CTaskEnum::Method& type)
   {
      return $self->setMethodType(type);
   }
#endif // SWIGR
}  





