NAME		=	philo

SRCS		=	main.c

OBJS		=	$(SRCS:.c=.o)

INCLUDES	=	-Iincludes

CC			=	gcc

CFLAGS		=	-Wall -Wextra -Werror

RM			=	rm -f

all : $(NAME)

$(NAME) : $(OBJS)
		$(CC) $(OBJS) -o $(NAME)

%.o : %.c
		$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

norm:
		@norminette ./*.c includes/*.h

clean:
		@$(RM) $(OBJS)
		@echo "\033[1;38;5;221m*  Philo objects removed\033[0m"

fclean:	clean
		@$(RM) $(NAME)
		@rm -rf *.dSYM 
		@echo "\033[1;38;5;221m*  Philo program removed\033[0m"

re:		fclean all

.PHONY: all clean fclean re norm bonus
