include ../Makefile.incl

clean:
	rm -f *.o  libjxlApp.$(TRUESUFFIX) 

ALL_OBJS= JxlFrame.o
ALL_EXES= JxlFrame.exe
					
all_objs: $(ALL_OBJS)

all:	$(ALL_OBJS) 
	$(AR) libjxlApp.$(TRUESUFFIX)  $(ALL_OBJS) 
		
build: $(ALL_EXES)
	cp JxlFrame $(SRCHOME)/bin

install: all
	cp -rf *.$(TRUESUFFIX)  $(SRCHOME)/lib

