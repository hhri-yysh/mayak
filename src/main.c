#include "../lib/un.h"
#include "../lib/icmp.h"
#include "../lib/socket.h"

void err_quit(const char* msg){
	perror(msg);
	exit(0);
}

void err_sys(const char* msg){
	perror(msg);
	exit(0);
}

int main(int argc, char** argv){
	/*
	 *	Example of working with glibc (getopt.h): 
	 *	https://www.gnu.org/software/libc/manual/html_node/Getopt-Long-Option-Example.html
	 * 
	*/

	int sockfd, opt;

	if (socket_work(&sockfd) < 0) {
		err_quit("Failed to create socket");
	}

	while(1) {
		static struct option long_opt[] = {
			{"help", no_argument,   0,	'h'},
			{"ipv4", no_argument,	0,	'4'},
			{"ipv6", no_argument,   0,	'6'},
			{"fqdn", no_argument,   0,	'f'},
			{0, 0, 0, 0}
		};
	
		int opt_index = 0;

		opt = getopt_long(argc, argv, "46f", 
					long_opt, &opt_index);
		if ( opt == -1)
			break;
		switch (opt)
		{
			case 0: 
				if (long_opt[opt_index].flag != 0)
					break;
				printf ("%s", long_opt[opt_index].name);
				if (optarg)
					printf("%s", optarg);
				printf("\n");
				break;
			case 'h':
				printf("\t --ipv4, -4\n");
				printf("\t --ipv6, -6\n");
				printf("\t --fqdn, -f\n");
				break;
			case '4':
				printf("IPv6 select\n");
				break;
			case '6':
				printf("IPv4 select\n");
				break;
			case 'f':

				break;
			case '?':
		         //	printf("\n");
			 //	err_quit("Unrecognized flags.\n");
				break;
			default:
				abort();
		}
	}
	close(sockfd);
	exit(0);
}
