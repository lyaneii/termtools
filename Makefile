NAME = libtermtools.a

CFLAGS = -Wall -Wextra -Werror

INCLUDE = -I./include

SRC =	ttools_attributes.c \
		ttools_cursor.c \
		ttools_draw.c \
		ttools_mouse_buttons.c \
		ttools_mouse.c \
		ttools_terminal.c

DIR_SRC = src
DIR_OBJ = obj

SRC := ${addprefix ${DIR_SRC}/, ${SRC}}

OBJ = ${subst ${DIR_SRC}/, ${DIR_OBJ}/, ${SRC:.c=.o}}

${NAME}: ${OBJ}
	ar rcs ${NAME} ${OBJ}

${OBJ}: ${DIR_OBJ}/%.o: ${DIR_SRC}/%.c
	@mkdir -p ${@D}
	cc ${CFLAGS} ${INCLUDE} -c $< -o $@

demo:
	cc ${CFLAGS} ${INCLUDE} demo/demo.c -L. -ltermtools -o demo/termtools_demo

clean:
	rm -f ${OBJ}

fclean: clean
	rm -f ${NAME}

all: ${NAME}

re: fclean all

.PHONY: clean fclean all re demo
