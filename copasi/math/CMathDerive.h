
#ifndef COPASI_CMathDerive
#define COPASI_CMathDerive

class CMathContainer;
class CEvaluationNode;

/**
 * This class contains all the information that is needed to calculate derivatives in a CMathContainer.
 * When initialised (through a constructor) it sets up the expression for symbolic derivatives and also determines
 * whether the derivative is constant (so that it is not reevaluated during simulations)
 */
class CMathDerive
{
public:
  
  CMathDerive(const CMathContainer* pContainer, size_t fun, size_t var);
  
  ///just for testing
  const CEvaluationNode* getRootNode();
  
private:

  void initOneVar(size_t fun, size_t var);
  
  
  
  const CMathContainer* mpContainer;
  
  CEvaluationNode* mpRootNode;



};



#endif

/*
TODOs:

- Make sure all valid functions can be derived (or implement a fallback)
-

*/
