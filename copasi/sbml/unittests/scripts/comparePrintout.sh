#!/bin/bash

PRINTOUT1=$1
export PRINTOUT2=$2
echo $PRINTOUT2


gawk 'BEGIN {
  reference=ENVIRON["PRINTOUT2"]
  print "reference file: \""reference"\""
  if(reference!="")
  {
    while ((getline < reference) > 0)
    {
      if($1=="functionDefinitions:" || 
         $1=="unitDefinitions:"     ||
         $1=="compartmentTypes:"    ||
         $1=="speciesTypes:"        ||
         $1=="compartments:"        ||
         $1=="species:"             ||
         $1=="parameters:"          ||
         $1=="initialAssignments:"  ||
         $1=="rules:"               ||
         $1=="constraints:"         ||
         $1=="reactions:"           || 
         $1=="events:"                )
      {
        elements[$1] = $2
      }
    }
  }
}
{
  if($1=="functionDefinitions:")
  {
    # $2 must be greater or equal to the one from the reference file
    if($2 < elements[$1])
    {
       print "ERROR. The number of function definitions is smaller than in the reference file."
    }
    else
    {
        print "Same number or more function definitions."
    }
  }
#  else if($1=="unitDefinitions:")
#  {
#    # ignored
#  }
#  else if($1=="compartmentTypes:")
#  {
#    #ignored
#  }
#  else if($1=="speciesTypes:")
#  {
#    # ignored
#  }
  else if($1=="compartments:")
  {
    # must be equal to the number from the reference file
    if($2 != elements[$1])
    {
       print "ERROR. The number of compartments is not equal to the number of compartments in the reference file."
    }
    else
    {
        print "Same number of compartments."
    }
  }
  else if($1=="species:")
  {
    # must be equal to the number from the reference file
    if($2 != elements[$1])
    {
       print "ERROR. The number of species is not equal to the number of species in the reference file."
    }
    else
    {
        print "Same number of species."
    }
  }
  else if($1=="parameters:")
  {
    # must be equal to the number from the reference file
    if($2 != elements[$1])
    {
       print "ERROR. The number of parameters is not equal to the number of parameters in the reference file."
    }
    else
    {
        print "Same number of parameters."
    }
  }
#  else if($1=="initialAssignments:")
#  {
#    # ignored
#  }
  else if($1=="rules:")
  {
    # must be equal to the number from the reference file
    if($2 != elements[$1])
    {
       print "ERROR. The number of rules is not equal to the number of rules in the reference file."
    }
    else
    {
        print "Same number of rules."
    }
  }
#  else if($1=="constraints:")
#  {
#    # ignored
#  }
  else if($1=="reactions:")
  {
    # must be equal to the number from the reference file
    if($2 != elements[$1])
    {
       print "ERROR. The number of reactions is not equal to the number of reactions in the reference file."
    }
    else
    {
        print "Same number of reactions."
    }
  }
#  else if($1=="events:")
#  {
     #ignored
#  }
}' $PRINTOUT1
