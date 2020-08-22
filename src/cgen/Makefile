
ASSN = 5
CLASS= cs143
CLASSDIR= ../..
LIB= -L/usr/pubsw/lib
AR= gar
ARCHIVE_NEW= -cr
RANLIB= gar -qs

SRC= cgen.cc cgen.h cgen_supp.cc cool-tree.h cool-tree.handcode.h emit.h example.cl README
CSRC= cgen-phase.cc utilities.cc stringtab.cc dumptype.cc tree.cc cool-tree.cc ast-lex.cc ast-parse.cc handle_flags.cc \
		code-container.cc memory.cc activation-record.cc memory-manager.cc ancestors-table.cc methods-table.cc \
		static-memory.cc object-prototype.cc filter-features.cc propagate-class.cc node-children.cc install-basic-classes.cc \
		inheritance-graph.cc init-static-memory.cc min-tmps.cc
TST= unit-test.cc utilities.cc stringtab.cc dumptype.cc tree.cc cool-tree.cc ast-lex.cc ast-parse.cc handle_flags.cc \
		code-container.cc memory.cc activation-record.cc memory-manager.cc ancestors-table.cc methods-table.cc \
		static-memory.cc object-prototype.cc filter-features.cc propagate-class.cc node-children.cc install-basic-classes.cc \
		inheritance-graph.cc init-static-memory.cc min-tmps.cc
		
		
TSRC= mycoolc
CGEN=
HGEN= 
LIBS= lexer parser semant
CFIL= cgen.cc cgen_supp.cc ${CSRC} ${CGEN}
TFIL= cgen.cc cgen_supp.cc ${TST} ${CGEN}
LSRC= Makefile
OBJS= ${CFIL:.cc=.o}
TOBJS = ${TFIL:.cc=.o} 
OUTPUT= good.output bad.output


CPPINCLUDE= -I. -I${CLASSDIR}/include/cgen -I${CLASSDIR}/src/cgen


FFLAGS = -d8 -ocool-lex.cc
BFLAGS = -d -v -y -b cool --debug -p cool_yy

CC=g++
CFLAGS=-g -Wall -Wno-unused -Wno-write-strings -Wno-deprecated ${CPPINCLUDE} -DDEBUG
FLEX=flex ${FFLAGS}
BISON= bison ${BFLAGS}
DEPEND = ${CC} -MM ${CPPINCLUDE}

source: ${SRC} ${TSRC} ${LIBS} lsource

lsource: ${LSRC}

${OUTPUT}:	cgen
	@rm -f ${OUTPUT}
	./mycoolc  example.cl >example.output 2>&1 

compile:	cgen change-prot

change-prot:
	@-chmod 660 ${SRC} ${OUTPUT}

test: 	${TOBJS} parser semant
		${CC} ${CFLAGS} ${TOBJS} ${LIB} -o test
cgen:	${OBJS} parser semant
	${CC} ${CFLAGS} ${OBJS} ${LIB} -o cgen

.cc.o:
	${CC} ${CFLAGS} -c $<

dotest:	cgen example.cl
	@echo "\nRunning code generator on example.cl\n"
	-./mycoolc example.cl

${LIBS}:
	${CLASSDIR}/etc/link-object ${ASSN} $@

${TSRC} ${CSRC}:
	-ln -s ${CLASSDIR}/src/cgen/$@ $@

${HSRC}:
	-ln -s ${CLASSDIR}/include/cgen/$@ $@

clean :
	-rm -f ${OUTPUT} *.s core ${OBJS} cgen parser semant lexer *~ *.a *.o

clean-compile:
	@-rm -f core ${OBJS} ${LSRC}

%.d: %.cc ${SRC}
	${SHELL} -ec '${DEPEND} $< | sed '\''s/\($*\.o\)[ :]*/\1 $@ : /g'\'' > $@'

-include ${CFIL:.cc=.d}


