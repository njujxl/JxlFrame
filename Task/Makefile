include ../Makefile.incl

clean:
	rm -f *.o libjxlTask.$(TRUESUFFIX) 

#ALL_OBJS= insertJob.o updateJob.o deleteJob.o jxlJob.o
#ALL_EXES= insertTask.exe updateTask.exe deleteTask.exe jxlTask.exe
ALL_OBJS= jxlJob.o
ALL_EXES= jxlTask.exe
					
all_objs: $(ALL_OBJS)

all:	$(ALL_OBJS) 
	$(AR) libjxlTask.$(TRUESUFFIX)  $(ALL_OBJS)
build: $(ALL_EXES)
	#cp insertTask $(SRCHOME)/bin
	#cp updateTask $(SRCHOME)/bin
	#cp deleteTask $(SRCHOME)/bin
	cp jxlTask $(SRCHOME)/bin

install: all
	cp -rf *.$(TRUESUFFIX)  /home/jxl/JxlFrame/lib

