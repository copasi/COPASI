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

class CTableauLine;

using std::vector;
using std::pair;

class CFluxMode
  {
    // Attributes

  private:
    /**
     *  Vector containing an index to a reaction an the multiplier
     *  for that reaction.
     */
    vector < pair < unsigned C_INT32, C_FLOAT64 > > mReactions ;

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
     *  @param "const unsigned C_INT32 &" index
     *  @return "const unsigned C_INT32 &" index
     */
    const unsigned C_INT32 & getReaction(const unsigned C_INT32 & index) const;

    /**
     *  Retrieves the multiplier for the reaction
     *  @param "const unsigned C_INT32 &" index
     *  @return "const unsigned C_INT32 &" index
     */
    const C_FLOAT64 & getMultiplier(const unsigned C_INT32 & index) const;

    /**
     *  Check whether the mode is reversible
     *  @return "const bool &" isReversible
     */
    const bool & isReversible() const;

    /**
     *  Retrieves the size of the mode
     *  @return "const unsigned C_INT32 &" size
     */
    const unsigned C_INT32 size() const;
  };

#endif // COPASI_CFluxMode
