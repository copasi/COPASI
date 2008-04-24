# delete empty lines
#/^$/d
# no units on parameters
/80701 \[Warning\]/,+1d 
# uncheckable units
/99505 \[Warning\]/,+1d
# units to function calls
/10501 \[Warning\]/,+1d
# rule for species must have correct units
/10512 \[Warning\]/,+1d
# rule for parameter must have correct units
/10513 \[Warning\]/,+1d
