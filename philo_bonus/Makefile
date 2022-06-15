NAME 	=	philo_bonus

CFILES	=	philo_bonus.c\
 			src/valid_bonus.c\
 			src/inits_bonus.c\
 			src/times_bonus.c\
			src/utils_bonus.c\
			src/conditions_bonus.c\
			src/actions_bonus.c

OBJECTS	=	$(CFILES:.c=.o)

D_FILES	=	$(patsubst %.c,%.d,$(CFILES))

CC = cc

CFLAGS = -Wall -Wextra -Werror -pthread

.PHONY	:	all clean fclean re

all		:	$(NAME)

$(NAME)	:	$(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $(NAME)

%.o 	:	%.c Makefile
	$(CC) $(CFLAGS) -c $< -o $@ -MD


include $(wildcard $(D_FILES))

clean	:
	rm -f $(OBJECTS) $(D_FILES)

fclean	:	clean
	rm -f $(NAME)

re		:	fclean all
