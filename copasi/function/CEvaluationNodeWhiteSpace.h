/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/function/CEvaluationNodeWhiteSpace.h,v $
   $Revision: 1.1 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2005/05/31 17:48:57 $
   End CVS Header */

#ifndef COPASI_CEvaluationNodeWhiteSpace
#define COPASI_CEvaluationNodeWhiteSpace

/**
 * This is class for nodes presenting numbers used in an evaluation trees
 */
class CEvaluationNodeWhiteSpace : public CEvaluationNode
  {
  public:
    /**
     * Enumeration of possible node types.
     */
    enum SubType
    {
      INVALID = 0x00FFFFFF,
      ANY = 0x00000000
    };

    // Operations
  private:
    /**
     * Default constructor
     */
    CEvaluationNodeWhiteSpace();

  public:
    /**
     * Default constructor
     * @param const SubType & subType
     * @param const Data & data
     */
    CEvaluationNodeWhiteSpace(const SubType & subType,
                              const Data & data);

    /**
     * Copy constructor
     * @param const CEvaluationNodeWhiteSpace & src
     */
    CEvaluationNodeWhiteSpace(const CEvaluationNodeWhiteSpace & src);

    /**
     * Destructor
     */
    virtual ~CEvaluationNodeWhiteSpace();
  };

#endif // COPASI_CEvaluationNodeWhiteSpace
