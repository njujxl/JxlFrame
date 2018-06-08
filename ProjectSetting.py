__author__ = 'Jiang.Xiaolong'

#项目参数设置
import sys, os, platform, re, string

from com_if import *

class QuickMDBVars(CompileVars):
    def __init__(self):
        CompileVars.__init__(self)
        self._env_params = [
        	['HOME', os.environ['HOME']],
            ['QMDB_HOME', os.environ['QuickMDB_HOME']],
			['SRCHOME', os.getcwd()],
			['ORACLE_HOME', os.environ['ORACLE_HOME']],
			['MYSQL_HOME', os.environ['MYSQL_HOME']],
            ]
        return

class QuickMDBCtrl(ControlVars):
    def __init__(self):
        ControlVars.__init__(self)
        self._params =[
        'mode     compile_mode debug  '.split(),
        'bits     object_mode  64     '.split(),
        'third    third_party  no     '.split(), #yes,no
		'db	   database	   oracle '.split(), #oracle,mysql
        ]
        self.build_home = '#../..'
        return


class CompileOptions(ShellSetVar):
    def __init__(self):
        ShellSetVar.__init__(self,QuickMDBCtrl(),QuickMDBVars())
        return
    def do_aix(self):
        self.vars.PLATFORM = 'IBM'
        return
    def do_sunos(self):
        self.vars.PLATFORM = 'SUN'
        return
    def do_linux(self):
        self.vars.PLATFORM = 'LINUX'
        return
    def do_hpux(self):
        self.vars.PLATFORM = 'HP'
        return
    def _default(self,env):
        assert(self == env['context'])
        suffix = env.Expand('.$(TRUESUFFIX)')
        if suffix:
            env.Replace(SHLIBSUFFIX=suffix)
            pass
        env.SetOptionCpp2Obj('$(CCC) -c $(CCFLAGS) $(LOCALINC)')
        return
    def _customize(self):
        self.make_incl_platform()
        self.make_incl()
        self.default_target_rule()
        return
    def make_incl_platform(self):
        '''
        这里翻译 makeall里面产生 变量到 Makefile.incl.platform 的逻辑
        注，里面的QuickMDB_HOME 被换为 QMDB_HOME
        '''
        #self.vars.SRCHOME = '#'
        #self.vars.PLATFORM
        self.vars.SetDefault('OBJECT_MODE',self.ctrl.bits)
        self.vars.COMPILE_MODE = 'DEBUG'
        self.vars.DATABASE = 'ORACLE'
        if self.ctrl.third == 'yes' and (self.ctrl.plat in ('linux','aix')):
            self.vars.THRID_PARTY_FLAG = '-DHAVE_READLINE'
            self.vars.THRID_PARTY_INC  = '-I$(QMDB_HOME)/mdb_thirdparty/include'
            self.vars.THRID_PARTY_LIB  = '-L$(QMDB_HOME)/lib -lreadline -lncurses'
            pass
        else:
            self.vars.THRID_PARTY_FLAG = ''
            self.vars.THRID_PARTY_INC  = ''
            self.vars.THRID_PARTY_LIB  = ''
            pass

        return

    def make_incl(self):
        '''
        这里翻译 Makefile.incl 里面定义变量的逻辑
        原来多行的要特殊处理
        AR 后面不能有 -o
        '''
        raw_text = r'''
			#############################
			# Application Dirs and Libs #
			#############################
			APPDIR           = $(SRCHOME)/App
			CONTROLDIR       = $(SRCHOME)/Control
			HELPERDIR        = $(SRCHOME)/Helper
			INTERFACEDIR     = $(SRCHOME)/Interface
			TOOLSDIR         = $(SRCHOME)/Tools
			REPLICATIONDIR   = $(SRCHOME)/Replication
			DBFLUSHDIR   = $(SRCHOME)/Dbflush
			AGENTDIR   = $(SRCHOME)/Agent
			
			OSDIR            = $(SRCHOME)
			FRAMEWORK_INC     = -I$(SRCHOME)/../BillingFramework/BillingSDK/include -I$(SRCHOME)/../BillingFramework/BillingNTC/include
			APP_INC = -I$(OSDIR)
			FRAMWORK_LIB = -L$(SRCHOME)/../lib -lBillingSDK -lBillingNTC			
			
			##############################
			# 32bit or 64bit object mode #
			##############################
			ORACLE_LIB32=lib32
			ORACLE_LIB64=lib
			
			#########################
			# Debug or Release mode #
			#########################
			COMPILE_DEBUG     = -g
			COMPILE_RELEASE   = -g -O 
			BASEFLAGS_DEBUG   =  -D_DEBUG $(TRACK_FLAG) $(THRID_PARTY_FLAG) -D_MDB_PERF 
			BASEFLAGS_RELEASE =  $(TRACK_FLAG) $(THRID_PARTY_FLAG)
			
			####################
			# PLATFORM SETTING #
			####################
			
			IBM_COMPILER = GNUC
			SUN_COMPILER = GNUC
			HP_COMPILER  = aCC
			LINUX_COMPILER= GNUC
			CYGWIN_COMPILER= GNUC
			
			IBM_CC	  = xlC
			SUN_CC	  = CC
			HP_CC     = aCC
			LINUX_CC  = g++
			CYGWIN_CC = g++
			
			SUN_AR   = CC -G -KPIC -DSYB_LP$(OBJECT_MODE) -m$(OBJECT_MODE) -D_REENTRANT -w  -DSIZEOF_LONG=8 -misalign -o
			IBM_AR   = xlC -q$(OBJECT_MODE) -G -qmkshrobj  -o
			HP_AR    = aCC -b +DD$(OBJECT_MODE) +u1  -o  
			LINUX_AR = g++ -shared -m$(OBJECT_MODE) -o 
			CYGWIN_AR= ar -rv
			
			IBM_LINKFLAGS   =  -q$(OBJECT_MODE) -brtl
			SUN_LINKFLAGS   = -DSYB_LP$(OBJECT_MODE) -KPIC -m$(OBJECT_MODE) -D_REENTRANT -w  -DSIZEOF_LONG=8 -misalign  
			HP_LINKFLAGS    = +DD$(OBJECT_MODE) -AA -mt -Wl,+as,mpas -Wl,+as,mpas -Wl,-w
			LINUX_LINKFLAGS = -m$(OBJECT_MODE)
			CYGWIN_LINKFLAGS=
			
			IBM_FLAGS   = -q$(OBJECT_MODE) -qstaticinline -bhalt:5 
			SUN_FLAGS   = -DSYB_LP$(OBJECT_MODE) -KPIC -m$(OBJECT_MODE) -D_REENTRANT -w  -DSIZEOF_LONG=8 -misalign -D_REENTRANT -w
			HP_FLAGS    = +Z +DD$(OBJECT_MODE) -AA -mt +u1 -DHP_UNIX -D_64_BIT_ -w -DOS_HP -D_BIG_ENDIAN_ -D_REENTRANT -Wl,+as,mpas -Wl,-w
			LINUX_FLAGS = -fPIC -m$(OBJECT_MODE) -Wall -Wformat=2
			CYGWIN_FLAGS=
			
			SUN_LIBS   = -ldl -lrt -lsocket
			IBM_LIBS   = -lpthread  -lm
			HP_LIBS	   = -lpthread
			LINUX_LIBS = -lutil
			CYGWIN_LIBS=
			
			SUN_TRUESUFFIX   = so
			IBM_TRUESUFFIX   = so
			HP_TRUESUFFIX	 = sl
			LINUX_TRUESUFFIX = so
			CYGWIN_TRUESUFFIX= dll
			
			####################################
			# 3rd Party Software INCs and LIBs #
			####################################
			SUN_ORACLEINC   = -I$(ORACLE_HOME)/rdbms/demo -I$(ORACLE_HOME)/rdbms/public $(ODBC_INCLUDE)
			SUN_ORACLELIBS   = -L$(ORACLE_HOME)/lib -lclntsh $(ODBC_LIB)
			SUN_MYSQLINC    = -I$(MYSQL_HOME)/include -I/usr/include/mysql
			SUN_MYSQLLIBS   = -L$(MYSQL_HOME)/lib$(OBJECT_MODE) -lmysqlclient -lrt -lpthread -L/usr/lib(OBJECT_MODE)/mysql -lmysqlclient -lrt -lpthread 
			
			#===============================================
			IBM_ORACLEINC   = -I$(ORACLE_HOME)/rdbms/demo -I$(ORACLE_HOME)/rdbms/public $(ODBC_INCLUDE)
			IBM_ORACLELIBS   = -L$(ORACLE_HOME)/$(ORACLE_LIB$(OBJECT_MODE)) -lclntsh $(ODBC_LIB)
			IBM_MYSQLINC    = -I$(MYSQL_HOME)/include -I/usr/include/mysql
			IBM_MYSQLIBS    = -L$(MYSQL_HOME)/lib$(OBJECT_MODE) -lmysqlclient -lrt -lpthread -L/usr/lib$(OBJECT_MODE)/mysql -lmysqlclient -lrt -lpthread 
			
			#===============================================
			HP_ORACLEINC   = -I$(ORACLE_HOME)/rdbms/demo -I$(ORACLE_HOME)/rdbms/public
			HP_ORACLELIBS   = -L$(ORACLE_HOME)/$(ORACLE_LIB$(OBJECT_MODE)) -lclntsh
			HP_MYSQLINC    = -I$(MYSQL_HOME)/include -I/usr/include/mysql
			HP_MYSQLLIBS   = -L$(MYSQL_HOME)/lib$(OBJECT_MODE) -lmysqlclient -lrt -lpthread -L/usr/lib$(OBJECT_MODE)/mysql -lmysqlclient -lrt -lpthread 
			
			#===============================================
			LINUX_ORACLEINC   = -I$(ORACLE_HOME)/rdbms/demo -I$(ORACLE_HOME)/rdbms/public
			LINUX_ORACLELIBS   = -L$(ORACLE_HOME)/$(ORACLE_LIB$(OBJECT_MODE)) -lclntsh
			LINUX_MYSQLINC    = -I$(MYSQL_HOME)/include -I/usr/include/mysql
			LINUX_MYSQLLIBS   = -L$(MYSQL_HOME)/lib$(OBJECT_MODE) -lmysqlclient -lrt -lpthread -L/usr/lib$(OBJECT_MODE)/mysql -lmysqlclient -lrt -lpthread
			
			#===============================================
			CYGWIN_ORACLEINC   = -I/usr/include/oracle
			CYGWIN_ORACLELIBS   = -L/lib/oracle -loci
			CYGWIN_MYSQLINC    = -I$(MYSQL_HOME)/include -I/usr/include/mysql
			CYGWIN_MYSQLLIBS   = -L$(MYSQL_HOME)/lib$(OBJECT_MODE) -lmysqlclient -lrt -lpthread -L/usr/lib$(OBJECT_MODE)/mysql -lmysqlclient -lrt -lpthread 
			
			#===============================================
			
			#########################
			# Choose Platform param #
			#########################
			CCC	     = $($(PLATFORM)_CC)
			LLDFLAGS = $($(PLATFORM)_LINKFLAGS)
			AR       = $($(PLATFORM)_AR)
			COMPILER = $($(PLATFORM)_COMPILER)
			
			DATABASE_INC  = $($(PLATFORM)_$(DATABASE)INC)
			DATABASE_LIBS = $($(PLATFORM)_$(DATABASE)LIBS)
			TRUESUFFIX    = $($(PLATFORM)_TRUESUFFIX)
			
			LONGSIZE = LONG$(OBJECT_MODE)
			CCFLAGS	 = $(COMPILE_$(COMPILE_MODE)) -D$(COMPILER) -D$(LONGSIZE) -DNO_DEBUG_NEW $(BASEFLAGS_$(COMPILE_MODE)) -DOS_$(PLATFORM) -D_$(PLATFORM) -D_$(DATABASE) $($(PLATFORM)_FLAGS) -DDB_$(DATABASE)
			
			LOCALINC = $(APP_INC) $(DATABASE_INC)  $(FRAMEWORK_INC) $(THRID_PARTY_INC)
			LOCALLIB = $(APP_LIB) $(DATABASE_LIBS) $($(PLATFORM)_LIBS)  $(FRAMWORK_LIB) $(THRID_PARTY_LIB)
        '''
        #上面 APP_LIB 定制一下
        self.vars.APP_LIB = '''
            -L$(AGENTDIR)          -lmdbAgent
            -L$(CONTROLDIR)        -lmdbControl
            -L$(HELPERDIR)         -lmdbHelper
            -L$(INTERFACEDIR)      -lmdbInterface
            -L$(DBFLUSHDIR)        -lmdbDbFlush
            -L$(REPLICATIONDIR)    -lmdbReplication
            -L$(TOOLSDIR)          -lmdbTools
            -L$(APPDIR)            -lmdbApp
        '''

        self.vars.SetBulk(raw_text)
        return

    def default_target_rule(self):
        self.ctrl.swig_option = ''
        sLine = '$(CCC) -c $(CCFLAGS) -c $(LOCALINC)'
        self.ctrl.cc  = self.vars.expand(sLine)
        self.ctrl.cxx = self.vars.expand(sLine)
        sLine = '$(CCC) $(LLDFLAGS) $(LOCALLIB) $(APP_LIB)'
        self.ctrl.link = self.vars.expand(sLine)
        #连接库
        sLine = '$(CCC) $(LLDFLAGS) $(LOCALLIB)'
        self.ctrl.shlink = self.vars.expand(sLine)
        return

