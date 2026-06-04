# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rafreire <rafreire@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/05/29 06:23:42 by rafreire          #+#    #+#              #
#    Updated: 2026/05/29 12:22:02 by rafreire         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

CC = cc
CFLAGS = -Wall -Werror -Wextra -pthread -g3

SRC_DIR = src/
OBJS_DIR = objs/
INCLUDES = -I includes/

SRC_LIST = parsing.c \
			pthread.c \
			utils.c \
			routine.c \
			main.c \
			monitor.c \
			data.c

SRCS = $(addprefix $(SRC_DIR), $(SRC_LIST))
OBJS = $(addprefix $(OBJS_DIR), $(SRC_LIST:.c=.o))

GREEN = \033[0;92m
YELLOW = \033[0;93m
CYAN = \033[0;96m
DEF_COLOR = \033[0;39m

all: $(NAME)

$(NAME): $(OBJS)
	@echo -n "$(YELLOW)A linkar $(NAME)... $(DEF_COLOR)"
	@sh -c '(while kill -0 $$PPID 2>/dev/null; do \
		echo -n "\b|"; sleep 0.05; \
		echo -n "\b/"; sleep 0.05; \
		echo -n "\b-"; sleep 0.05; \
		echo -n "\b\\"; sleep 0.05; \
	done) & \
	trap "kill $$!" EXIT; \
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)'
	@echo "\b$(GREEN)OK!$(DEF_COLOR)"

$(OBJS_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(OBJS_DIR)
	@echo -n "$(CYAN)A compilar $<... $(DEF_COLOR)"
	@sh -c '(while kill -0 $$PPID 2>/dev/null; do \
		echo -n "\b|"; sleep 0.05; \
		echo -n "\b/"; sleep 0.05; \
		echo -n "\b-"; sleep 0.05; \
		echo -n "\b\\"; sleep 0.05; \
	done) & \
	trap "kill $$!" EXIT; \
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@'
	@echo "\b$(GREEN)OK!$(DEF_COLOR)"

clean:
	@rm -rf $(OBJS_DIR)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re