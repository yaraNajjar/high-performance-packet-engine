#ifndef NETWORK_INTERFACE_H
#define NETWORK_INTERFACE_H

#include <pcap.h>

#ifdef __cplusplus
extern "C" {
#endif

int network_interface_init(const char *dev);

int network_capture_packet(int batch_size, pcap_handler handler);

void network_interface_close();

#ifdef __cplusplus
}
#endif

#endif