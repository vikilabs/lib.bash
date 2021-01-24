#Compiler
CC = arm-linux-gnueabihf-gcc
AR = arm-linux-gnueabihf-ar
STRIP = arm-linux-gnueabihf-strip

TARGET =libfio_common.a
OBJECT =fio_common.o

CP = cp
RM = rm -f
CFLAGS = -DDEBUG

#DEFINITIONS
DEFS = -DTRACES_VERIFICATION 
DEFS += -DDEBUG_TRACES

#Source Files
SOURCE_FILE = *.c

#LIBS to include
#LIBS = -ldl

OBJECT2=../bash_common/bash_common.o

all:
	$(CC) -c -Wall $(DEFS) ${CFLAGS} -o $(OBJECT) $(SOURCE_FILE) $(E_LIB_SRC) $(INC1) $(INC2) $(E_INC) ${LIBS} 
	$(AR) rcs $(TARGET) $(OBJECT) $(OBJECT2) 
