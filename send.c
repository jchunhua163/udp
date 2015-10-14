/*
 * server.c
 *
 *  Created on: Sep 29, 2015
 *      Author: bill
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define N 64
//#define BROADCAST_ADDR "192.168.121.255" //注意应该填写广播地址
typedef struct sockaddr SA;

int main(int argc, char *argv[]) {
	int sockfd, on = 1;
	socklen_t addr_len;
	char buf[N];
	struct sockaddr_in peeraddr;


	if (argc < 3) {
		printf("input format is : %s    \n", argv[0]);
		return -1;
	}

	if ((sockfd = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1) {
		perror("sock fail");
		return -1;
	}

	if (setsockopt(sockfd, SOL_SOCKET, SO_BROADCAST, &on, sizeof(on)) == -1) {
		perror("setsockopt fail");
		exit(-1);
	}

	peeraddr.sin_family = PF_INET;
	peeraddr.sin_port = htons(atoi(argv[2]));
	peeraddr.sin_addr.s_addr = inet_addr(argv[1]);
	strcpy(buf, "Hi! I am broadcast messgae\n");
	while (1) {
		addr_len = sizeof(peeraddr);
		sendto(sockfd, buf, N, 0, (SA *) &peeraddr, addr_len);
		sleep(4);
	}
	return 0;
}

