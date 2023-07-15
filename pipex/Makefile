# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aguezzi <aguezzi@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/04 14:34:04 by aguezzi           #+#    #+#              #
#    Updated: 2023/06/10 13:50:30 by aguezzi          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= pipex

NAME_BONUS	= pipex_bonus

SRCS	= pipex.c pipex_utils.c childs.c

BONUS	= bonus/pipex_bonus.c bonus/pipex_utils_bonus.c bonus/childs_bonus.c bonus/heredoc.c

CC	= gcc

FLAGS	= -Wall -Wextra -Werror

OBJS	= ${SRCS:.c=.o}

OBJS_BONUS	= ${BONUS:.c=.o}

RM	= rm -f

all:	${NAME}

.c.o:
		@echo "Compil $<..."
		@${CC} ${FLAGS} -c $< -o ${<:.c=.o}

${NAME}:	${OBJS}
		@echo "Compil libft..."
		@make -C libft
		@${CC} ${FLAGS} -Llibft -lft ${OBJS} -o ${NAME}

bonus:		${OBJS_BONUS}
		@echo "Compil libft..."
		@make -C libft
		@${CC} ${FLAGS} -Llibft -lft ${OBJS_BONUS} -o ${NAME_BONUS}

clean:
		@echo "clean all..."
		@${RM} ${OBJS} ${OBJS_BONUS}
		@make clean -C libft

fclean:	clean
		@echo "fclean all..."
		@${RM} ${NAME} ${NAME_BONUS}
		@${RM} libft/libft.a

re:	fclean all

.PHONY:	all clean fclean re