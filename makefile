RM=rm -rf
CC=gcc

C_SRCS=$(shell find . -iname "*.c" | tr '\n' ' ')
H_SRCS=$(shell find . -iname "*.h" | tr '\n' ' ')
OBJS=$(C_SRCS:./%.c=build/%.o)

all: build/so-ensamblador

create-dirs:
	@mkdir -p build

#Crear directorios y terminar de compilar el exe
build/so-ensamblador: create-dirs $(OBJS)
	@echo "Compilando so-ensamblador"
	@$(CC) -Wall  -o "build/so-ensamblador" $(OBJS)

#Compilar en objetos
build/%.o: %.c
	@echo 'Compilando $<'
	@$(CC)  -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"

#Compilar como Debug
debug: CC += -DDEBUG -g3
debug: all

# Clean build files
clean:
	@echo 'Borrando direcctorio /build'
	@$(RM) build

.PHONY: all create-dirs clean