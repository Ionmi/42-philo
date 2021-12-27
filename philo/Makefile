# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ioromero <ioromero@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/10 11:13:33 by ioromero          #+#    #+#              #
#    Updated: 2021/12/23 19:14:22 by ioromero         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS	= 	main.c			\
			philo.c			\
			utils.c			\
			philo_actions.c	\
		
OBJS	= ${SRCS:.c=.o}

NAME	= philo

SNAME	= fsanitize

RM		= rm -rf

CC		= gcc

RED		= \033[0;31m

GREEN		= \033[0;32m

WHITE		= \033[0;37m

SFLAGS	= -fsanitize=address -g3

CFLAGS	= -Wall -Werror -Wextra


all:	
		@ $(MAKE) -s $(NAME)
		@ echo "$(GREEN)Compiled ✅$(WHITE)"

$(NAME) :	${OBJS}
			@ echo "$(RED)Compiling... ⏳$(WHITE)"
			@ $(CC) ${CFLAGS} ${SRCS} -o $(NAME)

s:		
		@ $(MAKE) -s fsanitize
		@ echo "$(GREEN)Compiled with fsanitize ✅$(WHITE)"

$(SNAME):	${OBJS}
			@ echo "$(RED)Compiling with fsanitize... ⏳$(WHITE)"
			@ $(CC) ${CFLAGS} $(SFLAGS) ${SRCS} -o $(NAME)
			
clean:
		@ echo "$(RED)Clean in progress... ⏳$(WHITE)"
		@ $(RM) philo.dSYM
		@ $(RM) $(OBJS)
		@ echo "$(GREEN)Clean done ✅$(WHITE)"

fclean: 
		@ echo "$(RED)Fclean in progress... ⏳$(WHITE)"
		@ $(RM) *.dSYM
		@ $(RM) $(OBJS)
		@ $(RM) $(NAME)
		@ echo "$(GREEN)Fclean done ✅$(WHITE)"

re:		fclean all

.PHONY: all s clean fclean re