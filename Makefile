CC = cc
CFLAGS = -Wall -Werror -Wextra -I. -g
LIBFT_DIR = ./Libft
LIBFT = $(LIBFT_DIR)/libft.a
RM = rm -f
srcServer =  server_buf.c
srcClient =  client_buf.c
execServer = server
execClient = client
objServer = $(srcServer:.c=.o) 
objClient = $(srcClient:.c=.o)

all :${LIBFT} ${execClient} ${execServer}

${LIBFT}:
	${MAKE} -C ${LIBFT_DIR}

$(execServer) : ${objServer} ${LIBFT}
	${CC} ${CFLAGS}  ${objServer} -o ${execServer} -L${LIBFT_DIR} -lft

$(execClient) : ${objClient} ${LIBFT}
	${CC} ${CFLAGS}  ${objClient} -o ${execClient} -L${LIBFT_DIR} -lft

clean : 
	${RM} ${objServer} ${objClient}
	${MAKE} -C ${LIBFT_DIR} clean


fclean : clean
	${RM} ${execServer} ${execClient}
	${MAKE} -C ${LIBFT_DIR} fclean

re : fclean all 
.PHONY : all clean fclean re	