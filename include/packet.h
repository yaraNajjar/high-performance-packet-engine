#ifndef PACKET_H
#define PACKET_H

#include <stdint.h>

#define ETHER_ADDR_LEN 6

struct ethernet_header {

    uint8_t dest_mac[ETHER_ADDR_LEN];

    uint8_t src_mac[ETHER_ADDR_LEN];

    uint16_t ether_type;

};

#endif