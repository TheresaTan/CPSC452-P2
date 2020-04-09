#include <string>
#include "CipherInterface.h"
#include "DES.h"
#include "AES.h"
#include <iostream>
#include <fstream>

using namespace std;

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
    const unsigned char *cipherText = NULL;
    const unsigned char *plainText = NULL;
    //ifstream inputFile;
   // ofstream outputFile;
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
        cipher->setKey(key);
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
    long end;
    size_t result;
    unsigned char * buffer;
    if(inputFile!=NULL) {
        //while(!inputFile.eof()){
        while(!feof(inputFile)) {
            //getting the 8 or 16 character string
            if(cipherName == "DES"){
                end = 8;
            }else if(cipherName == "AES"){
                end = 16;
            }
            buffer = new unsigned char[end];

            result = fread(buffer, 1, end, inputFile);
            if(result != end && result != 0 && encOrDec != "DEC"){
                for(long int i = result; i < end; i++){
                    buffer[i] = '0';
                }
            }
            cout << "LINE CHUNK: " << buffer << endl;
            if(encOrDec == "ENC"){
                cipherText = cipher->encrypt((const unsigned char*)buffer);
                cout << "STARTING ENCRYPTION \n";
                //encrypts up to 8 character string
                //cipherText = cipher->encrypt((const unsigned char*)"helloworld");
                fwrite(cipherText, sizeof(char), end, outputFile);
            }else if(encOrDec == "DEC"){
                plainText = cipher->decrypt((const unsigned char*)buffer);
                cout << "STARTING DECRYPTION \n";
                //plainText = (const unsigned char*)"dodecryptlater";
                fwrite(plainText, sizeof(char), end, outputFile);

            }
        }
        fclose(inputFile);
        fclose(outputFile);
        free(buffer);

    }else cout << "Unable to open file";


    /* Perform encryption */
    //string cipherText = cipher->encrypt("hello world");

    /* Perform decryption */
    //cipher->decrypt(cipherText);
    cout << "Done.\n";

	return 0;
}
