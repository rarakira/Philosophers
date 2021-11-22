NAME		=	philo

SRCS		=	main.c				forks.c				\
				philos.c			philos_utils.c		\
				philo_activities.c	monitoring.c		\
				clean_and_free.c	lib.c

CUSTOM		=	philo_eats.c		philo_eats_mtxs.c	\
				print_msgs.c		printf_msgs.c		\
				print_buff_msgs.c						\

OBJS		=	$(SRCS:.c=.o)
OBJS_CUSTOM		=	$(CUSTOM:.c=.o)

INCLUDES	=	-Iincludes

CC			=	gcc

CFLAGS		=	-Wall -Wextra -Werror

RM			=	rm -f

all : $(NAME)

# buffered printer, forks with status #
$(NAME) : $(OBJS) $(OBJS_CUSTOM)
		$(CC) $(OBJS) print_buff_msgs.o philo_eats.o -o $(NAME)

# printf printer, forks with status #
printf : $(OBJS) $(OBJS_CUSTOM)
		$(CC) $(OBJS) printf_msgs.o philo_eats.o -o $(NAME)

# buffered printer, forks-mtxs #
buff_mxs : $(OBJS) $(OBJS_CUSTOM)
		$(CC) $(OBJS) print_buff_msgs.o philo_eats_mtxs.o -o $(NAME)

# printf printer, forks-mtxs #
printf_mxs : $(OBJS) $(OBJS_CUSTOM)
		$(CC) $(OBJS) printf_msgs.o philo_eats_mtxs.o -o $(NAME)

putnbr : $(OBJS) $(OBJS_CUSTOM)
		$(CC) $(OBJS) print_msgs.o philo_eats.o -o $(NAME)

%.o : %.c includes/philo.h
		$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

norm:
		@norminette ./*.c includes/*.h

clean:
		@$(RM) $(OBJS) $(OBJS_CUSTOM)
		@echo "\033[1;38;5;221m*  Philo objects removed\033[0m"

fclean:	clean
		@$(RM) $(NAME)
		@rm -rf *.dSYM
		@echo "\033[1;38;5;221m*  Philo program removed\033[0m"

re:		fclean all

.PHONY: all clean fclean re norm bonus
