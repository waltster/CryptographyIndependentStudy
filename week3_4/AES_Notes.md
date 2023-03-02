# AES Notes
# Notes about AES
## Purpose
AES was created as a stronger replacement for the DES, which became obsolete and
easily broken as computing power increased. While a viable alternative for DES 
came about, triple DES, it was not widely adopted and the government created AES
as a replacement. 

## History
AES was developed by Belgian cryptographers Joan Daemen and Vincent Rijmen and
submitted it to NIST for their review as part of the Advanced Encryption
Standard selection process. Rijndael was proposed as a collection of ciphers
with different key and block sizes, allowing for increased security and fewer
operations. AES was selected in part because of its ability to perform well on various
hardware, including running on smart cards within a reasonable amount of time.

## Application/Use
AES is a symmetic algorithm, meaning that it requires, and only functions, to
encrypt and decrypt with the same key both directions. Additionally, the
operations are inverse with the same key. 

AES is secure and acceptable for use across industries and is the only
cryptographic algorithm approved by the United State's National Security Agency
for the transmission/encryption of Top Secret Information
[ref](https://web.archive.org/web/20101106122007/http://csrc.nist.gov/groups/ST/toolkit/documents/aes/CNSS15FS.pdf).

AES can be implemented in any language that supports manipulation of binary
numbers and is provided in a wide array of open-source libraries and packages,
including the Linux kernel's Crypto API. At the disk level, AES is widely used
as part of macOS's FireVault program, IBM encryption, and most encrypted
file systems, including NTFS.

Since the release of `IEEE 802.11i-2004`, AES is used as the default block
cipher to supercede WEP and WPA's use of the RC4 stream cipher.

## Theory
### Galois Field
For AES, the Galois field is defined as a `GF(2^8)`, where the coefficients of a
polynomial are with in the set `{0, 1}`. This makes the field especially easy to
implement for digital computers.

Numbers in the field are represented in the following way, for byte `b`:
```
b = b7*x^7 + b6*x^6 + b5*x^5 + b4*x^4 + b3*x^3 + b2*x^2 + b1*x + b0
```

For example, the byte `0x55` (binary: `01010101`) is represented as the
polynomial:
```
b = 0*x^7 + 1*x^6 + 0*x^5 + 1*x^4 + 0*x^3 + 1*x^2 + 0*x + 1
b = x^6 + x^4 + x^2 + 1
```

### Operations
Since AES uses matrix operations, addition and multiplication for the fielf
`GF(2^8)` must be defined. The
[specification](https://csrc.nist.gov/csrc/media/projects/cryptographic-standards-and-guidelines/documents/aes-development/rijndael-ammended.pdf)
defines these and provides the following ways to operate on a number in the
field with order `8`.

#### Addition
Addition is defined as the result of polynomial addition with the coefficients
modified by modulo two (effectively XOR).

For example, `0x55 + 0x3A` (binary: `01010101` and `00111010`):
```
b1        = 0*x^7 + 1*x^6 + 0*x^5 + 1*x^4 + 0*x^3 + 1*x^2 + 0*x + 1
b2        = 0*x^7 + 0*x^6 + 1*x^5 + 1*x^4 + 1*x^3 + 0*x^2 + 1*x + 0
-------------------------------------------------------------------
sum       = 0*x^7 + 1*x^6 + 1*x^5 + 2*x^4 + 1*x^3 + 1*x^2 + 1*x + 1
-------------------------------------------------------------------
sum mod 2 = 0*x^7 + 1*x^6 + 1*x^5 + 0*x^4 + 1*x^3 + 1*x^2 + 1*x + 1
sum mod 2 = x^6 + x^5 + x^3 + x^2 + x + 1
sum mod 2 = 001101111
```

#### Multiplication
Multiplication is defined as a two-step process:
1. Multiplication of coefficients of polynomials (may result in a value larger
   than a byte)
2. Reduction by XOR `m(x)` (`m(x) = x^8 + x^4 + x^3 + x^1 + 1`) repeatedly until 
   the multiplication is within a byte (ensured by `m(x)`)

For example, `0x55 * 0x3A` (binary: `01010101` and `00111010`):
```
b1          = x^6 + x^4 + x^2 + 1
b2          = x^5 + x^4 + x^3 + x
---------------------------------------------------------------------------
b1*b2       = (x^6 + x^4 + x^2 + 1) * (x^5 + x^4 + x^3 + x)
b1*b2       = (x^11 + x^10 + x^9 + x^7) + (x^9 + x^8 + x^7 + x^5) + 
              (x^7 + x^6 + x^5 + x^3) + (x^5 + x^4 + x^3 + x)
b1*b2       = x^11 + x^10 + 2x^9 + x^8 + 3x^7 + x^6 + 3x^5 + x^4 + 2x^3 + x
---------------------------------------------------------------------------
b1*b2 mod 2 = x^11 + x^10 + x^8 + x^7 + x^6 + x^5 + x^4 + x
b1*b2 mod 2 = 110111110010 = D
---------------------------------------------------------------------------
D XOR m(x)  = 110111110010      Note that m(x) is shifted as far left as 
          xor 100011011         possible
D XOR m(x)  = 010100101010
          xor  100011011
D XOR m(x)  =  00101000110
          xor    100011011
D XOR m(x)  =    001011101
---------------------------------------------------------------------------
b1*b2       = 01011101
```

### Stages of AES Encryption
1. __Add Round Key:__ Take a matrix (4x4) of data, and XOR this with a matrix
   (4x4) of the key
2. __Substitute Bytes:__ Substitute bytes from each cell fo the resulting matrix
   with the substitution box generated. The leftmost four bits are mapped to the
   row value, and the rightmost four values are used as the column value.
   * Note: This substitution box is a constant
3. __Shift-Rows:__ Shift the row items to the left, wrapping around, `n` number
   of places, where `n` is the index of the row in the matrix beginning at `0`
4. __Mix Columns:__ Replace each byte of a column by the result of multiplying
   in the Galois field by the matrix below. This can be implemented using a
   lookup table rather than performing the operation each time.
```
[2 3 1 1
 1 2 3 1
 1 1 2 3
 3 1 1 2]
```
5. __Add Round Key:__ XOR the state array and the respective round key. This is
   passed to the next stage as input, or outputed as ciphertext if this is the
   final round.

## Sample Implementations
* [tiny-AES-c](https://github.com/kokke/tiny-AES-c) - Incredibly slim
  implementation of AES in C for use in embedded systems.
