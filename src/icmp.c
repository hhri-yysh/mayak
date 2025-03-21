#include "../lib/icmp.h"

uint16_t
checksum (void *buffer, size_t length) {
        uint16_t *data = buffer;
        uint32_t sum = 0;

        for (; length > 1; length -= 2) {
                sum += *data++;
        }

        if (length == 1) {
                sum += *((uint8_t *)data);
        }

        sum = (sum >> 16) + (sum & 0xffff);
        sum += (sum >> 16);

        return ~sum;
}

int
send_echo_req (int sock, struct sockaddr_in *addr, int ident, int seq,
               int ttl) {
        struct icmp_header icmp;
        memset (&icmp, 0, sizeof (icmp));

        icmp.icmp_type = ICMP_ECHO_REQUEST;
        icmp.icmp_code = 0;
        icmp.id = htons (ident);
        icmp.seq = htons (seq);
        icmp.icmp_checksum = 0;

        icmp.icmp_checksum = checksum (&icmp, sizeof (icmp));

        if (sock < 0) {
                fprintf (stderr, "Invalid socket descriptor\n");
                return -1;
        }

        if (setsockopt (sock, IPPROTO_IP, IP_TTL, &ttl, sizeof (ttl)) < 0) {
                perror ("sock(TTL)");
                return -1;
        }

        int pack_bytes
            = sendto (sock, &icmp, sizeof (icmp), 0, (struct sockaddr *)addr,
                      sizeof (struct sockaddr_in));

        if (pack_bytes < 0) {
                perror ("sendto");
                return -1;
        }

        return (0);
}

int
recv_echo_reply (int sock, int ttl) {
        char BUFF[512];
        struct sockaddr_in sender;
        socklen_t sender_len = sizeof (sender);

        int pack_bytes
            = recvfrom (sock, BUFF, sizeof (BUFF), 0,
                        (struct sockaddr *)&sender, (socklen_t *)&sender_len);

        if (pack_bytes < 0) {
                if (errno == EAGAIN || errno == EWOULDBLOCK) {
                        printf ("%2d *\n", ttl); // output timeout
                        return (0);
                }
                perror ("recvfrom");
                return -1;
        }

        struct iphdr *ip_hdr = (struct iphdr *)BUFF;
        struct icmp_header *icmp
            = (struct icmp_header *)(BUFF + (ip_hdr->ihl * 4));

        printf ("Received ICMP packet: type=%d, code=%d, from=%s\n",
                icmp->icmp_type, icmp->icmp_code, inet_ntoa (sender.sin_addr));

        return 0;
}