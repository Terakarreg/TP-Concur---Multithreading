INT=main.h 
INT1=gene.h
REAL=$(INT:.h=.c)
OBJ=$(INT:.h=.o)
REAL1=$(INT1:.h=.c)
OBJ1=$(INT1:.h=.o)
COMP=gcc
CPPFLAGS=#-Wall -DMAP
LINK=gcc
LINKFLAGS=
EXE=Thread
EXE1=Gene
CLEAR=clear
LIBS=-lpthread
ECHO=@echo
RM=rm
RMFLAGS=-f
INCPATH=#-I-I
LIBPATH=#-L-L


.PHONY : $(CLEAR)

$(CLEAR):
	$(ECHO) "destruction de $(OBJ) $(EXE)"
	$(RM) $(RMFLAGS) -f $(OBJ) $(EXE) core

main.o: main.c

gene.o: gene.c

%.o: %.cpp 
	$(ECHO) "compil de $@ depuis $^"
	$(COMP) $(CPPFLAGS) -c $<

$(EXE): $(OBJ)
	$(ECHO) "EDL de $@ depuis $(OBJ)"
	$(LINK) $(LINKFLAGS) -o $@ $(OBJ) $(LIBS)

$(EXE1): $(OBJ1)
	$(ECHO) "EDL de $@ depuis $(OBJ1)"
	$(LINK) $(LINKFLAGS) -o $@ $(OBJ1)





