CC=gcc
CCFLAGS=-Wall -g -c

LDFLAGS=
MODULES=clothsim app renderer logger linalg
OBJDIR=./obj
OBJS= ${addprefix ${OBJDIR}/, ${addsuffix .o, ${MODULES}}}
LIBS=-lSDL2 -lm 
INCLUDE=-I.

APP_IMPL=./impl/app/app_sdl.c
RENDERER_IMPL=./impl/renderer/renderer_sdl.c

build: clothsim

clothsim: ${OBJS}
	${CC} ${LDFLAGS} -o $@ ${OBJS} ${LIBS} ${INCLUDE} 

${OBJDIR}/renderer.o : ${RENDERER_IMPL} renderer.h
	@mkdir -p ${dir $@}
	@echo $@
	${CC} ${CCFLAGS} ${LIBS} ${INCLUDE} $< -D_GNU_SOURCE -o $@


${OBJDIR}/app.o : ${APP_IMPL} app.h
	@mkdir -p ${dir $@}
	@echo $@
	${CC} ${CCFLAGS} ${LIBS} ${INCLUDE} $< -D_GNU_SOURCE -o $@

${OBJDIR}/%.o : %.c %.h
	@mkdir -p ${dir $@}
	@echo $@
	${CC} ${CCFLAGS} ${LIBS} ${INCLUDE} $< -D_GNU_SOURCE -o $@


clean:
	rm -rf ${OBJDIR}