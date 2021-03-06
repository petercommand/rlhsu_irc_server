#ifndef BOKCHAT_GETOPT_H
#define BOKCHAT_GETOPT_H

#include <getopt.h>
#include "main.h"
struct cmd_arg_opt {
  bool verbose;
  bool daemonize;
  char* host;
  int irc_port;
  int ssl_irc_port;
  bool help;
};
typedef struct cmd_arg_opt cmd_arg_opt;
void get_server_opt(cmd_arg_opt* cmd_opt_ptr,int* argc, char** argv[]);



#endif
