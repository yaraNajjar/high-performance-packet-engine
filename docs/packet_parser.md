# Packet Parser Documentation

## 1. Overview
This parser extracts key information from network packets captured using `libpcap`.
It parses Ethernet, IP, and TCP/UDP headers and prints their details.

---

## 2. Structures

### Ethernet Header
```c
struct ethernet_header {
    uint8_t dest_mac[ETHER_ADDR_LEN];
    uint8_t src_mac[ETHER_ADDR_LEN];
    uint16_t ether_type;
};
```


dest_mac: Destination MAC address (6 bytes)

src_mac: Source MAC address (6 bytes)

ether_type: Type of payload (e.g., IP, ARP)

### IP Header
```c
struct ip_header {
    uint8_t version_ihl;        // Version + Internet Header Length
    uint8_t tos;                // Type of Service
    uint16_t total_length;      // Total length of IP packet
    uint16_t identification;    
    uint16_t flags_fragment;    
    uint8_t ttl;                // Time to live
    uint8_t protocol;           // Protocol (TCP/UDP/ICMP)
    uint16_t header_checksum;   
    uint32_t src_ip;            // Source IP address
    uint32_t dst_ip;            // Destination IP address
};
```

### TCP Header
```c
struct tcp_header {
    uint16_t src_port;          
    uint16_t dst_port;          
    uint32_t seq_number;        
    uint32_t ack_number;        
    uint16_t offset_reserved_flags;
    uint16_t window;            
    uint16_t checksum;          
    uint16_t urgent_pointer;    
};
```

## 3. Function: parse_packet()
```c
void parse_packet(const unsigned char *packet);
```

* Extracts and prints:

Source MAC and Destination MAC

Source IP and Destination IP

(Future: TCP/UDP ports and protocol)

* Input: pointer to the raw packet captured by libpcap.

* Usage Example:
```c
#include "packet.h"

void packet_handler(...) {
    ...
    parse_packet(packet);
}
```

## 4. Notes

* MAC addresses are 6 bytes.

* IP addresses are extracted using inet_ntoa from network byte order.

* Currently, the parser supports Ethernet + IPv4.

* TCP/UDP parsing will be added in the next stages.