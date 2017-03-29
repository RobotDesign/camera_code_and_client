#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include <unistd.h>
#include <WinSock2.h>
#include <sys/types.h> 
//#include <sys/socket.h>
//#include <netinet/in.h>

int sockfd;
struct sockaddr_in cli_addr;

void setupServer();
//void sendData(data)

int main(int argc, char *argv[])
{

	setupServer();


	int n;
	printf("Writing\n");
	n = sendto(sockfd, "I got your message", 18, 0, (struct sockaddr *) &cli_addr, sizeof(cli_addr));
	if (n < 0) {
		printf("ERROR writing to socket\n");
	}

}


void setupServer() {
	int ServPortNum = 4001;
	int CliPortNum = 4002;
	int newsockfd;
	///socklen_t clilen;
	struct sockaddr_in serv_addr;
	int n;

	sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	if (sockfd < 0) {
		printf("Error opening socket\n");
	}

	memset((char *)&serv_addr, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	serv_addr.sin_port = htons(ServPortNum);

	memset((char *)&cli_addr, sizeof(cli_addr));
	cli_addr.sin_family = AF_INET;
	cli_addr.sin_addr.s_addr = INADDR_ANY;
	cli_addr.sin_port = htons(CliPortNum);

	if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
		printf("ERROR on binding\n");

	}
	printf("Bound\n");


}