#include "AES.h"
#include <iostream>

/**
 * Sets the key to use
 * @param key - the first byte of this represents whether
 * to encrypt or to decrypt. 00 means encrypt and any other
 * value to decrypt.  Then come the bytes of the 128-bit key
 * (should be 16 of them).
 * @return - True if the key is valid and False otherwise
 */
bool AES::setKey(const unsigned char* keyArray)
{
	
	// TODO: AES implementation of openssl cares about whether
	// you are encrypting or decrypting when setting the key.
	// That is, when encrypting you use function AES_set_encrypt_key(...)
	// and when decrypting AES_set_decrypt_key(...).
	//
	// One way to solve this problem is to pass in a 17 byte key, where
	// the first byte is used to indicate whether we are encrypting or
	// decrypting. E.g., if the first byte is 0, then use AES_set_encrypt_key(...).
	// Otherwise, use AES_set_decrypt_key(...).  The rest of the bytes in the
	// array indicate the 16 bytes of the 128-bit AES key.
	//
	// Both functions return 0 on success and other values on faliure.
	// For documentation, please see https://boringssl.googlesource.com/boringssl/+/2623/include/openssl/aes.h
	// and aes.cpp example provided with the assignment.

	// if the first byte is 0, we will set an encryption key
	if(keyArray[0] == '0') {
		if(AES_set_encrypt_key(keyArray+1, 128, &AES_KEY) != 0){
			fprintf(stderr, "Could not successfully encrypt the AES key.\n");
			exit(-1);
		}
		fprintf(stderr, "Set the key for encryption\n");
		return 0;
	} else {
		// if first byte is any other value than 0, we will set a decryption key
		if(AES_set_decrypt_key(keyArray+1, 128, &AES_KEY)!=0) {
			fprintf(stderr, "Could not succesfully set the decryption key.\n");
			exit(-1);
		}
		fprintf(stderr, "Set the key for decryption\n");
		return 0;
	}
}

/**	
 * Encrypts a plaintext string
 * @param plaintext - the plaintext string
 * @return - the encrypted ciphertext string
 */
unsigned char* AES::encrypt(const unsigned char* plainText)
{
	
	//TODO: 1. Dynamically allocate a block to store the ciphertext.
	//	2. Use AES_ecb_encrypt(...) to encrypt the text (please see the URL in setKey(...)
	//	and the aes.cpp example provided.
	// 	3. Return the pointer to the ciphertext

	unsigned char* tempCipher;
	tempCipher = new unsigned char[AES_BLOCK_SIZE];
	
	// Clear the ciphertext block
	memset(tempCipher, 0, AES_BLOCK_SIZE);

	AES_ecb_encrypt(plainText, tempCipher, &AES_KEY, AES_ENCRYPT);
	
	//printf("%c\n", tempCipher[0]);
	return tempCipher;
	
}

/**
 * Decrypts a string of ciphertext
 * @param cipherText - the ciphertext
 * @return - the plaintext
 */
unsigned char* AES::decrypt(const unsigned char* cipherText)
{
	
	//TODO: 1. Dynamically allocate a block to store the plaintext.
	//	2. Use AES_ecb_encrypt(...) to decrypt the text (please see the URL in setKey(...)
	//	and the aes.cpp example provided.
	// 	3. Return the pointer to the plaintext

	unsigned char* tempPlain;
	tempPlain = new unsigned char[AES_BLOCK_SIZE];

	// clear the plaintext block
	memset(tempPlain, 0, AES_BLOCK_SIZE);

	AES_ecb_encrypt(cipherText, tempPlain, &AES_KEY, AES_DECRYPT);
		
	return tempPlain;
}



