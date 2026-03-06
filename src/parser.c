#include <stdio.h>
#include "../include/packet.h"
#include <arpa/inet.h>

void parse_packet(const unsigned char *packet){

    struct ethernet_header *eth;

    eth = (struct ethernet_header *)packet;

    printf("Source MAC: %02X:%02X:%02X:%02X:%02X:%02X\n",
        eth->src_mac[0],
        eth->src_mac[1],
        eth->src_mac[2],
        eth->src_mac[3],
        eth->src_mac[4],
        eth->src_mac[5]);

}