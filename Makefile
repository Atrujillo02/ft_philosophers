# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: atrujill <atrujill@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/03 17:59:46 by atrujill          #+#    #+#              #
#    Updated: 2023/05/19 11:46:45 by atrujill         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = philo
CFLAGS 		= -Wall -Wextra -Werror -pthread
NORMFLAG 	= -R CheckForbiddenSourceHeader
SRC_DIR		= src
FILES		= main.c init.c utils.c cycle.c status.c all_free.c 
SRCS		= $(addprefix $(SRC_DIR)/, $(FILES))
OBJS 		= $(SRCS:.c=.o)

all: 		$(NAME)

$(NAME):	$(OBJS)
			gcc $(CFLAGS) $(SRCS) -o $(NAME)

%.o:		%.c
			gcc $(CFLAGS) -c $< -o $@

clean:
			rm -f $(OBJS)

fclean:		clean
			rm -f $(NAME)

re: 		fclean all

norm:
			norminette $(NORMFLAG) src

.PHONY:		all clean fclean re norm