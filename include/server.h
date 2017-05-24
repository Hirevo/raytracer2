/*
** server.h for server in /home/arthur/delivery/MUL/raytracer2
** 
** Made by Arthur Knoepflin
** Login   <arthur.knoepflin@epitech.eu>
** 
** Started on  Wed May 24 09:27:17 2017 Arthur Knoepflin
** Last update Thu May 25 00:52:11 2017 Arthur Knoepflin
*/

#ifndef SERVER_H_
# define SERVER_H_

# include "raytracer.h"

# define PORT		33000
# define SIZE_SOCK	4096
# define CLIENTS	4

typedef int			t_socket;
typedef struct sockaddr_in	t_sockaddr_in;
typedef struct sockaddr		t_sockaddr;
typedef struct in_addr		t_in_addr;

typedef struct	s_client
{
  t_socket	sock;
  int		ready;
}		t_client;

/*
** check_cli_ready.c
*/

int	check_cli_ready(t_client *, int);

/*
** client.c
*/

int	print_state_wait(t_socket);
void	broadcast_start(t_client *);
int	client_cluster(t_params *);

/*
** com_sock.c
*/

int	read_socket(t_socket, char **);
void	write_socket(t_socket, char *);

/*
** get_ip.c
*/

char	*get_ip();

/*
** manag_client.c
*/

void	remove_client(t_client *, int, int *, int);
void	close_all(t_client *, int);

/*
** server.c
*/

int	server_cluster(t_window *, t_params *);

/*
** treat_resp_cli.c
*/

int	treat_resp(t_socket, char *);

/*
** treat_resp_wait.c
*/

int	treat_resp_cli_w(t_client *, int, char *, int);

/*
** recv_parse.c
*/

int	recv_parse(t_socket, t_params *);

/*
** send_parse.c
*/

int	send_parse(t_client *, t_params *);

/*
** wait_connection.c
*/

int	wait_connection_s(t_client *, t_socket);

#endif /* !SERVER_H_ */
