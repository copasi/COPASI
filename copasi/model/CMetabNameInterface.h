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

// Copyright (C) 2003 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

//
//
// C++ Interface: $MODULE$
//
// Description:
//
//
// Author: sven <sven@ares>, (C) 2003
//
// Copyright: See COPYING file that comes with this distribution
//
//
#ifndef COPASI_CMetabNameInterface
#define COPASI_CMetabNameInterface

#include <copasi/copasi.h>
#include <copasi/model/CMetab.h>

#include <string>
#include <utility>

class CModel;

/**
 * @class CMetabNameInterface
 *
 * This class handles the display names of metabolites. It converts "Species" to
 * "Species {Compartment}" if the metabolite name is not unique. If it is unique
 * (that means it occurs in only one compartment) then the "{Compartment}" is not added.
 */
/** @dia:pos 51.5,-17.9 */
class CMetabNameInterface
{
public:

  /**
   * This returns a name to use for display in the GUI. If the name of the
   * metabolite is unique it is used unaltered. If it is not then the compartment
   * is added to the name to make it unique.
   *
   */
  static std::string getDisplayName(const CModel* model, const std::string & key, const bool & quoted);

  /**
   * This returns a name to use for display in the GUI. If the name of the
   * metabolite is unique it is used unaltered. If it is not then the compartment
   * is added to the name to make it unique.
   */
  static std::string getDisplayName(const CModel* model, const CMetab & metab, const bool & quoted);

  /**
   * This returns a name to use for display in the GUI. If the name of the
   * metabolite is unique it is used unaltered. If it is not then the compartment
   * is added to the name to make it unique.
   */
  static std::string getDisplayName(const CModel* model,
                                    const std::string & metabolite,
                                    const std::string & compartment,
                                    const bool & quoted);

  /**
   * Returns the unique display name in the form metabolite{compartment}
   *
   * @param metabolite the metabolite name
   * @param compartment the compartment name
   *
   * @return the unique display name in the form metabolite{compartment}
   */
  static std::string createUniqueDisplayName(const std::string& metabolite,
      const std::string& compartment,
      const bool & quoted);

  /**
  * Returns the unique display name in the form metabolite{compartment}
  *
  * @param metab the metabolite
  *
  * @return the unique display name in the form metabolite{compartment}
  */
  static std::string createUniqueDisplayName(const CMetab& metab,
      const bool & quoted);

  /**
    * This tries to find the metabolite with the given name. If the name is not unique and
    * is given without a compartment then the first occurrence of a metabolite with this name
    * is returned.
    */
  static CMetab * getMetabolite(const CModel* model,
                                const std::string & metabolite,
                                const std::string & compartment);

  static std::string getMetaboliteKey(const CModel* model,
                                      const std::string & metabolite,
                                      const std::string & compartment);

  /**
   * Create the CN for the named species in the provided compartment.
   * @param const CModel * pModel
   * @param const std::string & species
   * @param const std::string & compartment
   */
  static std::string getSpeciesCN(const CModel* pModel,
                                  const std::string & species,
                                  const std::string & compartment);

  /**
  * This returns whether the metabolite name is unique.
  */
  static bool isUnique(const CModel* model, const std::string & name);

  /**
   * This returns whether a metabolite with the given name does exist. If a compartment is
   * also given (as an appendix to the name) then it only returns true if the metabolite
   * exists in the specified compartment.
   */
  static bool doesExist(const CModel* model,
                        const std::string & metabolite,
                        const std::string & compartment);

  static std::pair< std::string, std::string > splitDisplayName(const std::string & name);

  static std::string unQuote(const std::string & displayName);

#ifdef XXXX
  /**
   * This extracts the compartment name from the given metabolite display name. If no compartment name is
   * present in the given metabolite name then the name of the (first) compartment the metabolite is really
   * in is given. If the metabolite does not exist and the name does not contain a compartment
   * then the name of the first compartment in the model is returned.
   */
  static std::string extractCompartmentName(const std::string & name);

  /**
   * This extracts the metabolite name from the given metabolite display name.
   */
  static std::string extractMetabName(const std::string & name);

  /**
   *  This checks if the metabolite name (possibly including the compartment) is valid.
   * A valid name must be in the format of "species" or "species{compartment}"
   * and does not contain white spaces. (Other special characters are not considered yet.)
   * Neither metabolite nor  compartment can be an empty string.
   */
  static bool isValidMetabDisplayName(const std::string & name);
#endif // XXXX
};

#endif
