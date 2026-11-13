#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>

int main(void) {
  // Creates a socket with IPv4 as the communication protocol and creates a two
  // way byte stream
  int tcp_socket = socket(AF_INET, /* IPv4 */ SOCK_STREAM, /* TCP */ 0);

  // Checks if there is an error with creating the socket
  if (tcp_socket == -1) {
    perror("socket()");
    return 1;
  }
  printf("socket creation succeeded\n");

  // Creates a new sockaddr_in struct which is a data structure used to specify
  // IPv4 socket addresses
  struct sockaddr_in bind_addr;
  // Fills the block of memory that contains the address with 0 instead of
  // garbage
  memset(&bind_addr, 0, sizeof(bind_addr));
  // Binds the port 1024 to the socket address struct
  bind_addr.sin_port = htons(1024);
  // Sets IPv4
  bind_addr.sin_family = AF_INET;
  // Tells the server to bind to all available network interfaces
  bind_addr.sin_addr.s_addr = INADDR_ANY;
  // Binds the newly created socket to the address we created so it can accept
  // incoming requests
  int rc =
      bind(tcp_socket, (const struct sockaddr *)&bind_addr, sizeof(bind_addr));
  if (rc < 0) {
    perror("bind()");
    return 1;
  }
  printf("bind succeeded\n");
}
