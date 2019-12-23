#ifndef PEREVOROT_H
#define PEREVOROT_H

unsigned int Turn_int(unsigned  int a)
{
 union Turn_int_
  {
   unsigned int T;
   char  tar[4];
  };
 char tmp_tar[4];
 union Turn_int_  tmp;
 int i;
 tmp.T=a;
 for(i=0;i<4;i++)
   tmp_tar[i]=tmp.tar[i];
 for(i=0;i<4;i++)
   tmp.tar[i]=tmp_tar[3-i];
 return tmp.T;
}

unsigned short Turn_short(unsigned short a)
{
	unsigned short left = 0, right = 0, res = 0;
	left = a;
	right = a ;
	left = left << 8;
	right = right >> 8;
	res = left;
	res = res | right;
	return res;
}

#endif

