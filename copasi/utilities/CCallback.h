// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2014 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#ifndef COPASI_Callback
#define COPASI_Callback

class CCallbackInterface
{
public:
  typedef void (*Type)(void * /* pData */,
                       void * /* pCaller */);

  virtual ~CCallbackInterface() {};

  virtual void operator()(void * /* pData */ = NULL,
                          void * /* pCaller */ = NULL) = 0;
};

template <class Callee>
class CCallback : public CCallbackInterface
{
private:
  /**
   * The pointer to the instance of the caller
   */
  Callee * mpInstance;             // pointer to object
  void (Callee::*mMethod)(void * /* pData */,
                          void * /* pCaller */);
private:
  CCallback():
    CCallbackInterface(),
    mpInstance(NULL),
    mMethod(NULL)
  {}

public:
  CCallback(Callee * pInstance,
            void (Callee::*method)(void * /* pData */,
                                   void * /* pCaller */)):
    CCallbackInterface(),
    mpInstance(pInstance),
    mMethod(method)
  {}

  virtual ~CCallback() {}

  // override operator "()"
  virtual void operator()(void * pData = NULL,
                          void * pCaller = NULL)
  {
    // execute member function
    (*mpInstance.*mMethod)(pData, pCaller);
  }
};

class CStaticCallback : public CCallbackInterface
{
private:
  Type mMethod;

  CStaticCallback():
    CCallbackInterface(),
    mMethod(NULL)
  {}

public:
  CStaticCallback(Type method):
    CCallbackInterface(),
    mMethod(method)
  {}

  virtual ~CStaticCallback() {}

  // override operator "()"
  virtual void operator()(void * pData = NULL,
                          void * pCaller = NULL)
  {
    // execute member function
    (*mMethod)(pData, pCaller);
  }
};
#endif // COPASI_Callback
