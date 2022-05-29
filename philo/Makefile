NAME 	=	philo

CFILES	=	philo.c src/valid.c src/inits.c\
			src/utils.c src/times.c src/conditions.c\
			src/actions.c src/cleaner.c

OBJECTS	= $(CFILES:.c=.o)

D_FILES =	$(patsubst %.c,%.d,$(CFILES))

CC = cc

CFLAGS = -Wall -Wextra -pthread -O2

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
