# Project Architecture
See the architecture diagram:
```bash
docs/architecture_diagram.md
```

## Overview

- The system is designed to process network packets in **high-performance environments** using a **multi-threaded architecture**.
- The architecture separates packet **capture, processing**, and **monitoring** into different components in order to improve throughput and scalability.

The packet flow:

```bash
Network Interface
        │
        ▼
   Packet Capture
     (libpcap)
        │
        ▼
   Packet Queue
 (Shared buffer)
        │
        ▼
  Worker Threads
 (Batch processing)
        │
        ▼
 Firewall Rules
        │
        ▼
 Packet Parsing
        │
        ▼
 Statistics / Monitoring
 ```

## System Components
1. Packet Capture

File:
```bash
src/packet_sniffer.c
```
The capture module uses **libpcap** to receive packets from the network interface.

Packets are captured using:
```bash
pcap_dispatch()
```
Captured packets are pushed into the **packet queue** for processing by worker threads.

Responsibilities:

* Capture packets from network interface

* Copy packet data into internal buffers

* Send packets to the processing queue

## Packet Queue

File:
```bash
src/packet_queue.c
```
The packet queue acts as a **shared buffer** between the capture thread and worker threads.

It is implemented as a **ring buffer** with:

* head pointer

* tail pointer

* packet count

Synchronization is handled using a **mutex**.

Responsibilities:

* Store captured packets

* Allow workers to retrieve packets

* Support **batch dequeue** for performance

## Worker Threads

Workers are responsible for **processing packets in parallel**.

Each worker performs:

1. equeue packet batch

2. Validate Ethernet frame

3. Extract IP header

4. Apply firewall rules

5. Parse packet

Workers use **batch processing**:
```bash
BATCH_SIZE = 50
```
Processing multiple packets per iteration improves CPU cache efficiency.

## Firewall Rule Engine

File:
```bash
src/rules.c
```
The firewall module implements a simple rule engine.

Rules define whether packets from a specific **IP address** should be:

* allowed

* blocked

Example rule:
```bash
add_rule(&my_rules, inet_addr("8.8.8.8"), false);
```
Which blocks packets from:
```bash
8.8.8.8
```

## Packet Parser

File:
```bash
src/parser.c
```
The parser extracts protocol headers from raw packet data.

Supported protocols:

* Ethernet
* IPv4
* TCP
* UDP
* ICMP

Header structures are defined in:
```bash
include/packet.h
```

## Monitoring System

A dedicated monitoring thread prints statistics every second.

Displayed statistics:

* Packets processed per second
* Allowed packets
* Blocked packets

Example output:
```bash
Packets processed: 720 pkt/s
Allowed packets: 510
Blocked packets: 210
```

## Benchmark Mode

The project includes two modes to compare performance.

### OLD System

Single-thread processing:
```bash
Capture → Parse → Filter
```

### NEW System

Multi-thread architecture:
```bash
Capture → Queue → Workers → Parse → Filter
```

Benchmark duration:
```bash
60 seconds
```

Results show **packets-per-second (PPS)** for both systems.

Architecture Diagram
```bash
           +-------------------+
           |   Network Card    |
           +-------------------+
                     |
                     ▼
             +--------------+
             |   libpcap    |
             | Packet Capture|
             +--------------+
                     |
                     ▼
            +----------------+
            |   Packet Queue |
            |   Ring Buffer  |
            +----------------+
             /       |       \
            /        |        \
           ▼         ▼         ▼
     +---------+ +---------+ +---------+
     | Worker1 | | Worker2 | | Worker3 |
     +---------+ +---------+ +---------+
           |          |          |
           ▼          ▼          ▼
        Firewall   Firewall   Firewall
           |          |          |
           ▼          ▼          ▼
        Parser     Parser     Parser
```

### Performance Optimizations

The system improves performance using:

* Multi-threading
* Batch packet processing
* Shared queue
* Minimal memory allocations

### File Map
```bash
src/
 packet_sniffer.c   -> main capture engine
 parser.c           -> packet parsing
 packet_queue.c     -> queue implementation
 rules.c            -> firewall rules

include/
 packet.h
 packet_queue.h
 rules.h
```