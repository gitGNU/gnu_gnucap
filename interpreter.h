#ifndef INTERP_H
#define INTERP_H


int isdelim(char c)
{
  if(strchr(" !;,+-<>'/*%^=()", c) || c==9 ||
     c=='\r' || c==0) return 1;  
  return 0; 
}
/* Return 1 if c is space or tab. */
int iswhite(char c)
{
  if(c==' ' || c=='\t') return 1;
  else return 0;
}

#endif


