CC		=cc
LIBS	=
LINKS	=
CFLAGS	=-Wall -Werror -Wextra -Iinclude
NAME	=philo
C_FILES	=src/main.c \
		 src/tools/args.c \
		 src/tools/preparation.c \
		 src/tools/philo.c \
		 src/philo.c \
		 src/tools/lib.c \
		 src/tools/time.c \

outer_clean:

outer_fclean:
