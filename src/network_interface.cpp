#include <pcap.h>
#include <iostream>
#include "../include/network_interface.h"

static pcap_t *handle = nullptr;

int network_interface_init(const char *dev)
{
    char errbuf[PCAP_ERRBUF_SIZE];

    handle = pcap_open_live(dev, 65536, 1, 1000, errbuf);

    if (!handle) {
        std::cerr << "Failed to open device: " << dev << std::endl;
        return -1;
    }

    std::cout << "Network interface initialized: " << dev << std::endl;

    return 0;
}

int network_capture_packet(int batch_size,pcap_handler handler)
{
    if (!handle)
        return -1;

    return pcap_dispatch(handle, batch_size, handler, nullptr);
}

void network_interface_close()
{
    if (handle) {
        pcap_close(handle);
        handle = nullptr;
    }
}