
%include "../swig/copasi.i"

%pythoncode %{

CCopasiDataModel.GLOBAL=_COPASI.CCopasiDataModel_Global_get()

%}
