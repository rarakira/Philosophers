NAME		=	philo

SRCS		=	main.c				forks.c				\
				philos.c			philos_utils.c		\
				philo_eats.c		philo_activities.c	\
				monitoring.c							\
				clean_and_free.c	lib.c

PRINTERS		=	print_msgs.c		\
				print_buff_msgs.c	printf_msgs.c		\

OBJS		=	$(SRCS:.c=.o)
OBJS_PRINTERS		=	$(PRINTERS:.c=.o)

INCLUDES	=	-Iincludes

CC			=	gcc

CFLAGS		=	-Wall -Wextra -Werror

RM			=	rm -f

all : $(NAME)

$(NAME) : $(OBJS) $(OBJS_PRINTERS)
		$(CC) $(OBJS) print_buff_msgs.o -o $(NAME)

printf : $(OBJS) $(OBJS_PRINTERS)
		$(CC) $(OBJS) printf_msgs.o -o $(NAME)

putnbr : $(OBJS) $(OBJS_PRINTERS)
		$(CC) $(OBJS) print_msgs.o -o $(NAME)

%.o : %.c includes/philo.h
		$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

norm:
		@norminette ./*.c includes/*.h

clean:
		@$(RM) $(OBJS) $(OBJS_PRINTERS)
		@echo "\033[1;38;5;221m*  Philo objects removed\033[0m"

fclean:	clean
		@$(RM) $(NAME)
		@rm -rf *.dSYM
		@echo "\033[1;38;5;221m*  Philo program removed\033[0m"

re:		fclean all

.PHONY: all clean fclean re norm bonus
