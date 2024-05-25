NAME = libtermtools.a

CFLAGS = -Wall -Wextra -Werror

LINKS = -L. -ltermtools

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

demo_drawing: demo/demo_drawing.c
	cc ${CFLAGS} ${INCLUDE} $< ${LINKS} -o $@

demo_rays: demo/demo_rays.c
	cc ${CFLAGS} ${INCLUDE} $< ${LINKS} -o $@

clean:
	rm -f ${OBJ}

fclean: clean
	rm -f ${NAME}

all: ${NAME}

re: fclean all

.PHONY: clean fclean all re
