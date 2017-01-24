#ifndef __RNG_H__
#define __RNG_H__

void InitWELLRNG512a(unsigned int *init);
double rng(void);
int rng100();
int rng1000();

#endif