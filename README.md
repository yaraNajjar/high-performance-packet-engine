# High-Performance Packet Processing Engine

This project implements a **low-level packet analyzer** written in **C/C++** on **Linux**, designed for **high-performance networking and real-time packet processing**.

## Features

- **Packet capture** using **libpcap**
- Extract **Ethernet** and **IP headers**
- Print **MAC addresses** and **IP addresses**
- **Multi-threaded worker architecture** for high throughput
- **Lock-free ring buffer queue** for efficient packet handoff
- **Firewall rule engine** (dynamic IP allow/deny)
- **Batch processing** and **memory reuse** for performance optimization
- **Packets-per-second benchmarking** and statistics monitoring

## Technologies

- **C, C++**
- **Linux**
- **libpcap**
- **pthread**
- **Git**

## Run

Compile:

```bash
gcc src/packet_sniffer.c src/parser.c src/rules.c src/packet_queue.c -o packet_sniffer -lpcap -lpthread
```

Run:
```bash
sudo ./packet_sniffer
```

## Notes:
- Supports **high-performance mode** with larger batch sizes for stress testing.
- Firewall rules can be modified in rules.c or dynamically during runtime.
- For benchmarking, monitor the console output to see **allowed/blocked packets** and **packets per second (PPS).**