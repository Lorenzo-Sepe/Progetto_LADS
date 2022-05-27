#include "Miscellanee.h"
#include <ctype.h>

string FormattazioneTappe(string TappaInput){
    int i;
    
    //formatta la stringa per avere solo la prima lettera maiuscola
    for (i=0; i < MAX_STRINGHE; i++)
    {
        TappaInput[i]=tolower(TappaInput[i]);
    }
    TappaInput[0]=toupper(TappaInput[0]);  

    return TappaInput;
}