#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#ifndef CONNECT_H
#include "connect.h"
#endif
#ifndef MAIN_H
#include "main.h"
#endif
#ifndef CONFIG_H
#include "config.h"
#endif
#ifndef LIST_H
#include "list.h"
#endif
#include <errno.h>

void client_connect(user_info* user_info);
/*
1. mutex init();
2. channel list init();
3  user list init();
4. be sure to perform liveness(ping) check after each loop
*/
void server_mutex_init();
void start_server(int sockfd){
  server_mutex_init();
  while(1){
    if(1/* add select system call*/){
      int client_socket = -1;
      struct sockaddr client_addr;
      memset(&client_addr, 0, sizeof(struct sockaddr));      
      socklen_t client_len = sizeof(struct sockaddr);
      client_socket = accept(sockfd, &client_addr, &client_len);
      if(client_socket < 0){/* failed to accept socket*/
	fprintf(stderr, "Error occurred while accepting client connection: %s", strerror(errno));
	continue;
      }
      user_info* user_inf = (user_info *)malloc(sizeof(user_info));
      memset(&user_inf, 0, sizeof(user_info));
      user_inf->socket = client_socket;
      user_inf->liveness = time(NULL);
      pthread_create(&(user_inf->user_thread), NULL, (void *(*)(void *))client_connect, (void *)user_inf);
    }
  }

}



int listen_bind_on_port(int port){

  int sockfd;

  struct sockaddr_in irc_socket;


  sockfd = socket(PF_INET, SOCK_STREAM, 0);

  memset(&irc_socket, 0, sizeof(irc_socket));
  irc_socket.sin_family = AF_INET;
  irc_socket.sin_port = htons(port);
  irc_socket.sin_addr.s_addr = htonl(INADDR_ANY);

  if(bind(sockfd, (struct sockaddr*)&irc_socket, sizeof(irc_socket)) < 0){
    fprintf(stderr, "Failed to bind socket\n");
    return -1;
  }
  if(listen(sockfd, MAXCONNECTION) < 0){
    fprintf(stderr, "Failed to listen on port %d\n", port);
    return -1;
  }
  return sockfd;
  
}
void client_connect(user_info* user_info){
  


}
