#include "utilities.h"

string StringPrint( char * format, ... )
{
    long TextSize = INITIALTEXTSIZE;
    long Printed = 0;
    
    char *Text = NULL;
    
    va_list Arguments = NULL;
    va_start(Arguments, format);
    
    Text = new char[TextSize + 1];
    
    Printed = vsnprintf(Text, TextSize + 1, format, Arguments);

    while (Printed < 0 || TextSize < Printed)
    {
        delete [] Text;
        
        (Printed < 0) ? TextSize *= 2: TextSize = Printed;
        Text = new char[TextSize + 1];
        
        Printed = vsnprintf(Text, TextSize, format, Arguments);
    }
    va_end(Arguments);
    
    string Result = Text;
    
    delete [] Text;
    return Result;
}
