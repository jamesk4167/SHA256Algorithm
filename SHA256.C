// James Kennedy G00341457




#include <stdio.h>


#include<stdint.h>

void sha256();
   //section 4.1.2 and 4.2.2
    uint32_t sigma_0(uint32_t x);
    uint32_t sigma_19(uint32_t x);




int main(int argc, char *argv[]){


    sha256();
    return 0;
}


void sha256(){

    //section 4.1.2 and 4.2.2
    uint32_t sigma_0(uint32_t x);
    uint32_t sigma_19(uint32_t x);

    uint32_t W[64];

    uint32_t a,b,c,d,e,f,g,h;

    

    uint32_t T1, T2;
    uint32_t H[8] = {
        0x6a09a667,
        0xbb67ae85,
        0x3c6ef372,
        0xa54ff53a,
        0x519e527f,
        0x9b05688c,
        0x1f83d9ab,
        0x5be0cd19
    };


    uint32_t M[16];

    

    for(int t = 0; i < 16; i++)
        W[t] = M[t];

    for(t = 16; t < 64; t++){
        sigma_1(w[t - 2]) + W[t - 7] + sigma_0(W[t - 15]) + W[t - 16]);
    }

    uint32_t sigma_0(uint32_t x){
        //section 3.2
        //ROTR(x) = (x>>N) | (x <<(32-n))
        //shr_n(x) = (x >> n) 
    }
    uint32_t sigma_19(uint32_t x){

    }
     
}