/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/elementaryFluxModes/CFluxMode.h,v $
   $Revision: 1.9 $
   $Name:  $
   $Author: ssahle $ 
   $Date: 2004/09/26 21:48:35 $
   End CVS Header */

/**
 *  CFluxMode class.
 *  Used to return the flux modes in human readable form
 *
 *  Created for Copasi by Stefan Hoops 2002-05-10
 * (C) Stefan Hoops 2002
 */

#ifndef COPASI_CFluxMode
#define COPASI_CFluxMode

#include <vector>

class CReaction;
class CModel;
class CTableauLine;

class CFluxMode
  {
    // Attributes

  private:
    /**
     *  Vector containing an index to a reaction and the multiplier
     *  for that reaction.
     */
    std::vector < std::pair < unsigned C_INT32, C_FLOAT64 > > mReactions;

    /**
     *  Reversibility of the mode.
     */
    bool mReversible;

    // Operations

  public:
    /**
     *  Default constructor
     */
    CFluxMode();

    /**
     *  Copy constructor
     *  @param "const CFluxMode &" src
     */
    CFluxMode(const CFluxMode & src);

    /**
     *  Specific constructor
     *  @param "const CTableauLine &" line
     */
    CFluxMode(const CTableauLine * line);

    /**
     *  Destructor
     */
    ~CFluxMode();

    /**
     *  Retrieve the index of the reaction
     *  @param "unsigned C_INT32 " index
     *  @return "unsigned C_INT32 " index
     */
    unsigned C_INT32 getReactionIndex(unsigned C_INT32 index) const;

    //const CReaction * getReaction(unsigned C_INT32 index, const CModel * model) const;
    //std::string getReactionName(unsigned C_INT32 index, const CModel * model) const;
    //std::string getReactionEquation(unsigned C_INT32 index, const CModel * model) const;

    /**
     *  Retrieves the multiplier for the reaction
     *  @param "unsigned C_INT32 " index
     *  @return "unsigned C_FLOAT64 " index
     */
    const C_FLOAT64 & getMultiplier(unsigned C_INT32 index) const;

    /**
     *  Check whether the mode is reversible
     *  @return "bool" isReversible
     */
    bool isReversible() const;

    /**
     *  Retrieves the size of the mode
     *  @return "unsigned C_INT32" size
     */
    unsigned C_INT32 size() const;
  };

#endif // COPASI_CFluxMode
