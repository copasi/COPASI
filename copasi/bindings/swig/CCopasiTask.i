// Begin CVS Header 
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/bindings/swig/CCopasiTask.i,v $ 
//   $Revision: 1.15 $ 
//   $Name:  $ 
//   $Author: gauges $ 
//   $Date: 2008/01/15 17:17:08 $ 
// End CVS Header 

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc., EML Research, gGmbH, University of Heidelberg, 
// and The University of Manchester. 
// All rights reserved. 

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc. and EML Research, gGmbH. 
// All rights reserved. 

// Copyright © 2005 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

%include exception.i

%{
#include <exception>
#include "utilities/CCopasiTask.h"
#include "utilities/CCopasiException.h"
%}

%catches(CCopasiException) CCopasiTask::process();

class CCopasiTask : public CCopasiContainer
{
  public:
    /**
     * Enumeration of the types of tasks known to COPASI.
     */
    enum Type
    {
      steadyState = 0,
      timeCourse,
      scan,
      fluxMode,
      optimization,
      parameterFitting,
      mca,
      lyap,
#ifdef COPASI_DEBUG
      tss,
      sens,
#endif // COPASI_DEBUG
#ifdef COPASI_SSA
      ssa,
#endif // COPASI_SSA
      unset,
    };

    enum OutputFlag
    {
      NO_OUTPUT = 0,                       //do no output
      OUTPUT,                              //do output, but do not initialize/finish
      OUTPUT_COMPLETE          //do output, including initialization and closing
    };



    /**
     * Default constructor
     */
    CCopasiTask(const std::string & name = "NoName",
                const CCopasiContainer * pParent = NULL,
                const std::string & type = "Task");

    /**
     * Specific constructor
     * @param const Type & taskType
     * @param const CCopasiContainer * pParent (default: NULL)
     * @param const std::string & type (default: "Task")
     */
    CCopasiTask(const Type & taskType,
                const CCopasiContainer * pParent = NULL,
                const std::string & type = "Task");

    /**
     * Copy constructor
     * @param const CCopasiTask & src
     * @param const CCopasiContainer * pParent (default: NULL)
     */
    CCopasiTask(const CCopasiTask & src,
                const CCopasiContainer * pParent = NULL);

    /**
     * Destructor
     */
    virtual ~CCopasiTask();

    /**
     * Retrieve the type of the task
     * @return CCopasiTask::Type type
     */
    Type getType() const;

    /**
     * Set the type of the task
     * @param CCopasiTask::Type & type
     */
    void setType(const Type & type);


    /**
     * Retrieve the key for the task.
     * @return std::string key
     */
    virtual const std::string & getKey() const;

    /**
     * Set whether the task is scheduled
     * @param const bool & scheduled
     */
    void setScheduled(const bool & scheduled);

    /**
     * Check whether the task is scheduled
     * @return const bool & scheduled
     */
    const bool & isScheduled() const;

    /**
     * Set whether the task must update the model
     * @param const bool & updateModel
     */
    void setUpdateModel(const bool & updateModel);

    /**
     * Check whether the task must update the modle
     * @return const bool & updateModel
     */
    const bool & isUpdateModel() const;

    /**
     * Retrieve the problem
     */
    CCopasiProblem * getProblem();

    /**
     * Retrieve the method
     */
    CCopasiMethod * getMethod();

     /**
     * Set the method type applied to solve the task
     * @param const CCopasiMethod::SubType & type
     * @return bool success
     */
    virtual bool setMethodType(const int & type);

    /**
     * Retrieve the report
     */
    CReport & getReport();



%extend {
  std::vector<C_INT32> getValidMethods() const
    {
      std::vector<C_INT32> validMethods;
      unsigned int i=0;
      while(self->ValidMethods[i]!=CCopasiMethod::unset)
      {
        validMethods.push_back(self->ValidMethods[i]);
        i++;
      }
      return validMethods;
    } 

    virtual  bool process(bool useInitialValues) 
      {
        CCopasiMessage::clearDeque();
        bool result=$self->initialize(CCopasiTask::OUTPUT_COMPLETE,NULL);
        if(result)
        {
          result=$self->process(useInitialValues);
          CCopasiDataModel::Global->finish();
        }
        if(result)
        {
          result=$self->restore();
        }
        return result;
      }  
   
}  

};




