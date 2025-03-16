#include "../lib/un.h"
#include "../lib/icmp.h"
#include "../lib/socket.h"

void example_print(){
	printf("./mayak --help\n");
	printf("Traceroute clone created by Heorhii Yashchuk\n");	
}

void print_help(){
	printf("Usage: ./mayak [OPTIONS]\n");
	printf("Options:\n");
	printf("\t-4\t IPv4\n");
	printf("\t-6\t IPv6\n");
}

void err_quit(const char* msg){
	perror(msg);
	exit(0);
}

void err_sys(const char* msg){
	perror(msg);
	exit(0);
}

int main(int argc, char** argv){
	int sockfd;

	if (argc <=1) {
		example_print();
	}
	else if (strcmp(argv[1], "--help") == 0){
		print_help();	
	}

	if (argc != 2){
		err_quit("Usage: ./mayak [OPTIONS] <IP-Address>");
	}

	if ( socket_work(&sockfd) < 0 ){
		err_sys("Wrong IP");
	}
	
}
