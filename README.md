# SHA256

This repository holds contains all my impplementation of the SHA256 algorithm written in C. The aim being to take a file containing a certain amount of bytes and convert it to the correct Hash. 

## SHA256.c
The SHA256 algorithm is a set of cryptography hash functions which were created by the NSA, with the aim of creating hashes which could not feasibly be deconstructed. 
In order to complete this project I followed the videos provided by Ian mcgloughlin in order to learn about the sha256 Algorithm and how to implement it in C. After the videos it was indicated that the results were being written in little Endian, however Sha256 directly states that the results must be written in big endian so this was one of the first things I aimed to change in the implementation provided. 


## Setup
In order to run this file the first thing you will need is a GCCC compiler. it can be downloaded from [here](http://www.codebind.com/cprogramming/install-mingw-windows-10-gcc/)\\
Next you will need to clone this repo to your local machine.\\
Once the file has been cloned, you must navigate to where the file has been dowloaded and run the following command:\\
gcc -o sha256 sha256.c\\

This will compile your file, next you will need to run \\
./sha256 followed by the file which you want to hash.


## Additional features
I have provided all of the additional features mentioned in the videos, including creating macros using the #define method in order to create the EP0, EP1, CH and MAJ files. 
Next I created a macro which would convert the bytes from big endian to little endian within the Sha256 algorithm. This worked when I tested it with the empty file, however after adding additional characters to the file the tests began to fale. This was due to the padding nextMsgBlk not converting from little endian to big endian, after this the algorithm worked with files over 0 bytes. 
I then decided to add a check for the endianess of a machine so it would be only converted if the machine was in little endian.
Finally I decided to use malloc to create a pointer to the array H[8]. This helped with memory management as instead of printing the results to the main method, I provided a pointer which would return the value instead.


## Testing
In order to test my implementation of the sha256 algorithm, I needed to creates files with the specified amount of bytes. So I have created an emptyFile and abc.txt, these are provided in the tests folder in order to test my implementation of the sha256 standard.

## Correct hashes
 emptyFile   = e3b0c442 98fc1c14 9afbf4c8 996fb924 27ae41e4 649b934c a495991b 7852b855
 abc = ba7816bf 8f01cfea 414140de 5dae2223 b00361a3 96177a9c b410ff61 f20015ad
 
## Research
[Sha256 standard](https://nvlpubs.nist.gov/nistpubs/FIPS/NIST.FIPS.180-4.pdf)
[little to big endian](https://stackoverflow.com/questions/19275955/convert-little-endian-to-big-endian)
[Dynamic memory allocation](https://www.programiz.com/c-programming/c-dynamic-memory-allocation)
## Authors

* **James kennedy** 




