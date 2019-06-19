# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kehuang <kehuang@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/01/25 12:25:43 by kehuang           #+#    #+#              #
#    Updated: 2019/06/19 19:18:06 by kehuang          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.DEFAULT_GOAL			:=			all
ROOT					:=			$(shell pwd)

ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

NAME					:=			libft_malloc_$(HOSTTYPE).so
NAME_LINK				:=			libft_malloc.so

#==============================================================================#
#------------------------------------------------------------------------------#
#                                 COLOR                                        #

C_X						:=			\033[0m
C_R						:=			\033[31m
C_Y						:=			\033[33m
C_C						:=			\033[36m

#==============================================================================#
#------------------------------------------------------------------------------#
#                               DIRECTORIES                                    #

INC_DIR					:=			./includes
TEST_DIR				:=			./tests
OBJ_DIR					:=			./objs

#==============================================================================#
#------------------------------------------------------------------------------#
#                            COMPILER & FLAGS                                  #

CC						:=			gcc
CFLAGS					:=			-Wall -Wextra -Werror
LFLAGS					:=			-shared

ifneq ($(DEBUG),)
OBJ_DIR					:=			./debug
CFLAGS					+=			-g3
else
  ifneq ($(DEV),)
  OBJ_DIR				:=			./dev
  CFLAGS				+=			-g3
  CFLAGS				+=			-O0 -std=c99 \
  									-Wchar-subscripts -Wparentheses \
									-Wsequence-point -Winline \
									-Wdisabled-optimization
  endif
endif

#==============================================================================#
#------------------------------------------------------------------------------#
#                                  FILES                                       #

#-----------#
#    ROOT   #

SRC_DIR					:=			./src

INC_NAME				:=			ft_malloc_int.h			\
									malloc.h				\

SRC_NAME				:=			ft_calloc.c				\
									ft_free.c				\
									ft_malloc.c				\
									ft_realloc.c			\
									show_alloc_mem.c		\

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(addprefix $(SRC_DIR)/,$(INC_NAME))
	@$(CC) $(CFLAGS) -c $< -o $@ -I$(INC_DIR)
	@printf "${C_C}%s${C_X} :: ${C_R}%s${C_X}\n" $(NAME) $@

OBJS					:=			$(addprefix $(OBJ_DIR)/,$(SRC_NAME:.c=.o))

#-----------#
#   UTILS   #

SRC_UTILS_DIR			:=			utils

INC_UTILS_NAME			:=			utils.h					\

SRC_UTILS_NAME			:=			ft_memcpy.c				\
									ft_memset.c				\

OBJS					+=			$(addprefix $(OBJ_DIR)/,$(SRC_UTILS_NAME:.c=.o))

$(OBJ_DIR)/%.o: $(SRC_DIR)/$(SRC_UTILS_DIR)/%.c $(addprefix $(SRC_DIR)/$(SRC_UTILS_DIR)/,$(INC_UTILS_NAME))
	@$(CC) $(CFLAGS) -c $< -o $@ -I$(INC_DIR)
	@printf "${C_C}%s${C_X} :: ${C_R}%s${C_X}\n" $(NAME) $@

#   FT_PRINTF

SRC_FT_PRINTF_DIR		:=			ft_printf

INC_FT_PRINTF_NAME		:=			ft_printf.h				\
									ft_printf_int.h			\

SRC_FT_PRINTF_NAME		:=			ft_pf.c					\
									ft_pf_buf.c				\
									c_conv.c				\
									id_conv.c				\
									p_conv.c				\
									s_conv.c				\
									u_conv.c				\
									x__conv.c				\
									x_conv.c				\

OBJS					+=			$(addprefix $(OBJ_DIR)/,$(SRC_FT_PRINTF_NAME:.c=.o))

$(OBJ_DIR)/%.o: $(SRC_DIR)/$(SRC_UTILS_DIR)/$(SRC_FT_PRINTF_DIR)/%.c $(addprefix $(SRC_DIR)/$(SRC_UTILS_DIR)/$(SRC_FT_PRINTF_DIR)/,$(INC_FT_PRINTF_NAME))
	@$(CC) $(CFLAGS) -c $< -o $@ -I$(INC_DIR)
	@printf "${C_C}%s${C_X} :: ${C_R}%s${C_X}\n" $(NAME) $@

#==============================================================================#
#------------------------------------------------------------------------------#
#                                 RULES                                        #

all:					$(NAME)
.PHONY: all

$(NAME):				$(OBJ_DIR) $(OBJS)
	@$(CC) $(LFLAGS) $(CFLAGS) -o $(NAME) $(OBJS) -I$(INC_DIR)
	@printf '${C_Y}[ READY ] ${C_C}$(NAME)${C_Y} ---\n${C_X}'
	@$(MAKE) $(NAME_LINK)

$(NAME_LINK):
	@ln -sf $(NAME) $(NAME_LINK)
	@printf '${C_Y}[ READY ] ${C_C}$(NAME_LINK)${C_Y} ---\n${C_X}'

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

clean:
	@rm -rf $(OBJ_DIR)
	@printf '${C_Y}[ KILL ] ${C_C}$(NAME)${C_Y} Clean ${C_R}$(OBJ_DIR)${C_Y} ---\n${C_X}'
.PHONY: clean

fclean:
	@$(MAKE) clean
	@rm -f $(NAME_LINK)
	@rm -f $(NAME)
	@printf '${C_Y}[ KILL ] ${C_C}$(NAME)${C_Y} Flean ---\n${C_X}'
.PHONY: fclean

re:
	@$(MAKE) fclean
	@$(MAKE)
.PHONY: re

delete:
	@$(MAKE) fclean
	@$(MAKE) DEV="1" fclean
	@$(MAKE) DEBUG="1" fclean
.PHONY: delete

pclean:
	@rm -rf $(OBJ_DIR)
	@printf '${C_Y}[ KILL ] ${C_C}$(NAME)${C_Y} Clean ${C_R}$(OBJ_DIR)${C_Y} ---\n${C_X}'
	@rm -f $(NAME)
	@printf '${C_Y}[ KILL ] ${C_C}$(NAME)${C_Y} Flean ---\n${C_X}'
	@rm -f $(NAME_LINK)
	@printf '${C_Y}[ KILL ] ${C_C}$(NAME_LINK)${C_Y} Flean ---\n${C_X}'

ra:
	@$(MAKE) pclean
	@$(MAKE)
.PHONY: ra

run test t: $(NAME) $(TEST_BIN_DIR) $(TEST_OBJ)
	@find $(ROOT)/$(TEST_DIR) -name "*.c" \
		-exec gcc {} -o {}.unit.out $(NAME_LINK) -I$(INC_DIR) \;
	@find -s $(ROOT)/$(TEST_DIR) -name "*.unit.out" \
		-exec $(ROOT)/run.sh {} \;
	@rm -f $(ROOT)/$(TEST_DIR)/**/*.unit.out

build dist:
	mkdir -p $(TEST_DIR)/bin
	find $(TEST_DIR) -name "*.c" \
		-exec gcc {} -o {}.unit.out objs/c_conv.o objs/ft_memcpy.o objs/ft_memset.o objs/ft_pf.o objs/ft_pf_buf.o objs/ft_realloc.o objs/id_conv.o objs/p_conv.o objs/s_conv.o objs/show_alloc_mem.o objs/u_conv.o objs/x__conv.o objs/x_conv.o -I$(INC_DIR) \;
	find $(TEST_DIR) -name "*.unit.out" \
		-exec mv {} $(TEST_DIR)/bin \;


main: main.c
	@$(CC) -o a.out main.c -I$(INC_DIR)
	@./a.out
	@rm -f a.out
