# CPSC452-P2
Christopher Phongsa - cphongsa@csu.fullerton.edu



# Instructions for AES encryption/decryption:
- run 'make' in the terminal to compile all programs
- use the following command to run AES encryption: 
    ./cipher AES <KEY> <ENC/DEC> <INPUT FILE> <OUTPUT FILE>

########################PLEASE NOTE########################
    <KEY> must be 17 bytes (32-bits) long
    For encryption, the first byte must be 00
    For decryption, the first byte must be 11
###########################################################
For example (these commands can be run sequentially):
    - AES encryption
        ./cipher AES "0000112233445566778899aabbccddeeff" ENC in.txt out.txt
    - AES decryption
        ./cipher AES "1100112233445566778899aabbccddeeff" ENC out.txt in.txt

