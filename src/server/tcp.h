#ifndef TCP_H
#define TCP_H

#include "../misc/typedefs.h"

struct __tcp_header {
    word_t source_port;
    word_t dest_port;
    byte_t seq_num[4];
    byte_t ack_num[4];
    byte_t data_offset; // Data offset (4 bits), reserved (4 bits) 
    byte_t flags; // Control flags: CWR | ECE | URG | ACK | PSH | RST | SYN | FIN 
    word_t win_size;
    word_t checksum;
    word_t urgent_ptr;
} tcp_header;

#define TCP_HEADER_LENGTH 0x0014

struct ip_header {
    ipv4_t source_addr;
    ipv4_t dest_addr;
    byte_t zeros;
    byte_t protocol;
    word_t tcp_len;
};

struct tcp_packet {
    struct ip_header ip_header;
    struct tcp_header tcp_header;
    byte_t *data;
};

#endif