#pragma once

#include "un.h"

/*struct arp_header{
        unsigned char
        unsigned char
        unsigned char
};

struct arp_request_header{
        unsigned char
        unsigned char
        unsigned char
};

struct eth_frame{
        unsigned char dst[];
        unsigned char src[];
        unsigned short type; // 2 byte
        char payload[1500]; // ARP & IP
};

struct ip_datagram{

};
*/

int socket_work (int *sockfd);
