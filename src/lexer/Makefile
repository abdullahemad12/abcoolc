
ASSN = 2
CLASS= cs143
CLASSDIR= ../..
LIB= 

SRC= cool.flex test.cl README 
CSRC= lextest.cc utilities.cc stringtab.cc handle_flags.cc
TSRC= mycoolc
HSRC= 
CGEN= cool-lex.cc
HGEN=
LIBS= parser semant cgen
CFIL= ${CSRC} ${CGEN}
LSRC= Makefile
OBJS= ${CFIL:.cc=.o}
OUTPUT= test.output
MYTEST= mytest.cl

CPPINCLUDE= -I. -I${CLASSDIR}/include/lexer -I${CLASSDIR}/src/lexer


FFLAGS= -d -ocool-lex.cc

CC=g++
CFLAGS= -g -Wall -Wno-unused -Wno-write-strings ${CPPINCLUDE}
FLEX=flex ${FFLAGS}
DEPEND = ${CC} -MM ${CPPINCLUDE}

test: 
	perl pa1-grading.pl

source : ${SRC} ${TSRC} ${LSRC} ${LIBS} lsource

lsource: ${LSRC}

${OUTPUT}:	lexer test.cl
	@rm -f test.output
	-./lexer test.cl >test.output 2>&1 

lexer: ${OBJS}
	${CC} ${CFLAGS} ${OBJS} ${LIB} -o lexer

.cc.o:
	${CC} ${CFLAGS} -c $<

cool-lex.cc: cool.flex 
	${FLEX} cool.flex

dotest:	lexer test.cl
	./lexer test.cl

mytest:
	if [ "`../../bin/lexer mytest.cl`" == "`./lexer mytest.cl`" ]; then \
		echo "Test Passed"; \
	else \
		echo "Test Failed"; \
	fi;\
	
${LIBS}:
	${CLASSDIR}/etc/link-object ${ASSN} $@

${TSRC} ${CSRC}:
	-ln -s ${CLASSDIR}/src/lexer/$@ $@

${HSRC}:
	-ln -s ${CLASSDIR}/include/lexer/$@ $@

clean :
	-rm -f ${OUTPUT} *.s core ${OBJS} lexer cool-lex.cc *~ parser cgen semant

clean-compile:
	@-rm -f core ${OBJS} cool-lex.cc ${LSRC}
	

%.d: %.cc ${SRC} ${LSRC}
	${SHELL} -ec '${DEPEND} $< | sed '\''s/\($*\.o\)[ :]*/\1 $@ : /g'\'' > $@'

-include ${CFIL:.cc=.d}


