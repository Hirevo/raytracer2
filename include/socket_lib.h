/*
** socket_lib.h for sok in /home/Maxime/perso/echat/lib/include/
**
** Made by Maxime Jenny
** Login   <maxime.jenny@epitech.eu>
**
** Started on  Tue May  2 15:05:43 2017 Maxime Jenny
** Last update	Sat May 27 21:21:52 2017 Full Name
*/

#ifndef SOCKET_LIB_H_
# define SOCKET_LIB_H_

# define INVALID_SOCKET -1
# define SOCKET_ERROR -1
# define ERROR -1
# define PORTY 42

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <netdb.h>

typedef int t_SOCKET;
typedef struct sockaddr_in t_SOCKADDR_IN;
typedef struct sockaddr t_SOCKADDR;
typedef struct in_addr t_IN_ADDR;
typedef struct hostent t_hostent;

int			create_socket(void);
int			send_protocol(t_SOCKET, void *, long, int);
int			recv_protocol(t_SOCKET, void **, long *, int);
void			set_sockaddr_in(t_SOCKADDR_IN *son);
int			read_protocol(t_SOCKET sock, void **msg, long *len);
int			count_place(int fd, long size);
int			my_put_error(char *str, int nbr);

#endif /* !SOCKET_LIB_H_ */
