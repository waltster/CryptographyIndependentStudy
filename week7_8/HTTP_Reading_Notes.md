# _HTTP: The Definitive Guide_ Reading Notes
Gourley, David, et al. _HTTP: The Definitive Guide_, O'Reilly, 2002.

## Chapter 14: Secure HTTP
- HTTP requires the following in order to be secure:
  - Server authentication
  - Client authentication
  - Integrity of messages
  - Encryption
  - Efficiency
  - Ubiquity
- SSL/TLS provides the ability for HTTP to be secure, encapsulating traffic in
  the SSL/TLS body.
  ```
  | HTTP
    | SSL/TLS
      | TCP
        | IP
          | Network Interface
  ```
- The RSA algorithm provides a way to ensure that: "given a public key, an
  arbitrary piece of plaintext, the associated ciphertext from encoding the
  plaintext with the public key, the RSA algorithm itself, and even the source
  code of the RSA implementation, cracking the code to find the corresponding 
  private key is believed to be one of hte hardest problems in all of computer
  science" (317).
- HTTPS traffic arrives on port `443` since port `80` would likely refuse/reject
  the traffic since it appears as meaningless binary information
- SSL handshaking takes the following steps:
  1. Exchange protocol version numbers
  2. Select a cipher that each side knows
  3. Authenticate the identity of each side
  4. Generate temporary session keys to encrypt the channel
- Clients may have certificates and use this with the server, but many do not.
  If they do, the server can demand this, providing authentication of the user.
  Some organizations (such as the government) use this to control employee 
  access to information.
- Site Certificate Validation:
  1. Date Check: Verify that the certificate is valid on the front and back end
  2. Signer Trust Check: Verifies that the Certificate Authority is trusted
  3. Signature Check: Verifies that the certificate's integrity is valid by
     calculating the digest as well.
  4. Site Identity Check: Verifies that the site identity matches the site on
     the certificate.
