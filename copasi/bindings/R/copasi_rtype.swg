
%typemap(scoercein) SWIGTYPE, SWIGTYPE *, SWIGTYPE *const, SWIGTYPE &  
 %{ 
   stopifnot(!is.null($input))
   if (inherits($input, "ExternalReference")) $input <- $input@ref
   stopifnot(typeof($input) != "externalptr" || !(capture.output($input) %in% c("<pointer: 0x0>", "<pointer: (nil)>")))
 %}

 %typemap(scoerceout) SWIGTYPE 
 %{
   if (capture.output($result) %in% c("<pointer: 0x0>", "<pointer: (nil)>")) return()
   $result <- new("$&R_class", ref=$result)
 %}
 
 %typemap(scoerceout) SWIGTYPE & 
 %{ 
    if (capture.output($result) %in% c("<pointer: 0x0>", "<pointer: (nil)>")) return()
    $result <- new("$R_class", ref=$result)
 %}
 
 %typemap(scoerceout) SWIGTYPE * 
 %{ 
    if (capture.output($result) %in% c("<pointer: 0x0>", "<pointer: (nil)>")) return()
    $result <- new("$R_class", ref=$result)
 %}
 
 %typemap(scoerceout) SWIGTYPE *const
 %{ 
    if (capture.output($result) %in% c("<pointer: 0x0>", "<pointer: (nil)>")) return()
    $result <- new("$R_class", ref=$result)
 %}
