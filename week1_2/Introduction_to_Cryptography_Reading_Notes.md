# Reading Notes for _PGP 7.0: An Introduction to Cryptography_
I found this book to be a great resource for an introduction into the field of
cryptography and the basic principles, history, and primitive functions. I
enjoyed the way that the book was written as an approachable resource, without
too much theory. While the text focused on PGP, I think that its discussion of
cryptographic primitives and the essential functions of a public-key
cryptosystems was helpful in understanding any.

## Transmission Steps
- PGP first compresses plaintext to reduce any patterns in the data that would
  be easy to analyze
- PGP then generates a random session key and encrypts the data using this
- PGP encrypts the session key using the public key provided and attaches this
  to the message
- PGP then transmits both the message and the encrypted key

## Public/Private Keys
- Key size relates to the number of bits in a key
- Key size between asymmetric and symmetric cryptography is incomparable, since
  asymmetric cryptographic keys tend to have metadata attached and contain more
  information in the key itself
- Keys are mathematically related and can be computed with enough time, making
  cracking encryption a function of key length and computational power

## Digital Signatures
- Basic equation: `Message = Plaintext +
  Private_Key_Encryption(Hash(Plaintext))`
- Digital signatures allow someone to verify that the content of a message and
  only that content was sent by the signer, due to the digest being encrypted
    - Weakness: a collidable hash function may allow someone to generate a digest
      equal but with different data, compromising the validity of the signature

## Digital Certificates
- Form the basis of trust in an environment when you cannot verify who is
  sending a key, such as a remote connection
- Helps to avoid man-in-the-middle-attack by establishing trust that the
  identity of the sender is trusted and private
- Consists of:
  1. A public key
  2. Certificate information (identity information, issuance metadata, et c.)
  3. One or more digital signatures providing authority
- Allows a public key to have an identification and signature of a trusted third
  party.

## Certificate Distribution
- __Directory Server:__ A server that allows users to submit and retrieve
  digital certificates.
- Public Key Infrastructure (PKI) provides some of these same services:
  issuance, revokation, and trust verification.
    - __Certificate Authority:__ Creates Certificates and signs them
    - __Registration Authority:__ The human processes and people operating a CA.
- Two main formats for certificates: PGP and X.509
    - People can make their own PGP, but they must request X.509 from an
      authority
    - Issuers may take steps to actually verify ownership of identity
- Validation of certificates and keys as a whole can be done via fingerprints,
  which are essentially digests
- Revokation happens through publishing the revokation key, or through a
  certificate revokation list which acts as a centralized fail point.

> Once a communication infrastructure optimized for surveillance becomes
> entrenched, a shift in political conditions may lead to abuse of this
> new-formed power. Political conditions may shift with the election of a new
> government, or perhaps more abruptly from the bombing of a federal building"
> 
> If privacy is outlawed, only outlaws will have privacy
>
> (pp. 34, "PGP 7.0: An Introduction to Cryptography")

## Phil Zimmermann's Essay 
- In order to supply a public that was growing aware of its ability to use
  cryptography, the government created the innovation of the "Clipper chip"
  which relied on key-escrow to maintain a copy of the encryption key for the
  government.
- In response to increaing usage of cryptography, the Clinton administration
  threw out most of their export control restrictions that were placed on the
  cryptography software and algorithms.
- Certificate authorities make-up the gaps and differences when public-keys
  cannot be trusted off of the bat.
- The relationship between people's trusting of a key and trusting the person
  with the key is divided by Zimmermann. He emphasizes that just because you
  trust the key and its signatories does not mean that the person's content is
  true
