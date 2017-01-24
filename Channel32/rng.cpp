#include "rng.h"

#define xxxW 32
#define xxxR 16
#define xxxP 0
#define xxxM1 13
#define xxxM2 9
#define xxxM3 5

#define xxxMAT0POS(t,v) (v^(v>>t))
#define xxxMAT0NEG(t,v) (v^(v<<(-(t))))
#define xxxMAT3NEG(t,v) (v<<(-(t)))
#define xxxMAT4NEG(t,b,v) (v ^ ((v<<(-(t))) & b))

#define xxxV0            STATE[state_i                   ]
#define xxxVM1           STATE[(state_i+xxxM1) & 0x0000000fU]
#define xxxVM2           STATE[(state_i+xxxM2) & 0x0000000fU]
#define xxxVM3           STATE[(state_i+xxxM3) & 0x0000000fU]
#define xxxVRm1          STATE[(state_i+15) & 0x0000000fU]
#define xxxVRm2          STATE[(state_i+14) & 0x0000000fU]
#define xxxnewV0         STATE[(state_i+15) & 0x0000000fU]
#define xxxnewV1         STATE[state_i                 ]
#define xxxnewVRm1       STATE[(state_i+14) & 0x0000000fU]

#define xxxFACT 2.32830643653869628906e-10

static unsigned int state_i = 0;
static unsigned int STATE[xxxR];
static unsigned int z0, z1, z2;

void InitWELLRNG512a(unsigned int *init) {
	int j;
	state_i = 0;
	for (j = 0; j < xxxR; j++)
		STATE[j] = init[j];
}

double rng(void) {
	z0 = xxxVRm1;
	z1 = xxxMAT0NEG(-16, xxxV0) ^ xxxMAT0NEG(-15, xxxVM1);
	z2 = xxxMAT0POS(11, xxxVM2);
	xxxnewV1 = z1                  ^ z2;
	xxxnewV0 = xxxMAT0NEG(-2, z0) ^ xxxMAT0NEG(-18, z1) ^ xxxMAT3NEG(-28, z2) ^ xxxMAT4NEG(-5, 0xda442d24U, xxxnewV1);
	state_i = (state_i + 15) & 0x0000000fU;
	return ((double)STATE[state_i]) * xxxFACT;
}

int rng100()
{
	return rng() * 100;
}

int rng1000()
{
	return rng() * 1000;
}
