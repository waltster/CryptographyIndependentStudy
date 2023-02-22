# AES Notes

## Galois Field
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

## Operations
Since AES uses matrix operations, addition and multiplication for the fielf
`GF(2^8)` must be defined. The
[specification](https://csrc.nist.gov/csrc/media/projects/cryptographic-standards-and-guidelines/documents/aes-development/rijndael-ammended.pdf)
defines these and provides the following ways to operate on a number in the
field with order `8`.

### Addition
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

### Multiplication
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
