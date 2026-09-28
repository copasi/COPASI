// Copyright (C) 2019 - 2026 by Pedro Mendes, Rector and Visitors of the 
// University of Virginia, University of Heidelberg, and University 
// of Connecticut School of Medicine. 
// All rights reserved. 

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc., University of Heidelberg, and University of 
// of Connecticut School of Medicine. 
// All rights reserved. 

// Copyright (C) 2012 - 2016 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc., University of Heidelberg, and The University 
// of Manchester. 
// All rights reserved. 




%{

#include "copasi/plot/CPlotItem.h"

%}

%ignore CPlotItem::getChannels() const;
%ignore CPlotItem::XMLRecordingActivity;
%ignore CPlotItem::getRecordingActivityName;
%ignore CPlotItem::LineTypeNames;
%ignore CPlotItem::LineStyleNames;
%ignore CPlotItem::SymbolNames;

%extend CPlotItem {
  %{
    using CPlotItem_LineTypeNames = decltype(CPlotItem::LineTypeNames);
    using CPlotItem_LineTypeNames_Map = CBidirectionalMap< CPlotItem_LineTypeNames::EnumType, CPlotItem_LineTypeNames::AnnotationType, CPlotItem_LineTypeNames::Size >;
    using CPlotItem_LineTypeNames_AnnotationType = CEnumAnnotation< CPlotItem_LineTypeNames_Map >;

    using CPlotItem_LineStyleNames = decltype(CPlotItem::LineStyleNames);
    using CPlotItem_LineStyleNames_Map = CBidirectionalMap< CPlotItem_LineStyleNames::EnumType, CPlotItem_LineStyleNames::AnnotationType, CPlotItem_LineStyleNames::Size >;
    using CPlotItem_LineStyleNames_AnnotationType = CEnumAnnotation< CPlotItem_LineStyleNames_Map >;

    using CPlotItem_SymbolNames = decltype(CPlotItem::SymbolNames);
    using CPlotItem_SymbolNames_Map = CBidirectionalMap< CPlotItem_SymbolNames::EnumType, CPlotItem_SymbolNames::AnnotationType, CPlotItem_SymbolNames::Size >;
    using CPlotItem_SymbolNames_AnnotationType = CEnumAnnotation< CPlotItem_SymbolNames_Map >;
  %}

  const CPlotItem_LineTypeNames_AnnotationType& getLineTypeNames() {
    return CPlotItem::LineTypeNames;
  }

  const CPlotItem_LineStyleNames_AnnotationType& getLineStyleNames() {
    return CPlotItem::LineStyleNames;
  }

  const CPlotItem_SymbolNames_AnnotationType& getSymbolNames() {
    return CPlotItem::SymbolNames;
  }
}

%include "plot/CPlotItem.h"

