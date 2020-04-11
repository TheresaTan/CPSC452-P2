# CPSC452-P2
# Team Members:
Christopher Phongsa - cphongsa@csu.fullerton.edu

Marianne Tolentino - mariannetolentino@csu.fullerton.edu

Julian Coronado - juliancoronado@csu.fullerton.edu

Andrew Lopez - alopez8969@csu.fullerton.edu

Theresa Tanubrata - theresatanubrata123@csu.fullerton.edu

# Programming Language:
C++

# How to Execute Your Program:
- run 'make' in the terminal to compile all programs
# Instructions for DES encryption/decryption:
- use the following command to run DES encryption:
    ./cipher DES <KEY> <ENC/DEC> <INPUT FILE> <OUTPUT FILE>
  - For example (these commands can be run sequentially):
      - DES encryption:
          ./cipher DES "0123456789abcdef" ENC in.txt enc.txt
      - DES decryption
          ./cipher DES "0123456789abcdef" DEC enc.txt dec.txt
  
# Instructions for AES encryption/decryption:

- use the following command to run AES encryption: 
    ./cipher AES <KEY> <ENC/DEC> <INPUT FILE> <OUTPUT FILE>

------------------------PLEASE NOTE------------------------
- <KEY> input must be 32 bytes long
-----------------------------------------------------------
- For example (these commands can be run sequentially):
    - AES encryption
        ./cipher AES "00112233445566778899aabbccddeeff" ENC in.txt enc.txt
    - AES decryption
        ./cipher AES "00112233445566778899aabbccddeeff" DEC enc.txt dec.txt
  
# We did not implement the extra credit
