// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
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

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef SBMLDOCUMENTLOADER_H_
#define SBMLDOCUMENTLOADER_H_

#include <string>
#include <map>

#include "copasi/core/CDataVector.h"
#include "CLLocalStyle.h"
#include "CLGradientBase.h"

#include <sbml/ListOf.h>

class CDataObject;
class CDataContainer;
class CListOfLayouts;
class CLayout;

class CLTransformation2D;
class CLRenderInformationBase;
class CLTransformation2D;

LIBSBML_CPP_NAMESPACE_BEGIN
class Layout;
class SBase;
class TextGlyph;

class Transformation2D;
class RenderInformationBase;
LIBSBML_CPP_NAMESPACE_END

class SBMLDocumentLoader
{

public:

  static void readListOfLayouts(CListOfLayouts & lol,
                                const ListOf & sbmlList,
                                const std::map<const CDataObject*, SBase*> & copasimodelmap);

  // createLayout is now needed by the code for the CellDesigner import
  static CLayout * createLayout(const Layout & sbmlLayout,
                                const std::map<std::string, std::string> & modelmap,
                                std::map<std::string, std::string> & layoutmap
                                , const std::map<std::string, std::string>& globalIdToKeyMap
                                , const CDataContainer * pParent = NO_PARENT
                               );

protected:

  /**
   * resolves the graphical object reference of the text glyph
   */
  static void postprocessTextGlyph(const TextGlyph & sbml,
                                   const std::map<std::string, std::string> & layoutmap);

public:
  /**
   * converts the sbml id for render render information objects into the corresponding copasi key
   * where they are used in a reference.
   * This is used for the import from SBML.
   */
  template<typename RENDER_INFORMATION>
  static void convertRenderInformationReferencesIds(CDataVector<RENDER_INFORMATION>& list,
      const std::map<std::string, std::string> & idToKeyMap)
  {
    size_t i, iMax = list.size();
    RENDER_INFORMATION* pRI = NULL;
    std::map<std::string, std::string>::const_iterator pos;

    for (i = 0; i < iMax; ++i)
      {
        pRI = &list[i];

        if (pRI->getReferenceRenderInformationKey().find_first_not_of(" \t\n\r") != std::string::npos)
          {
            pos = idToKeyMap.find(pRI->getReferenceRenderInformationKey());
            assert(pos != idToKeyMap.end());
            pRI->setReferenceRenderInformationKey(pos->second);
          }
      }
  }

  /**
   * Converts references to ids of layout objects to the corresponding key.
   */
  static void convertLayoutObjectIds(CLLocalStyle& style, const std::map<std::string, std::string>& idToKeyMap);

  /**
   * converts references to color ids, gradient ids and/or line ending ids in graphical primitives
   * to references to the corresponding keys.
   */
  static void convertPropertyIds(CLTransformation2D* pObject,
                                 const std::map<std::string, std::string>& colorIdToKeyMap,
                                 const std::map<std::string, std::string>& gradientIdToKeyMap,
                                 const std::map<std::string, std::string>& lineEndingIdToKeyMap);

  /**
   * converts references to color ids in gradient stops
   * to references to the corresponding keys.
  static void convertColorIds(CLGradientBase& gradient,
          const std::map<std::string,std::string>& colorIdToKeyMap);
   */

  /**
   * converts the copasi key for global render information objects into the corresponding sbml id
   * where they are used in a reference.
   * This is used for the SBML export.
   */
  template<typename RENDER_INFORMATION>
  static void convertRenderInformationReferencesKeys(ListOf& list,
      const std::map<std::string, std::string> & keyToIdMap)
  {
    size_t i, iMax = list.size();
    RENDER_INFORMATION* pRI = NULL;
    std::map<std::string, std::string>::const_iterator pos;

    for (i = 0; i < iMax; ++i)
      {
        pRI = dynamic_cast<RENDER_INFORMATION*>(list.get((unsigned int) i));
        assert(pRI != NULL);

        if (pRI->getReferenceRenderInformationId().find_first_not_of(" \t\n\r") != std::string::npos)
          {
            pos = keyToIdMap.find(pRI->getReferenceRenderInformationId());

            if (pos == keyToIdMap.end())
              continue;

            pRI->setReferenceRenderInformationId(pos->second);
          }
      }
  }

