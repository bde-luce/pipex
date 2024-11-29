# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bde-luce <bde-luce@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/04 18:48:55 by bde-luce          #+#    #+#              #
#    Updated: 2024/11/04 18:48:55 by bde-luce         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

SRC = pipe_fork create_path execute get_here_doc execute_hd make_here_doc \
	get_next_line/get_next_line get_next_line/get_next_line_utils pipex

OBJ = $(SRC:=.o)

CC = cc
CFLAGS = -Wall -Wextra -Werror
RM = rm -f

LIBFT = ./libft/libft.a
LIBFT_PATH = ./libft

all: $(NAME)

$(NAME): $(OBJ)
		make -C $(LIBFT_PATH)
		$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -o $(NAME)

clean:
		make clean -C $(LIBFT_PATH)
		$(RM) $(OBJ)

fclean: clean
		make fclean -C $(LIBFT_PATH)
		$(RM) $(NAME)

re: fclean all