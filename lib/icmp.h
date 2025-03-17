#pragma once

#include "../lib/un.h"

#define ICMP_ECHO_REQUEST 8
#define ICMP_ECHO_REPLY 0
#define ICMP_TIME_EXCEEDED 11
#define ICMP_DESTINATION 3

// ICMp packet encapsulation in ipv4 packet. The packet have: header and data.
// Declared two struct(icmp_header, icmp_time_exceeded) and func checksum 
// checksum https://www.scribd.com/doc/7074846/ICMP-and-Checksum-Calc (Figure 9.19) 

struct icmp_header{
	uint8_t icmp_type;
	uint8_t icmp_code;
	uint16_t icmp_checksum;
	uint16_t id;
	uint16_t seq;
}__attribute__((packed));

uint16_t checksum(void *buffer, size_t length);
int send_echo_req(int sock, struct sockaddr_in* addr, int ident, int seq, int ttl);
int recv_echo_reply(int sock, int ident,int ttl);