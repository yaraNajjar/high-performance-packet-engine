# High Performance Packet Engine

This project implements a low level packet analyzer written in C
for learning high performance networking and packet processing.

## Features

- Packet capture using libpcap
- Extract Ethernet headers
- Extract IP headers
- Print MAC addresses
- Print IP addresses

## Technologies

- C
- Linux
- libpcap
- Git

## Run

Compile:

gcc src/packet_sniffer.c -o packet_sniffer -lpcap

Run:

sudo ./packet_sniffer