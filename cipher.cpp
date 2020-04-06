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
    string line = "";
    const unsigned char *cipherText = NULL;
    const unsigned char *plainText = NULL;
    ifstream inputFile;
    ofstream outputFile;

    string cipherName = argv[1];
    key = (const unsigned char *)argv[2];
    string encOrDec = argv[3];
    string input = argv[4];
    string output = argv[5];



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

    inputFile.open(input);
    outputFile.open(output);
    if(inputFile.is_open()){
        while(getline(inputFile,line)){
            if(encOrDec == "ENC"){

                //cipherText = cipher->encrypt((const unsigned char*)line.c_str());
                cout << "STARTING ENCRYPTION \n";
                //encrypts up to 8 character string

                cipherText = cipher->encrypt((const unsigned char*)"helloworld");
                outputFile << cipherText;
            }else if(encOrDec == "DEC"){
                //plainText = cipher->decrypt((const unsigned char*)line.c_str());
                cout << "STARTING DECRYPTION \n";
                plainText = (const unsigned char*)"dodecryptlater";
                outputFile << plainText;
            }
        }
        inputFile.close();
        outputFile.close();
    }else cout << "Unable to open file";


    /* Perform encryption */
    //string cipherText = cipher->encrypt("hello world");

    /* Perform decryption */
    //cipher->decrypt(cipherText);

	return 0;
}
