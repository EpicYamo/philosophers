SRCS 			= philosophers.c check_arguments.c init_sim_pt_one.c init_sim_pt_two.c \
					routine.c death_monitor.c eat_perm_monitor.c meals_monitor.c \
					utils_pt_one.c utils_pt_two.c \

NAME			=	philosophers
CC				=	cc
CFLAGS			=	-Wall -Wextra -Werror
RM				=	rm -rf

all: $(NAME)

$(NAME): $(SRCS)
	${CC} ${CFLAGS} -o $(NAME) $(SRCS)

clean:
	$(RM) $(NAME)

fclean:	clean

re:		clean all

.PHONY:	all clean fclean re