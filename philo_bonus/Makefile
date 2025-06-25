SRCS 			= philosophers.c check_arguments.c init_sim_pt_one.c init_sim_pt_two.c \
					routine_pt_one.c routine_pt_two.c utils_pt_one.c utils_pt_two.c
NAME			=	philo_bonus
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