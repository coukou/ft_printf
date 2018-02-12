# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: spopieul <spopieul@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/19 20:53:51 by spopieul          #+#    #+#              #
#    Updated: 2018/02/12 19:32:12 by spopieul         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# $(1): folder
# $(2): files
define get_objs
	$(addprefix $(1)/, $(addsuffix .o, $(2)))
endef

# LIBFT
# -------------

LIBFT_DIR	= libft
LIBFT_FILES	= $(shell find libft/srcs/**/*.c | sed -e "s/libft\/srcs\///g" | sed -e "s/\.c//g")
# LIBFT_FILES	= conversion/ft_atoi
LIBFT_ODIR 	= $(LIBFT_DIR)/objs
LIBFT_SDIR 	= $(LIBFT_DIR)/srcs

LIBFT_INC	= -I $(LIBFT_DIR)/includes

$(LIBFT_ODIR)/%.o: $(LIBFT_SDIR)/%.c
	@mkdir -p $(@D)
	@$(CC) -c -ggdb $(LIBFT_INC) -o $@ $< $(CFLAGS)

# PRINTF
# -------------

PRINTF_DIR		= .
PRINTF_FILES	= ft_printf buffer

PRINTF_ODIR 	= $(PRINTF_DIR)/objs
PRINTF_SDIR 	= $(PRINTF_DIR)/srcs

PRINTF_INC		= -I $(PRINTF_DIR)/includes

$(PRINTF_ODIR)/%.o: $(PRINTF_SDIR)/%.c
	@mkdir -p $(@D)
	@$(CC) -c -ggdb $(PRINTF_INC) $(LIBFT_INC) -o $@ $< $(CFLAGS)

# MAKE
# -------------

NAME 	= libftprintf.a
CC		= gcc
CFLAGS	= -Wall -Wextra # -Werror
OBJS 	=\
	$(call get_objs, $(LIBFT_ODIR), $(LIBFT_FILES)) \
	$(call get_objs, $(PRINTF_ODIR), $(PRINTF_FILES))

$(NAME): $(make_libft) $(OBJS)
	@ar rvs $(NAME) $^

all: $(NAME)

clean:
	/bin/rm -rf $(LIBFT_ODIR)/*
	/bin/rm -rf $(PRINTF_ODIR)/*

fclean: clean
	/bin/rm -f $(NAME)

re: fclean all
