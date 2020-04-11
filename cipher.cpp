#include <string>
#include "CipherInterface.h"
#include "DES.h"
#include "AES.h"
#include <iostream>
#include <fstream>
#include <cstring>
#include <sys/stat.h>
#include <string>

using namespace std;

// function to get the size of the file
size_t getFilesize(FILE* filename) {
    struct stat st;
    int fp = fileno(filename);
    if(fstat(fp, &st) != 0) {
        return 0;
    }
    return st.st_size;   
}

int main(int argc, char** argv)
{
	/**
	 * TODO: Replace the code below	with your code which can SWITCH
	 * between DES and AES and encrypt files. DO NOT FORGET TO PAD
	 * THE LAST BLOCK IF NECESSARY.
	 *
	 * NOTE: due to the incomplete skeleton, the code may crash or
	 * misbehave.
	 */
    /* Create an instance of the DES cipher */
    CipherInterface* cipher = NULL;
    const unsigned char *key = NULL;
    unsigned char key2[33];
    const unsigned char *cipherText = NULL;
    const unsigned char *plainText = NULL;

    FILE * inputFile;
    FILE * outputFile;
    string cipherName = argv[1];
    key = (const unsigned char *)argv[2];
    string encOrDec = argv[3];
    char * input = argv[4];
    char * output = argv[5];


    /* Set the encryption key
     * A valid key comprises 16 hexidecimal
     * characters. Below is one example.
     * Your program should take input from
     * command line.
     */
    //cipher->setKey((unsigned char*)"0123456789abcdef");
    if(cipherName == "DES"){
        cipher = new DES();
        cout << "DES IS PICKED, SETTING KEY NOW" << endl;
        cipher->setKey(key);

    }else if(cipherName == "AES"){
        cipher = new AES();
        cout << "AES IS PICKED, SETTING KEY NOW" << endl;
            strncpy((char*)key2+1, (const char*)key, 33);
    }else cipher = NULL;

    /* Error checks */
    if(!cipher)
    {
        fprintf(stderr, "ERROR [%s %s %d]: could not allocate memory\n",
                __FILE__, __FUNCTION__, __LINE__);
        exit(-1);
    }

    inputFile = fopen(input, "rb");
    outputFile = fopen(output, "wb");

    // Check to see if files opened correctly AKA sanity checks
    if(!inputFile) {
        perror("fopen");
        exit(-1);
    }
    if(!outputFile) {
        perror("fopen");
        exit(-1);
    }
    size_t fsize = getFilesize(inputFile);

    // number of blocks counter
    size_t counter = 1;

    // size of each block
    long end;
    size_t result;

    if(inputFile!=NULL) {
        //getting the 8 or 16 character string
        if(cipherName == "DES"){
            end = 8;
        }else if(cipherName == "AES"){
            end = 16;
            if(encOrDec == "ENC") {
                key2[0] = '0';
            } else {
                key2[0] = '1';
            }
            cipher->setKey(key2);
        }
    // get the number of blocks to use
    size_t numBlocks = fsize/end;

    // Count the partial block if necessary
    if(fsize % end > 0)
	    ++numBlocks;

    // get the number of padding to use
    size_t padding = end - (fsize%end);

    // temporary char array to store the second to last block of the plaintext
    const unsigned char *tempPlainText;
    tempPlainText = new unsigned char[fsize];

    // buffer to store input from inputFile
    unsigned char buffer[end+1];

        while(!feof(inputFile)) {
            memset(buffer, 0, end+1);
            result = fread(buffer, 1, end, inputFile);

            // if 0, then we have reached the end of the file
            if(result != 0) {
                if(result != end && encOrDec != "DEC"){
                    // add padding if necessary to complete the length of the block size
                    for(long int i = result; i < end; i++){
                        buffer[i] = '0';
                    }
                }
                cout << "LINE CHUNK: " << buffer << endl;
                if(encOrDec == "ENC"){
                    cipherText = cipher->encrypt((const unsigned char*)buffer);
                    cout << "STARTING ENCRYPTION \n";
                    //encrypts up to 8 character string
                    fwrite(cipherText, sizeof(char), end, outputFile);
                    if (counter == numBlocks){

                        // clear buffer so that we can concatenate a block that includes the number of padding
                        memset(buffer,0,end+1);
                        for(long int i = 0; i < end; i++){
                            if(i==end-1){
                                // store the padding in the last index.
                                buffer[i] = padding;
                            } else {
                                buffer[i] = '0';
                            }
                        }
                        cipherText = cipher->encrypt((const unsigned char*)buffer);
                        fwrite(cipherText, sizeof(char), end, outputFile);
                    }
                    delete[] cipherText;
                }else if(encOrDec == "DEC"){
                    plainText = cipher->decrypt((const unsigned char*)buffer);
                    cout << "STARTING DECRYPTION \n";
                    if (counter == numBlocks-1){
                        // store the second to last block into the temporary char array
                        strcat((char*)tempPlainText, (char*)plainText);
                    }else if(counter==numBlocks){
                        // grab the number of padding to remove
                        int rmPadding = plainText[end-1];
                        // concatenate the last block to the temporary char array
                        strcat((char*)tempPlainText, (char*)plainText);

                        // write to the file, while removing padding
                        fwrite(tempPlainText, sizeof(char), end-rmPadding, outputFile);
                        delete[] tempPlainText;
                    }else if(counter!=numBlocks){
                        fwrite(plainText, sizeof(char), end, outputFile);
                    } 
                    delete[] plainText;
                }
                counter++;
            }
        }
        
        // close the files
        fclose(inputFile);
        fclose(outputFile);

    }else cout << "Unable to open file";

    cout << "Done.\n";

	return 0;
}
