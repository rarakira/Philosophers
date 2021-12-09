NAME		=	philo_bonus

SRCS		=	main.c				forks.c				\
				philos.c			philos_utils.c		\
				philo_eats.c		printf_msgs.c		\
				philo_activities.c	monitoring.c		\
				clean_and_free.c	lib.c

OBJS		=	$(SRCS:.c=.o)

INCLUDES	=	-Iincludes

CC			=	gcc

CFLAGS		=	-Wall -Wextra -Werror

RM			=	rm -f

all : $(NAME)

$(NAME) : $(OBJS)
		$(CC) $(OBJS) -o $(NAME)

%.o : %.c includes/philo_bonus.h
		$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

norm:
		@norminette ./*.c includes/*.h

clean:
		@$(RM) $(OBJS)
		@echo "\033[1;38;5;221m*  Philo_bonus objects removed\033[0m"

fclean:	clean
		@$(RM) $(NAME)
		@rm -rf *.dSYM
		@echo "\033[1;38;5;221m*  Philo_bonus program removed\033[0m"

re:		fclean all

.PHONY: all clean fclean re norm
