include ../Makefile.incl

clean:
	rm -f *.o  libjxlCommon.$(TRUESUFFIX) 

ALL_OBJS=jxlOS.o jxlProcess.o jxlThread.o jxlLog.o jxlRand.o

ALL_EXES= 
					
all_objs: $(ALL_OBJS)

all:	$(ALL_OBJS) 
	$(AR) libjxlCommon.$(TRUESUFFIX)  $(ALL_OBJS) 
		
build: $(ALL_EXES)

install: all
	cp -rf *.$(TRUESUFFIX)  $(SRCHOME)/lib

