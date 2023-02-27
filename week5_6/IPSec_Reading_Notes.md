# IPSec Reading Notes
Perez, Andre. Network Security, John Wiley & Sons, 17 November 2014.

## Implementation
- IPSec mechanisms are required to be implemented in IPv6 but are optional in
  IPv4. The use is optional for both (83)
- IPSec mechanisms can take place in the following environments:
  - Host to host on a WAN
  - Host to Security Gateway across an insecure WAN into a protected LAN
  - Host to host through secure LAN, out Security Gateway, through unprotected
    WAN, through Security Gateway, into secure LAN
- IPSec mechanism provides two headers to IP packets:
  - `Authentication Header (AH)` - Ensures integrity and authentication of IP
    packets
  - `Encapsulating Security Payload (ESP)` - Ensures integrity, authentication,
    and confidentiality of IP packets

### Authentication Header (AH)
- Provides protection from replay attacks,
