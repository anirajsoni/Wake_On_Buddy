#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <sys/socket.h> 
#include <netinet/in.h> 
#include <arpa/inet.h> 
#include <string.h> 
#include <sys/types.h> 

int main() 
{ 
	int i; 
	unsigned char toSend[102],mac[6]; 
	struct sockaddr_in udpClient, udpServer; 
	int broadcast = 1 ; 

	// UDP Socket creation 
	int udpSocket = socket(AF_INET, SOCK_DGRAM, 0); 

	// Manipulating the Socket 
	if (setsockopt(udpSocket, SOL_SOCKET, SO_BROADCAST, 
				&broadcast, sizeof broadcast) == -1) 
	{ 
		perror("setsockopt (SO_BROADCAST)"); 
		exit(EXIT_FAILURE); 
	} 
	udpClient.sin_family = AF_INET; 
	udpClient.sin_addr.s_addr = INADDR_ANY; 
	udpClient.sin_port = 0; 

	//Binding the socket 
	bind(udpSocket, (struct sockaddr*)&udpClient, sizeof(udpClient)); 

	for (i=0; i<6; i++) 
		toSend[i] = 0xFF; 

	//  MAC Address is: d7:5d:e2:a4:0a:58 
	mac[0] = 0xd7; // 1st octet of the MAC Address 
	mac[1] = 0x5d; // 2nd octet of the MAC Address 
	mac[2] = 0xe2; // 3rd octet of the MAC Address 
	mac[3] = 0xa4; // 4th octet of the MAC Address 
	mac[4] = 0x0a; // 5th octet of the MAC Address 
	mac[5] = 0x58; // 6th octet of the MAC Address 

	for (i=1; i<=16; i++) 
		memcpy(&toSend[i*6], &mac, 6*sizeof(unsigned char)); 

	udpServer.sin_family = AF_INET; 

	// Braodcast address 
	udpServer.sin_addr.s_addr = inet_addr("10.89.255.255"); 
	udpServer.sin_port = htons(9); 

	sendto(udpSocket, &toSend, sizeof(unsigned char) * 102, 0, 
			(struct sockaddr*)&udpServer, sizeof(udpServer)); 
	return 0; 
} 

