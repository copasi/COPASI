
%include "../swig/copasi.i"

%pythoncode %{

CCopasiDataModel.GLOBAL=_COPASI.CCopasiDataModel_Global_get()

CCopasiObjectName.escape=_COPASI.CCopasiObjectName_escape
CCopasiObjectName.unescape=_COPASI.CCopasiObjectName_unescape

CCopasiMethod.TypeNameToEnum=_COPASI.CCopasiMethod_TypeNameToEnum

CCopasiContainer.ObjectFromName=_COPASI.CCopasiContainer_ObjectFromName

%}
