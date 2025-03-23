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
               int ttl, struct timeval *start_time) {
        struct icmp_header icmp;
        memset (&icmp, 0, sizeof (icmp));

        icmp.icmp_type = ICMP_ECHO_REQUEST;
        icmp.icmp_code = 0;
        icmp.id = htons (ident);
        icmp.seq = htons (seq);
        icmp.icmp_checksum = 0;

        icmp.icmp_checksum = checksum (&icmp, sizeof (icmp));
	
	gettimeofday(start_time, NULL);

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
//recv_echo_reply (int sock, int ttl, struct timeval *rtt) {
recv_echo_reply (int sock, int ttl, struct timeval *start_time) {
        char BUFF[512];
        struct sockaddr_in sender;
        //struct timespec dt;
        struct timeval end_time, timeout;
        socklen_t sender_len = sizeof (sender);

        // setup timeout 
        timeout.tv_sec = TIMEOUT;
        timeout.tv_usec = 0;
        
        if (setsockopt (sock, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof (timeout)) < 0) {
                perror ("setsockopt");
                return -1;
        }
        // receive icmp packet
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

        //gettimeofday(&start_time, NULL);
	gettimeofday(&end_time, NULL); // record the end time (im fucked up, and I hate myself)
        struct iphdr *ip_hdr = (struct iphdr *)BUFF;
        struct icmp_header *icmp
            = (struct icmp_header *)(BUFF + (ip_hdr->ihl * 4));

        // struct timeval start_time;
        // struct timeval end_time;
        
        // dt.tv_sec = 0;
        // dt.tv_nsec = 1000000;
        // nanosleep(&dt, NULL);

        double rtt = rtt_calculate(start_time, &end_time);

        //printf("%lf %lf\n", rtt, rtt * 1000);

        // double rtt_cal = (end_time.tv_sec - start_time.tv_sec) + (end_time.tv_usec - start_time.tv_usec) / 1e6;

	if (icmp->icmp_type == 0 && icmp->icmp_code == 0){
                printf(" %3d %s %.2lf ms\n", ttl, inet_ntoa(sender.sin_addr), rtt);
		printf("Destination reached: %s\n", inet_ntoa(sender.sin_addr));	
		exit(0);
	} 
	else {
		printf(" %3d %s %.2lf ms\n", ttl, inet_ntoa(sender.sin_addr), rtt);
	}
        //printf ("Received ICMP packet: type=%d, code=%d, from=%s\n",
         //       icmp->icmp_type, icmp->icmp_code, inet_ntoa (sender.sin_addr));

        return 0;
}

double 
rtt_calculate(struct timeval *start_time, struct timeval *end_time) {
        long sec_s = end_time->tv_sec - start_time->tv_sec;
        long microsec_s = end_time->tv_usec - start_time->tv_usec;

        if (microsec_s < 0){
                sec_s -=1;
                microsec_s += 1000000;
        }
 
        //double rtt_cal = (end_time->tv_sec - start_time->tv_sec) + (end_time->tv_usec - start_time->tv_usec) / 1e6;
        double rtt_cal = (sec_s *1000.0) + (microsec_s / 1000.0);
        return rtt_cal;
}
