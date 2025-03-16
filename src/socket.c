#include "../lib/socket.h"

int socket_work(int *sockfd){
	//int n;
	struct sockaddr_in servaddr;
	// char recvline[MAXLINE + 1];

	*sockfd = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
	if (*sockfd < 0) {
		perror("Socket create with faill");
		return -1;
	}

	servaddr.sin_family =  AF_INET;
	// servaddr.sin_port = htons();
	return *sockfd;
}