  /**
   * Converts references to keys of layout objects to the corresponding id.
   */
  static void convertLayoutObjectKeys(LocalStyle& style, const std::map<std::string, std::string>& keyToIdMap);

  /**
   * converts references to color keys, gradient keys and/or line ending keys in graphical primitives
   * to references to the corresponding Ids.
  template<typename RENDER_INFORMATION>
  static void convertPropertyKeys(RENDER_INFORMATION* pObject,
          const std::map<std::string,std::string>& colorKeyToIdMap,
          const std::map<std::string,std::string>& gradientKeyToIdMap,
          const std::map<std::string,std::string>& lineEndingKeyToIdMap);
   */

  /**
   * converts references to color keys, gradient keys and/or line ending keys in graphical primitives
   * to references to the corresponding Ids.
  static void convertPropertyKeys(Transformation2D* pObject,
          const std::map<std::string,std::string>& colorKeyToIdMap,
          const std::map<std::string,std::string>& gradientKeyToIdMap,
          const std::map<std::string,std::string>& lineEndingKeyToIdMap);
   */

  /**
   * converts references to color ids in gradient stops
   * to references to the corresponding keys.
  static void convertColorKeys(GradientBase& gradient,
          const std::map<std::string,std::string>& colorKeyToIdMap);
   */

  /**
   * Adds all elements of the source map into the dest map if an element with the same key does not already exist in the dest map.
   */
  static void combineMaps(
    const std::map<std::string, std::string>& sourceMap,
    std::map<std::string, std::string>& destMap
  );

  /**
   * Creates maps of maps for the colors, gradients and line endings of the given of render information
   * objects.
   * Those maps can than be used to convert the id of a color, gradient or lineEnding from the SBML model
   * to the key used in the COPASI model.
  template<typename RENDER_INFORMATION>
  static void expandIdToKeyMaps(const CLRenderInformationBase* pRenderInfo,
          CDataVector<RENDER_INFORMATION>& renderInformationVector,
          std::map<std::string,std::map<std::string,std::string> >& colorIdToKeyMapMap,
          std::map<std::string,std::map<std::string,std::string> >& gradientIdToKeyMapMap,
          std::map<std::string,std::map<std::string,std::string> >& lineEndingIdToKeyMapMap,
          const std::map<std::string,std::map<std::string,std::string> >& unexpandedColorIdToKeyMapMap,
          const std::map<std::string,std::map<std::string,std::string> >& unexpandedGradientIdToKeyMapMap,
          const std::map<std::string,std::map<std::string,std::string> >& unexpandedLineEndingIdToKeyMapMap,
          std::set<std::string>& chain,
          const std::map<std::string,std::map<std::string,std::string> >& expandedGlobalColorIdToKeyMapMap,
          const std::map<std::string,std::map<std::string,std::string> >& expandedGlobalGradientIdToKeyMapMap,
          const std::map<std::string,std::map<std::string,std::string> >& expandedGlobalLineEndingIdToKeyMapMap
          );
   */

  /**
   * Creates maps of maps for the colors, gradients and line endings of the given of render information
   * objects.
   * Those maps can than be used to convert the id of a color, gradient or lineEnding from the SBML model
   * to the key used in the COPASI model.
  static void expandKeyToIdMaps(const RenderInformationBase* pRenderInfo,
          ListOf& renderInformationVector,
          std::map<std::string,std::map<std::string,std::string> >& colorKeyToIdMapMap,
          std::map<std::string,std::map<std::string,std::string> >& gradientKeyToIdMapMap,
          std::map<std::string,std::map<std::string,std::string> >& lineEndingKeyToIdMapMap,
          const std::map<std::string,std::map<std::string,std::string> >& unexpandedColorKeyToIdMapMap,
          const std::map<std::string,std::map<std::string,std::string> >& unexpandedGradientKeyToIdMapMap,
          const std::map<std::string,std::map<std::string,std::string> >& unexpandedLineEndingKeyToIdMapMap,
          std::set<std::string>& chain,
          const std::map<std::string,std::map<std::string,std::string> >& expandedGlobalColorKeyToIdMapMap,
          const std::map<std::string,std::map<std::string,std::string> >& expandedGlobalGradientKeyToIdMapMap,
          const std::map<std::string,std::map<std::string,std::string> >& expandedGlobalLineEndingKeyToIdMapMap
          );
   */
};

#endif /*SBMLDOCUMENTLOADER_H_*/
