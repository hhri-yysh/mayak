#include "socket.h"

int
socket_work (int *sockfd, const char *_interface) {
        *sockfd = socket (AF_INET, SOCK_RAW, IPPROTO_ICMP);
        if (*sockfd < 0) {
                perror ("socket");
                return -1;
        }

	if (*_interface != NULL && setsockopt(*sockfd, SOL_SOCKET, 
				SO_BINDTODEVICE, _interface,  sizeof(_interface)) == -1) {
		perror("setsockopt");
		fprintf(stderr, "Invalid interface device %s\n", _interface);
		close(*sockfd);
		exit(EXIT_FAILURE);
	}

        return 0;
}
