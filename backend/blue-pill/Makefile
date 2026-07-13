OUT = img.bin

OBJ = start.o

CFLAGS  = -mcpu=cortex-m0 -mthumb -Wall -Wextra -Werror -Wpedantic
LDFLAGS = -T link.ld

CC = arm-none-eabi-gcc
LD = arm-none-eabi-ld

all: build

.PHONY: build
build: ${OUT}

.PHONY: clean
clean:
	rm -f ${OUT} ${OBJ}

${OUT}: ${OBJ}
	${LD} ${LDFLAGS} -o ${OUT} ${OBJ}

%.o: %.c
	${CC} ${CFLAGS} -c -o $@ $^

%.o: %.S
	${CC} ${CFLAGS} -c -o $@ $^
