#include<stdio.h>
#include<stdint.h>

//Convert big endian
union messageBlock{

uint8_t e[64];
uint32_t t[32];
uint64_t s[8];
};



enum status {READ, PAD0, PAD1, FINISH};




int main(int argc, char *argv[]){

    union messageBlock MsgBlk;
    uint16_t noBits = 0;
    uint64_t NoOfBytes;
    
    enum status s = READ;

    FILE* f;  

    
    //do some error checking (header file stdarg)
    f = fopen(argv[1], "r");

    int i;
    //check for error
    while(s == READ) {
        NoOfBytes = fread(MsgBlk.e, 1, 64, f);
        //printf(("Read %2llu bytes \n", NoOfBytes));
        noBits = noBits + (NoOfBytes * 8);
        if(NoOfBytes < 55 ){
            printf("I have found a block with less then 55 bytes");
            MsgBlk.e[NoOfBytes] = 0x01;
            while((NoOfBytes < 56)){
                NoOfBytes = NoOfBytes + 1;
                MsgBlk.e[NoOfBytes] = 0x00;
            }
           MsgBlk.s[7] = noBits; 
           s = FINISH;

        }else if(NoOfBytes < 64 ){
            s = PAD0;
            MsgBlk.e[NoOfBytes] = 0x80;
            while(NoOfBytes < 64){
                NoOfBytes = NoOfBytes + 1;
                MsgBlk.e[NoOfBytes] = 0x00;
            }
            //need to check if at nd of file(checks if file is exactly 512 bytes so no bits at end)
        }else if(feof(f)){
            printf("Perfect file");
            s=PAD1;
        }


        if(s == PAD0){
            for(i = 0; i < 56; i++){
                MsgBlk.e[i] = 0x00;
            }
            MsgBlk.s[7] = noBits;
        }
        if( s == PAD1)
            MsgBlk.e[0] = 0x80;
    
    }
    fclose(f);


    for(int i = 0; i < 64;i++)
        printf("%x", MsgBlk.e[i]);
    printf("\n");
    return 0;
}
