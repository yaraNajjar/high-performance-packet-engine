#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/ip.h>
#include <netinet/tcp.h>
#include <net/ethernet.h>

int main() {

    int sock_raw;
    unsigned char buffer[65536];

    sock_raw = socket(AF_PACKET , SOCK_RAW , htons(ETH_P_ALL));

    if(sock_raw < 0){
        printf("Socket creation failed\n");
        return 1;
    }

    printf("Packet sniffer started...\n");

    while(1){

        int data_size = recvfrom(sock_raw , buffer , 65536 , 0 , NULL , NULL);

        struct ethhdr *eth = (struct ethhdr *)buffer;

        if(ntohs(eth->h_proto) == ETH_P_IP){

            struct iphdr *ip = (struct iphdr *)(buffer + sizeof(struct ethhdr));

            if(ip->protocol == IPPROTO_TCP){

                struct tcphdr *tcp = (struct tcphdr *)
                    (buffer + sizeof(struct ethhdr) + ip->ihl*4);

                printf("\nSRC IP: %s\n", inet_ntoa(*(struct in_addr *)&ip->saddr));
                printf("DST IP: %s\n", inet_ntoa(*(struct in_addr *)&ip->daddr));
                printf("PROTO : TCP\n");
                printf("SRC PORT: %d\n", ntohs(tcp->source));
                printf("DST PORT: %d\n", ntohs(tcp->dest));
            }
        }
    }

    return 0;
}