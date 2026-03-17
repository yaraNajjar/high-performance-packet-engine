#!/bin/bash

set -e

LOG_FILE="docs/benchmark_results.txt"
TMP_FILE="benchmark_tmp.txt"
EXECUTABLE="packet_sniffer"
#SOURCES="src/packet_sniffer.c src/parser.c src/rules.c src/packet_queue.c src/network_interface.cpp"
#COMPILE_FLAGS="-lpcap -lpthread"

run_mode_benchmark() {
    local mode_name=$1
    local mode_arg=$2
    local grep_lines=$3

    echo ""
    echo "Running $mode_name system benchmark (60s)..."

    sudo ./${EXECUTABLE} $mode_arg | tee $TMP_FILE

    echo "--- $mode_name System Benchmark ---" >> $LOG_FILE
    grep -A $grep_lines "Benchmark Results" $TMP_FILE >> $LOG_FILE
    echo "" >> $LOG_FILE
}

echo "" > $LOG_FILE

echo "===================================="
echo "Packet Processing Benchmark"
echo "===================================="

echo "Compiling project..."

# compile C files
gcc -O2 -Wall -Wextra -c src/packet_sniffer.c
gcc -O2 -Wall -Wextra -c src/parser.c
gcc -O2 -Wall -Wextra -c src/rules.c
gcc -O2 -Wall -Wextra -c src/packet_queue.c

# compile C++ file
g++ -O2 -Wall -Wextra -c src/network_interface.cpp

# link everything
g++ packet_sniffer.o parser.o rules.o packet_queue.o network_interface.o -o $EXECUTABLE -lpcap -lpthread

run_mode_benchmark "OLD" "old" 3
run_mode_benchmark "NEW" "" 5

rm $TMP_FILE

echo ""
echo "Benchmark finished."
echo "Results saved to $LOG_FILE"