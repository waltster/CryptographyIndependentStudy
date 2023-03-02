# Reading Notes for _A Course in Number Theory and Cryptography_
Koblitz, Neal. _A Course in Number Theory and Cryptography_. Springer-Verlag,
1987.

## Chapter IV: "Public Key"
### Description and Requirements
- Cryptographic systems can be understood as a function `f(m)` transforming
  plaintext data `m` into ciphertext `c`. Conversely, the function `f'(c)` is a
  function that transforms the ciphertext `c` into plaintext `m`. Thus, it is
  necessary that the operations be opposites.
- Unlike other cryptosystems, public key cryptosystems rely on a function that
  is easy to compute in one direction, but difficult in the opposite. This
  allows for the distribution of a ciphertext and an enciphering key but makes it
  infeasible to compute the plaintext.
- Public key systems rely on the concept of _realistic computability_ which
  refers to the ability to compute within an amount of time where the data is
  applicable.
- As computational power increases through new algorithms or hardware, the
  notion of realistic computability changes, requiring redefinition of public
  key standards. This means that the security of a cryptosystem is a function of
  time and computational ability since processor power increases with time.
- There are no _true_ public key systems, since this would require the absolute
  nontrivial calculation of ciphertext with no ability to decipher the message.
  At best, current systems functionally operate as a public key system.
- Public key systems, in general, are described as: `E(m) = O(log B)` while
  `D(c)` is polynomial in `B`.

### Application
- Public key systems are ideal in an environment where the affiliation and
  identification may be shifting or where entities who have not previously
  exchanged information may be required to encipher it.
- Public key systems provide authentication and verification of the
  sender/receiver.
- Public key systems may be used as an auxillary to the main cryptosystem,
  allowing two non-connected parties to negotiate on a private key to use with a
  classical cryptosystem.

