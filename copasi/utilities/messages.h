MESSAGES Messages[] =
  {
    // CReadConfig
    {MCReadConfig + 1, "CReadConfig (1): Variable '%s' not found in '%s(%d)'."},
    {MCReadConfig + 2, "CReadConfig (2): Cannot open file '%s'."},
    {MCReadConfig + 3, "CReadConfig (3): Cannot read file '%s'."},
    {MCReadConfig + 4, "CReadConfig (4): Cannot close file '%s'."},
    {MCReadConfig + 5, "CReadConfig (5): Invalid type '%s' for  Variable '%s'."},

    // CKinFunction
    {MCKinFunction + 1, "CKinFunction (1): Cannot find identifier '%s'"
     " in function '%s'."},
    {MCKinFunction + 2, "CKinFunction (2): Missing operant in function '%s'."},

    // CRange
    {MCRange + 1, "CRange (1): Invalid range ('%d', '%d')."},

    // CCopasiVector
    {MCCopasiVector + 1, "CCopasiVector (1): Object '%s' not found."},
    {MCCopasiVector + 2, "CCopasiVector (2): Object '%s' allready exists."},

    // CFunctionParameters
    {MCFunctionParameters + 1, "CFunctionParameters (1): The usage '%s' "
     "is not unique for a vector type parameter ('%d')."},
    {MCFunctionParameters + 2, "CFunctionParameters (2): No parameter with "
     "usage '%s' with index >= '%ld'."},

    // CMassAction
    {MCMassAction + 1, "CMassAction (1): The function Mass Action reversibility "
     "must be either TRUE or FALSE."},

    // CMethodParameterList
    {MCMethodParameterList + 1, "CMethodParameterList (1): No parameter list "
     "found for name '%s' and type '%'."},

    // CRraction
    {MCReaction + 1, "CReaction (1): Function '%s' not found."},

    // This must be the last element of the message list! Do not delete!
    {0, NULL}
  };
