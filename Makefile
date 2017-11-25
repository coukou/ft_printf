# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: spopieul <spopieul@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/19 20:53:51 by spopieul          #+#    #+#              #
#    Updated: 2017/11/25 01:11:01 by spopieul         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# $(1): folder
# $(2): files
define get_objs
	$(addprefix $(1)/, $(addsuffix .o, $(2)))
endef

# LIBFT
# -------------

LIBFT_DIR	= libs/libft
LIBFT_FILES	= ft_putstr ft_strlen ft_putchar ft_putnbr ft_strlenc ft_strndup\
				ft_strchr ft_strjoin ft_strnew ft_strcat ft_strjoin ft_memalloc\
				ft_bzero ft_memset ft_strdup ft_strdel ft_memdel ft_strcpy\
				ft_memcmp ft_strjoin_free ft_strdupc

LIBFT_ODIR 	= $(LIBFT_DIR)/objs
LIBFT_SDIR 	= $(LIBFT_DIR)/srcs

LIBFT_INC	= -I $(LIBFT_DIR)/includes

$(LIBFT_ODIR)/%.o: $(LIBFT_SDIR)/%.c
	$(CC) -c $(LIBFT_INC) -o $@ $< $(CFLAGS)

# PRINTF
# -------------

PRINTF_DIR		= .
PRINTF_FILES	= ft_printf ft_format

PRINTF_ODIR 	= $(PRINTF_DIR)/objs
PRINTF_SDIR 	= $(PRINTF_DIR)/srcs

PRINTF_INC		= -I $(PRINTF_DIR)/includes

$(PRINTF_ODIR)/%.o: $(PRINTF_SDIR)/%.c
	$(CC) -c -ggdb $(PRINTF_INC) $(LIBFT_INC) -o $@ $< $(CFLAGS)

# MAKE
# -------------

NAME 	= libftprintf.a
CC		= gcc
CFLAGS	= -Wall -Wextra -Werror
OBJS 	=\
	$(call get_objs, $(LIBFT_ODIR), $(LIBFT_FILES)) \
	$(call get_objs, $(PRINTF_ODIR), $(PRINTF_FILES))

$(NAME): $(OBJS)
	ar rvs $(NAME) $^

all: $(NAME)

clean:
	/bin/rm -rf $(LIBFT_ODIR)/*
	/bin/rm -rf $(PRINTF_ODIR)/*

fclean: clean
	/bin/rm -f $(NAME)

re: fclean all
