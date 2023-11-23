#include <stdio.h>
#include <stdint.h>
#include "genpat.h"

#define LFSR_WIDTH 8
#define LFSR_TAP_BIT1 1
#define LFSR_TAP_BIT2 3
#define LFSR_TAP_BIT3 4
#define LFSR_TAP_BIT4 5

void updateLFSR(uint8_t*state){
	uint8_t lsb=*state & 1;
	uint8_t feedback = ((*state>>(LFSR_TAP_BIT1 - 1)) & 1)^
		((*state>>(LFSR_TAP_BIT2 - 1)) & 1)^
		((*state>>(LFSR_TAP_BIT3 - 1)) & 1)^
		((*state>>(LFSR_TAP_BIT4 - 1)) & 1);
	*state>>=1;
	if(feedback){
		*state^=(1<<7);//Bit mais significativo(MSB)
	}else{
		*state^=(0<<7);//Bit mais significativo(MSB)
	}	
}

char *inttostr(int inteiro) {
    char *str = (char *)malloc(32 * sizeof(char));
    if (str != NULL) {
        sprintf(str, "%d", inteiro);
    }
    return str;
}

int main(){
	uint8_t lfsr_state=0xB8;
	int tempo = 0;

	DEF_GENPAT("lfsr_sim");
	DECLAR("lfsr_state",":2","B",IN,"7 down to 0","");

	int i;
	for(i = 0;i<256;i++){
		updateLFSR(&lfsr_state);
		//fprintf(stdout,"Saida[%d]:%02X\n",i,lfsr_state);
		AFFECT(inttostr(tempo),"lfsr_state",inttostr(lfsr_state));
		tempo++;
	}

	SAV_GENPAT();
	return 0;

}