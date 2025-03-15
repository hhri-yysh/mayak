#include "../lib/icmp.h"

uint16_t(void *buffer, size_t length) {
	uint16_t *data = buffer;
	uint32_t sum = 0;

	for(; length > 1; length -= 2){
		sum += *data++;	
	}

	if (length == 1) {
		sum += *data;
	}

	sum = (sum >> 16) + (sum & 0xffff);
	sum += (sum >> 16); 

	sum = ~sum;
	return sum;
}
