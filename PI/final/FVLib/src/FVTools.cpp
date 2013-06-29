#include "FVTools.h"

void strtos(char *ptr, char **endptr,char *auxString)
{
size_t pos,poss,strl;
strl=strlen(ptr);
pos=0;poss=0;
while((pos<strl) && ptr[pos]==32) pos++;
if (pos==strl){auxString[poss]='\0'; return;} // no string
// ok now I pointing on the first character
while(((pos+poss)<strl) &&  (ptr[pos+poss]!=32))
    {
    auxString[poss]=ptr[pos+poss];
    poss++;
    }
auxString[poss]='\0';
//std::cout <<((pos+poss)<strl) <<" " << (ptr[pos+poss]!=32)<<std::endl;
//std::cout<<"pos="<<pos<<" poss="<<poss<<" string="<<auxString<<std::endl;
*endptr=ptr+pos+poss;
}
