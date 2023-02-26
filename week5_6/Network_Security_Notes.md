# Reading Notes for SSL/TLS from _Network Security_ 
Perez, Andre. Network Security, John Wiley & Sons, 17 November 2014.

## SSL/TLS Notes
- SSL is the _Secure Sockets Layer_ protocol, which provides a secure session 
  between a host and a security gateway
    - SSL was originally created by Netscape in order to secure messages between
      a server and the "navigator"
- TLS is the _Transport Layer Security_ protocol which provides a way to secure
  messages on the application level.
    - TLS was created as a standard by the Internet Engineering Task Force,
      superceding the SSL protocol
- Both SSL and TLS are alternative solutions for Internet Protocol Security
  mechanisms, but can also apply outside of IP domain and be used in general
  application-level communication. 
- Both SSL and TLS operate by inserting a _Record_ header "between the transport
  layer and the messages of the application layer, or following SSL/TLS
  messages" (pp. 110)

## Requirements/Characteristics
- SSL/TLS require TCP communication since it is reliable and enables the
  retransmission in case of error
    - Can be implemented using datagrams but requires large overhead and many
      modifications
- SSL/TLS protocols delimit messages and determine the length of messages,
  allowing multiple SSL/TLS messages in a single TCP segment
- Encapsulation of messages in the application layer is done via a _Record_
  header, providing encryption, authentication, and nonrepudiation.

## Types of Messages
- `alert` - Alerts the other side of an important state change or the neccessity
  to terminate the connection
    - Allows for notification, error conditions, and retransmission
    - Two levels: level 1 is a minor note and level 2 is a termination level
      alert
- `application` - Messages encapulated by SSL/TLS but pertaining to the
  application itself and not SSL/TLS
- `change_cipher_spec` - Provides a new key and algorithms to use for encrypting
  traffic. Allows each side to modify the existing relationship 
- `handshake` - Allows for two parties to establish a connection and determine
  the means for encrypting/compressing traffic

## Handshake Process
