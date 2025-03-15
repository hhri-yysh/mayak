#include "../lib/un.h"
#include "../lib/icmp.h"

void example_print(){
	printf("./mayak --help\n");
	printf("Traceroute clone created by Heorhii Yashchuk\n");	
}

void print_help(){
	printf("Usage: ./mayak [OPTIONS]\n");
	printf("Options:\n");
	printf("-4\t IPv4\n");
	printf("-6\t IPv6\n");
}

int main(int argc, char** argv){
	if (argc <=1) {
		example_print();
	}
	else if (strcmp(argv[1], "--help") == 0){
		print_help();	
	}
}
