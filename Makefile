TYPE:=int
OPT:=

CXX = u++						# compiler
CXXFLAGS = -g -multi -Wall -Wno-unused-label -MMD ${OPT} # compiler flags
MAKEFILE_NAME = ${firstword ${MAKEFILE_LIST}}	# makefile name

OBJECTS = q1mapper.o q1reducer.o q1sortmapper.o q1sortreducer.o q1kvqueue.o q1main.o# list of object files prefixed with "q1"
EXEC = wordcount

DEPENDS = ${OBJECTS:.o=.d}

#############################################################

.PHONY : all clean

all : ${EXECS}						# build all executables

${EXEC} : ${OBJECTS}					# link step 1st executable
	${CXX} ${CXXFLAGS} $^ -o $@

#############################################################

${OBJECTS} : ${MAKEFILE_NAME}				# OPTIONAL : changes to this file => recompile

-include ${DEPENDS}					# include *.d files containing program dependences

clean :							# remove files that can be regenerated
	rm -f *.d *.o ${EXECS} ImplType
