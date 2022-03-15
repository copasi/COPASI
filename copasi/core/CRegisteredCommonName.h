// Copyright (C) 2019 - 2022 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

#ifndef COPASI_CRegisteredCommonName
#define COPASI_CRegisteredCommonName

#include "copasi/core/CCommonName.h"

class CRegisteredCommonName: public CCommonName
{
public:
  class RenameInterface
  {
  public:
    typedef void (*Type)(const std::string & /* oldCN */,
                         const std::string & /* newCN */);

    virtual ~RenameInterface() {};

    virtual void operator()(const std::string & oldCN,
                            const std::string &  newCN) = 0;
  };

  class Rename : public RenameInterface
  {
  public:
    Rename() = delete;
    Rename(Type method);

    virtual ~Rename();

    // override operator "()"
    virtual void operator()(const std::string & oldCN,
                            const std::string & newCN);

  private:
    Type mMethod;
  };

  template <class Renamer>
  class ClassMemberRename : public RenameInterface
  {
  public:
    ClassMemberRename() = delete;

    ClassMemberRename(Renamer * pRenamer,
                      void (Renamer::*method)(const std::string & /* oldCN */,
                          const std::string & /* newCN */));

    virtual ~ClassMemberRename() {};

    // override operator "()"
    virtual void operator()(const std::string & oldCN,
                            const std::string & newCN);

  private:
    /**
     * The pointer to the instance of the caller
     */
    Renamer * mpRenamer;             // pointer to object
    void (Renamer::*mpMethod)(const std::string & /* oldCN */,
                              const std::string & /* newCN */);
  };

  /**
   * Default Constructor
   */
  CRegisteredCommonName();

  /**
   * Copy Constructor
   * @param const CRegisteredCommonName & src
   */
  CRegisteredCommonName(const CRegisteredCommonName & src);

  /**
   * Destructor
   */
  ~CRegisteredCommonName();

  /**
   * Constructor from base class
   * @param const std::string & name
   */
  CRegisteredCommonName(const std::string & name);

  /**
   * Enable and disable the rename handler
   * @param const bool & enabled
   */
  static void setEnabled(const bool & enabled);

  /**
   * Check whether the rename handler is enabled
   * @return const bool & enabled
   */
  static const bool & isEnabled();

  /**
   * Update all registered common names which contain
   * the oldCN
   * @param const std::string & oldCN
   * @param const std::string & newCN
   */
  static void handle(const std::string & oldCN,
                     const std::string & newCN);

  /**
   * Old files (before build 171) may have common name where invalid characters have been used.
   * This function sanitizes the name part
   */
  static void sanitizeObjectNames();

  /**
   * Register and additional handler
   * @param RenameInterface * pRenameHandler
   */
  static void registerHandler(RenameInterface * pRenameHandler);

  /**
   * Deregister and additional handler
   * @param RenameInterface * pRenameHandler
   */
  static void deregisterHandler(RenameInterface * pRenameHandler);

private:
  /**
   * A set which contains all registered comon names
   */
  static std::set< CRegisteredCommonName * > mSet;

  /**
   * A flag indicating whether renaming is enabled.
   */
  static bool mEnabled;

  /**
   * A set of registered handlers
   */
  static std::set< RenameInterface * > mRegisteredHandlers;
};

template <class Renamer>
CRegisteredCommonName::ClassMemberRename< Renamer >::ClassMemberRename(Renamer * pRenamer,
    void (Renamer::*method)(const std::string & /* oldCN */, const std::string & /* newCN */)):
  RenameInterface(),
  mpRenamer(pRenamer),
  mpMethod(method) {}

// override operator "()"
// virtual
template <class Renamer>
void CRegisteredCommonName::ClassMemberRename< Renamer >::operator()(const std::string & oldCN,
    const std::string & newCN)
{
  // execute member function
  return (*mpRenamer.*mpMethod)(oldCN, newCN);
}

#endif // COPASI_CRegisteredCommonName
