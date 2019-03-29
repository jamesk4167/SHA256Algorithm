// James Kennedy G00341457




#include <stdio.h>

#include <stdlib.h>
#include<stdint.h>

#include<unistd.h>

//represents a message block
union msgBlock{

uint8_t e[64];
uint32_t t[32];
uint64_t s[8];
};


//a flag for reading the file
enum status {READ, PAD0, PAD1, FINISH};

void sha256(FILE *f);

static const uint32_t K[64] = {
        0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5,
        0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
        0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3, 
        0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
        0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc, 
        0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da, 
        0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7, 
        0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
        0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13, 
        0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85, 
        0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3,
        0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070, 
        0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5, 
        0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3, 
        0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208, 
        0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2,
    };
   //section 4.1.2 and 4.2.2
    //created definitions to help with memort management
    #define sigma_1(x) (ROTR(x,17) ^ ROTR(x,19) ^ ROTR(x,10))
    #define sigma_0(x) (ROTR(x,7) ^ ROTR(x,18) ^ ROTR(x,3))


   #define EP0(x) (ROTR(x,2) ^ ROTR(x,13) ^ ROTR(x,22))
   #define EP1(x) (ROTR(x,6) ^ ROTR(x,11) ^ ROTR(x,25))
   


    #define CH(x,y,z) ((x & y) ^ ((!x) & z))

    #define MAJ(x,y,z) ((x & y) ^ (x & z) ^ (y & z))

    #define ROTR(n,x) ((x >> n) | (x << (32 - n)))
    #define shr(n,x) (((x) >> n))
    #define SWAP_UINT32(x) (((x) >> 24) | (((x) & 0x00FF0000) >> 8) | (((x) & 0x0000FF00) << 8) | ((x) << 24))


    //retrieve the next message block
    // will return 1 when there are messageblocks and 0 when there are no more
    int nextMsgBlk(FILE *f, union msgBlock *M, enum status *s, uint64_t *nobits);

    uint32_t W[64];
    
    


    int main(int argc, char *argv[]){
    FILE* msgFile;  
    int n = 1;
    
    

    //check if a file has been inputted
    if((msgFile = fopen(argv[1],"r"))!=NULL)
    
        {
            
        //pass the file to sha256
            sha256(msgFile);
            fclose(msgFile);
        }
    else
        {
            printf("Error: File not found \n");
        }
    return 0;
}




//Sha256
void sha256(FILE *msgFile){
    //the current messageBlock
    union msgBlock M;

    //the number of bits read from thr gilr
    uint64_t noBits = 0;
    
    //status of message block
    enum status s = READ;


    
    uint32_t a,b,c,d,e,f,g,h;

    uint32_t T1, T2;
    

    //initial valuies for H
    uint32_t H[8] = {
        0x6a09a667,0xbb67ae85,
        0x3c6ef372,0xa54ff53a,
        0x519e527f,0x9b05688c,
        0x1f83d9ab,0x5be0cd19
    };
    


    
    //for loop to iterate through array
    int t, i;
    //check the next message
    while(nextMsgBlk(msgFile, &M, &s, &noBits)){
    for(t = 0; t < 16; t++)
    //converting from little endian to big endian
        W[t] = SWAP_UINT32(M.t[t]);

    for(t = 16; t < 64; t++){
       W[t] = sigma_1(W[t - 2]) + W[t - 7] + sigma_0(W[t - 15]) + W[t - 16];

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
        T1 = h + EP1(e) + CH(e,f,g) + K[t] + W[t];
        T2 = EP0(a) + MAJ(a, b, c);
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
    H[2] = c + H[2];
    H[3] = d + H[3];
    H[4] = e + H[4];
    H[5] = f + H[5];
    H[6] = g + H[6];
    H[7] = h + H[7];


    }

    printf("%x %x %x %x %x %x %x %x ", H[0],H[1],H[2],H[3],H[4],H[5],H[6],H[7]);
}




//end of code from this file the rest

//next message block
int nextMsgBlk(FILE *f, union msgBlock *MsgBlk, enum status *s, uint64_t *noBits){

    //the number of bytes we get from fread.
    uint64_t NoOfBytes;
    //For looping
    int i;


    if (*s == FINISH)
        return 0;

    //check if we need another block full of padding.
    if(*s == PAD0 || *s == PAD1){
        //set the first 56 bytes to zero bits
        for(i = 0; i < 56; i++){
            MsgBlk->e[i] = 0x00;
        }//set the last 64 bits to an integer (should be big endian)
        MsgBlk->s[7] = *noBits;
        //Tell s we are finished
        *s = FINISH;
        //if s was pd1 then set the first bit of M to one.
        if(*s == PAD1){
        MsgBlk->e[0] = 0x80;
    }
    return 1;
    }
    //if s was pad1 then set the first bit of M to one.
    
    //check for error
        //if we get here we havent finished reading the file
        NoOfBytes = fread(MsgBlk->e, 1, 64, f);
        //keep track of the number of bytes we have read
        *noBits = *noBits + (NoOfBytes * 8);
        //if we read less then 56 bytes we can put all padding in this block
        if(NoOfBytes < 56 ){
            
            MsgBlk->e[NoOfBytes] = 0x80;
            while((NoOfBytes < 56)){
                NoOfBytes = NoOfBytes + 1;
                MsgBlk->e[NoOfBytes] = 0x00;
            }
            //append the file size in bits as a big endian unsigned 64 int.
           MsgBlk->s[7] = *noBits; 
           //Tell s we are finished
           *s = FINISH;
        //otherwise check fif we can put some padding into this block
        }else if(NoOfBytes < 64 ){
            //tell s we need another message block with padding but no 1 bits
            *s = PAD0;
            //put the one bit into current block
            MsgBlk->e[NoOfBytes] = 0x80;
            //pad the rest of the block with zero bits.
            while(NoOfBytes < 64){
                NoOfBytes = NoOfBytes + 1;
                MsgBlk->e[NoOfBytes] = 0x00;
            }
            //need to check if at nd of file(checks if file is exactly 512 bytes so no bits at end)
        }else if(feof(f)){
            //tell s that we need another messageblock with all padding
            *s=PAD1;
        }
    
    
    //if we get this far, then return 1 so function is called again
    return 1;
}
