NAME     := philo_bonus
CC       := cc
CFLAGS   := -Wall -Wextra -Werror
SRC      := philosophers.c check_arguments.c init_sim_pt_one.c init_sim_pt_two.c \
				routine_pt_one.c routine_pt_two.c utils_pt_one.c utils_pt_two.c
OBJ_DIR  := objects
OBJ      := $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))
GREEN    := \033[0;32m
BLUE     := \033[0;34m
CYAN     := \033[0;36m
RESET    := \033[0m
BOLD     := \033[1m

all: $(NAME)

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(OBJ_DIR)
	@printf "$(CYAN)Compiling:$(RESET) %-20s → $(GREEN)%s$(RESET)\n" "$<" "$@"
	@$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJ)
	@printf "$(BOLD)Linking...$(RESET)\n"
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME)
	@printf "$(GREEN)✔ Build complete: $(NAME)$(RESET)\n"

clean:
	@rm -rf $(OBJ_DIR)
	@printf "$(BLUE)🧹 Cleaned object files$(RESET)\n"

fclean: clean
	@rm -f $(NAME)
	@printf "$(BLUE)🧹 Removed binary $(NAME)$(RESET)\n"

re: fclean all

.PHONY: all clean fclean re
