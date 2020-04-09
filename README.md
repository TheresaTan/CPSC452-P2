# CPSC452-P2
Christopher Phongsa - cphongsa@csu.fullerton.edu



# Instructions for AES encryption/decryption:
- run 'make' in the terminal to compile all programs
- use the following command to run AES encryption: 
    ./cipher AES <KEY> <ENC/DEC> <INPUT FILE> <OUTPUT FILE>

------------------------PLEASE NOTE------------------------
- <KEY> must be 16 bytes (32-bits) long
-----------------------------------------------------------
- For example (these commands can be run sequentially):
    - AES encryption
        ./cipher AES "00112233445566778899aabbccddeeff" ENC in.txt enc.txt
    - AES decryption
        ./cipher AES "00112233445566778899aabbccddeeff" DEC enc.txt dec.txt
OR
    ./cipher AES "0123456789abcdef" ENC in.txt enc.txt
    ./cipher AES "0123456789abcdef" DEC enc.txt dec.txt
