// James Kennedy G00341457




#include <stdio.h>


#include<stdint.h>

void sha256();
   //section 4.1.2 and 4.2.2
    uint32_t sigma_0(uint32_t x);
    uint32_t sigma_19(uint32_t x);

    uint32_t rotr(uint32_t n, uint32_t x);
    uint32_t shr(uint32_t n, uint32_t x);




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


    a = H[0];
    b = H[1];
    c = H[2];
    d = H[3];
    e = H[4];
    f = H[5];
    g = H[6];
    h = H[7];

    for(t = 0; t < 64; t++){
        T1 = h + sigma_1(e) + ch(e,f,g) + K[t] + W[t];
        T2 = sigma_0 + Maj(a,b,c);
        h = g;
        g = f;
        f = e;
        e = d + T1;
        d = c;
        c = b;
        b = a;
        a = T1 + T2;

    }
    H[0] = a + H[0];
    H[1] = b + H[1];
    H[2] = b + H[2];
    H[3] = b + H[3];
    H[4] = b + H[4];
    H[5] = b + H[5];
    H[6] = b + H[6];
    H[7] = b + H[7];




}


    uint32_t sigma_0(uint32_t x){
        //section 3.2
        //ROTR(x) = (x>>N) | (x <<(32-n))
        //shr_n(x) = (x >> n) 
        return (rotr(7,x) ^ rotr(18,x) ^ shr(3,x));
    }
    uint32_t sigma_19(uint32_t x){
        return (rotr(17,x) ^ rotr(19,x) ^ rotr(10,x));
    }
    uint32_t rotr(uint32_t n, uint32_t x){
        return (x >> n) | (x << (32 - n));
    }
    uint32_t shr(uint32_t n, uint32_t x){
        return(x >> n);
    }