# High-Performance Packet Processing Engine

This project implements a **low-level packet analyzer** written in **C/C++** on **Linux**, designed for **high-performance networking and real-time packet processing**.
The system captures packets using **libpcap**,  processes them through a **multi-threaded** worker architecture, and applies **basic firewall filtering rules.**

## Features

- **Packet capture** using **libpcap**
- Extract **Ethernet** and **IP headers**
- Print **MAC addresses** and **IP addresses**
- **Multi-threaded worker architecture** for high throughput
- **Packet queue** for safe communication between capture and workers
- **Batch packet processing** for improved performance
- **Firewall rule engine** (IP allow/deny)
- **Packets-per-second (PPS) benchmarking**
- **Real-time statistics monitoring**

## Technologies

- **C, C++**
- **Linux**
- **libpcap**
- **pthread**
- **Git**

## Project Structure
```bash
src/
    packet_sniffer.c
    parser.c
    packet_queue.c
    rules.c

include/
    packet.h
    packet_queue.h
    rules.h

docs/
    benchmark_results.txt
```

## Build

Compile the project using:
```bash
gcc src/packet_sniffer.c src/parser.c src/rules.c src/packet_queue.c -o packet_sniffer -lpcap -lpthread
```

## Run
### Run NEW System (Multi-threaded)

Runs the **high-performance architecture**:

- Packet capture thread
- Packet queue 
- Worker threads
- Batch packet processing

```bash
sudo ./packet_sniffer
```

### Run OLD System (Single-threaded Benchmark)

Runs the **baseline implementation** for performance comparison.
```bash
sudo ./packet_sniffer old
```

## Benchmark Mode

The benchmark compares two architectures:

**System**	| **Architecture**
OLD	        | Single-thread packet processing
NEW	        | Queue + Worker Threads + Batch Processing

Example output:

```bash
=== Benchmark Results ===
System: OLD (single-thread processing)
Total packets captured: 37385
Average PPS: 623
=== Benchmark Results ===
System: NEW (queue + workers + batching)
Total packets processed: 37863
Allowed packets: 29841
Blocked packets: 8022
Average PPS: 631
```

Full benchmark logs are available in:
```bash
docs/benchmark_results.txt
```
## Architecture

The system uses a **multi-threaded packet processing pipeline**.

Architecture diagram:
```bash
docs/architecture_diagram.md
```
Detailed architecture explanation:
```bash
docs/project_architecture.md
```

## Notes
- Benchmark duration is **60 seconds**.
- Firewall rules can be modified in **rules.c**.
- The current implementation parses **Ethernet** and **IP** headers.
- Future extensions include deeper parsing of **TCP / UDP / ICMP** protocols.