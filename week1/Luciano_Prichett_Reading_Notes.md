# Reading Notes for _Cryptology: From Caesar Ciphers to Public-Key
Cryptosystems_

Luciano, Dennis, and Gordon Prichett. "Cryptology: From Caesar Ciphers to 
Public-Key Cryptosystems.” The College Mathematics Journal, vol. 18, no. 1, 
1987, pp. 2–17. JSTOR, https://doi.org/10.2307/2686311. Accessed 12 Feb. 2023.

## Types of Ciphers
- __Linear Cipher:__ Moving characters according to a value as if it were linear
- __Decimation Cipher:__ Uses multiplication rather than addition as the key, but
functionally similar to a linear cipher.
    - Requires a relative prime to 26 as the key
    - Subset of a linear cipher
- Linear ciphers can be generally defined as: `E(m) = (kM + t) mod 26` where `k`
  and `t` are integers and `k` is relatively prime to 26.
- __Substitution Cipher:__ is a cipher where letters may be substituted out of
  a specific order and substituted with each-other , increasing the search 
  space to `26!`
    - All properties of the language are inherited by the substitution, since
      each letter always is used the same substituted way. Any kind of
      statistical distribution in the usage of the letter is preserved.
- __Polyalphabetic Cipher:__ Relies on using multiple alphabets with a cipher
  using a keyword. For example, the first `n` letters are using alphabet `a` and
  the next `m` letters are using alphabet `b`.
    - The keyspace is defined as `(26!)^2` where `n` is the number of letters
      and alphabet pairs.
    - This helps to avoid doubling of letters, statistical distribution, and
      natural language patterns.

## One-Time Pad
- Provides a perfectly secure encryption by introducing equal probability of
  _any_ solution being used without any deterministic pattern.
- Works by:
    1. Translate message characters into their index in the alphabet (`M`)
    2. Translate key characters into their index in the alphabet (`K`)
    3. `C(i) = (M(i) + K(i)) mod 26`, yeilding a ciphertext.
    4. Recipient takes the key and performs the opposite operation but with the
       same key: `D(i) = (C(i) - K(i)) mod 26`
- Suffers from severe issues:
    - With high overhead, since the key length must equal the amount of data 
      being sent
    - The data is easily malleable since there is no authentication that the
      message has not meen tampered with, and the ability to flip bits
      individually will weaken the strength of the encryption
    - Relies on specialized true random number generating hardware
    - No authentication of the sender or receiver is possible excpe that they
      possess the key, making impersonation trivial.

## Public-Key Cryptosystems
- Proposed in 1975 by Whitfield Diffie and Martin Hellman
- Relies on computational complexity and an analysis of how long it would take
  to break the cipher
- Relies on a "trap door" function, where given `M` it is trivial to compute
  `E(M)` but given `E(M)` it is effectively impossible to compute `M`.
- Computation complexity theory describes a "hard" problem as "no such algorithm
  to solve the problem in `kd^a` where `k` and `a` are constants and `d` is the
  size of the input.
- Solves statistical distribution, authentication, and repudiation problems of
  One-Time Pads.

### RSA
- RSA is an implementation of a public-key cryptosystem, posessing the function
  necessary to have the "trap door" implemented
- Implements a trap door through factorization of a number using two large
  primes.
- Depends on Ellis's idea of locking and unlocking being inverse operations and
  the encryption and decryption being synonymous but opposite.
- __Modular Exponentiation:__ Raise a number `a` to the power `b`, divide by `c`
  and output the remainder. `(a ^ b) mod c`
    - `M^e mod N = C`, where `M` is the message, `e` is the public exponent, and
      `N` is a random number.
    - `C^d mod N = M`, where `C` is the ciphertext, `d` is the secret key, `N`
      is the random number
    - `M^(e^d) mod N = M` is the full encryption followed by decryption
- Relies on the difficulty and trial-and-error required in order to factor until
  prime numbers. This grows exponentially, making it ideal for this setting.
- Full example:
    - `Φ(n)`, all numbers that do not share factors with `n` less than `n` 
        - Posesses the property of `Φ(A) * Φ(B) = Φ(A*B)`
    - `p1`, large prime, more than one-hundred digits long
    - `p2`, large prime, more than one-hundred digits long
    - The `Φ(n)` is `n-1` for any prime, since all numbers less than it are
      included as ones that do not share factors.
    - Euler's theorem: `M^(Φ(n)) = 1 mod n`
    - Since `1^k = 1`, then it is safe to multiply `Φ(n)` by `k`, thus
      `m^(k*Φ(n) + 1) = m mod n`, thus `m^(e * d) = m mod n` and `e * d = k *
      Φ(n) + 1`
    - `d = ((k * Φ(n) + 1) / e)`
