#include <stdio.h>
#include <stdint.h>
#include <arpa/inet.h>
#include "../include/packet.h"

/* -------- Protocol Parsers -------- */

void parse_tcp(const unsigned char *transport) {

    struct tcp_header *tcp = (struct tcp_header *)transport;

    printf("Protocol: TCP\n");
    printf("Source Port: %d\n", ntohs(tcp->src_port));
    printf("Destination Port: %d\n", ntohs(tcp->dst_port));
    printf("Sequence Number: %u\n", ntohl(tcp->seq_number));
}

void parse_udp(const unsigned char *transport) {

    struct udp_header *udp = (struct udp_header *)transport;

    printf("Protocol: UDP\n");
    printf("Source Port: %d\n", ntohs(udp->src_port));
    printf("Destination Port: %d\n", ntohs(udp->dst_port));
}

void parse_icmp(const unsigned char *transport) {

    struct icmp_header *icmp = (struct icmp_header *)transport;

    printf("Protocol: ICMP\n");
    printf("ICMP Type: %d\n", icmp->type);
    printf("ICMP Code: %d\n", icmp->code);
}

/* -------- Packet Parser -------- */

void parse_packet(const unsigned char *packet) {

    /* Ethernet header */
    struct ethernet_header *eth = (struct ethernet_header *)packet;

    printf("Source MAC: %02X:%02X:%02X:%02X:%02X:%02X\n",
           eth->src_mac[0], eth->src_mac[1], eth->src_mac[2],
           eth->src_mac[3], eth->src_mac[4], eth->src_mac[5]);

    printf("Destination MAC: %02X:%02X:%02X:%02X:%02X:%02X\n",
           eth->dest_mac[0], eth->dest_mac[1], eth->dest_mac[2],
           eth->dest_mac[3], eth->dest_mac[4], eth->dest_mac[5]);

    /* IP header */
    struct ip_header *ip =
        (struct ip_header *)(packet + sizeof(struct ethernet_header));

    printf("Source IP: %s\n", inet_ntoa(*(struct in_addr *)&ip->src_ip));
    printf("Destination IP: %s\n", inet_ntoa(*(struct in_addr *)&ip->dst_ip));

    /* IP header length */
    int ip_header_len = (ip->version_ihl & 0x0F) * 4;

    /* Pointer to transport layer */
    const unsigned char *transport =
        packet + sizeof(struct ethernet_header) + ip_header_len;

    /* Protocol dispatch */
    switch(ip->protocol) {

        case PROTO_TCP:
            parse_tcp(transport);
            break;

        case PROTO_UDP:
            parse_udp(transport);
            break;

        case PROTO_ICMP:
            parse_icmp(transport);
            break;

        default:
            printf("Protocol: Other (%d)\n", ip->protocol);
    }

    printf("\n");
}