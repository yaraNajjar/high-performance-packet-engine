#!/bin/bash

# Exit immediately if a command exits with a non-zero status.
set -e

LOG_FILE="docs/benchmark_results.txt"
TMP_FILE="benchmark_tmp.txt"
EXECUTABLE="packet_sniffer"
SOURCES="src/packet_sniffer.c src/parser.c src/rules.c src/packet_queue.c"
COMPILE_FLAGS="-lpcap -lpthread"

# Function to run a benchmark for a given mode
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

# clear previous results
echo "" > $LOG_FILE

echo "===================================="
echo "Packet Processing Benchmark"
echo "===================================="

echo "Compiling project..."
gcc src/packet_sniffer.c src/parser.c src/rules.c src/packet_queue.c -o packet_sniffer -lpcap -lpthread
gcc $SOURCES -o $EXECUTABLE $COMPILE_FLAGS

echo ""
echo "Running OLD system benchmark (60s)..."
run_mode_benchmark "OLD" "old" 3
run_mode_benchmark "NEW" "" 5

sudo ./packet_sniffer old | tee $TMP_FILE

grep -A 3 "Benchmark Results" $TMP_FILE >> $LOG_FILE

echo ""
echo "Running NEW system benchmark (60s)..."

sudo ./packet_sniffer | tee $TMP_FILE

grep -A 5 "Benchmark Results" $TMP_FILE >> $LOG_FILE

rm $TMP_FILE

echo ""
echo "Benchmark finished."
echo "Results saved to $LOG_FILE"