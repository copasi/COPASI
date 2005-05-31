/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/function/CEvaluationNodeConstant.h,v $
   $Revision: 1.6 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2005/05/31 17:48:57 $
   End CVS Header */

#ifndef COPASI_CEvaluationNodeConstant
#define COPASI_CEvaluationNodeConstant

/**
 * This is class for nodes presenting Constants used in an evaluation trees
 */
class CEvaluationNodeConstant : public CEvaluationNode
  {
  public:
    /**
     * Enumeration of possible node types.
     */
    enum SubType
    {
      INVALID = 0x00FFFFFF,
      PI = 0x00000000,
      EXPONENTIALE = 0x00000001,

#ifdef TRUE
# undef TRUE
#endif
      TRUE = 0x00000002,

#ifdef FALSE
# undef FALSE
#endif
      FALSE = 0x00000003
    };

    // Operations
  private:
    /**
     * Default constructor
     */
    CEvaluationNodeConstant();

  public:
    /**
     * Default constructor
     * @param const SubType & subType
     * @param const Data & data
     */
    CEvaluationNodeConstant(const SubType & subType,
                            const Data & data);

    /**
     * Copy constructor
     * @param const CEvaluationNodeConstant & src
     */
    CEvaluationNodeConstant(const CEvaluationNodeConstant & src);

    /**
     * Destructor
     */
    virtual ~CEvaluationNodeConstant();
  };

#endif // COPASI_CEvaluationNodeConstant
