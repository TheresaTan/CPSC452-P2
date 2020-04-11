#include "AES.h"
#include <iostream>
#include <cstring>

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

	int aesKeyIndex = 1;
	int keyIndex = 1;
	unsigned char temp[17];
	memset(temp, 0, 17);
	
	int hexKeyIndex = 0;
	
	// A single byte in the key
	char byte = 0;

	// Convert the string key into a hex
	for(int keyIndex = 1; keyIndex < 33; keyIndex += 2)
	{
		// Convert two bytes representing the hex digits into one
		// byte with two digits corresponding to the digits in the string
		byte = twoCharToHexByte(keyArray + keyIndex);
		
		// Something went wrong
		if(byte == 'z')
		{
			fprintf(stderr, "Invalid character in the key");
			break;
		}
		
		temp[hexKeyIndex] = byte;

		++hexKeyIndex;


	}
	
	// if the first byte is 0, we will set an encryption key
	if(keyArray[0] == '0') {
		if(AES_set_encrypt_key(temp, 128, &AES_KEY) != 0){
			fprintf(stderr, "Could not successfully encrypt the AES key.\n");
			exit(-1);
		}
		fprintf(stderr, "Set the key for encryption\n");
		return 0;
	} else {
		// if first byte is any other value than 0, we will set a decryption key
		if(AES_set_decrypt_key(temp, 128, &AES_KEY)!=0) {
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

/**
 * Converts a character into a hexidecimal integer
 * @param character - the character to convert
 * @return - the converted character, or 'z' on error
 */
unsigned char AES::charToHex(const char& character)
{
	/* Is the first digit 0-9 ? */	
	if(character >= '0' && character <= '9')	
		/* Convert the character to hex */
		return character - '0';
	/* It the first digit a letter 'a' - 'f'? */
	else if(character >= 'a' && character <= 'f')
		/* Conver the cgaracter to hex */
		return (character - 97) + 10;	
	/* Invalid character */
	else return 'z';
}

/**
 * Converts two characters into a hex integers
 * and then inserts the integers into the higher
 * and lower bits of the byte
 * @param twoChars - two charcters representing the
 * the hexidecimal nibbles of the byte.
 * @param twoChars - the two characters
 * @return - the byte containing having the
 * valud of two characters e.g. string "ab"
 * becomes hexidecimal integer 0xab.
 */
unsigned char AES::twoCharToHexByte(const unsigned char* twoChars)
{
	/* The byte */
	unsigned char singleByte;
	
	/* The second character */
	unsigned char secondChar;

	/* Convert the first character */
	if((singleByte = charToHex(twoChars[0])) == 'z') 
	{
		/* Invalid digit */
		return 'z';
	}
	
	/* Move the newly inserted nibble from the
	 * lower to upper nibble.
	 */
	singleByte = (singleByte << 4);
	
	/* Conver the second character */
	if((secondChar = charToHex(twoChars[1])) == 'z')
		return 'z'; 
	
	/* Insert the second value into the lower nibble */	
	singleByte |= secondChar;

	return singleByte;
}
