# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bposa <bposa@student.hive.fi>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/19 18:50:25 by bposa             #+#    #+#              #
#    Updated: 2023/12/22 10:15:11 by bposa            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= libftprintf.a

CC	= cc

SRCS	= 	ft_printf.c \
			hex_prefix.c \
			put_hex.c \
			my_putnbr.c

OBJCS	= $(SRCS:.c=.o)

DEPS	= ft_printf.h

CFLAGS	= -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJCS)
	ar crs $(NAME) $(OBJCS)

%.o: %.c  $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -rf $(OBJCS)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all re clean fclean