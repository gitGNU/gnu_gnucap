#sample makefile to generate strcmp.so alias.so version.so shared object files
CC=g++ 
CFLAGS=-shared -fPIC -o

all:c_alias_unalias.so \
	c_def_undef.so \
	c_echo.so \
	c_history.so \
	c_mdump.so \
	c_colon_comand.so \
	c_quit.so \
	c_rmcirc.so \
	c_shell.so \
	c_strcmp.so \
	c_sysinfo.so \
        c_version.so

c_alias_unalias.so : c_alias_unalias.cc
	$(CC) $(CFLAGS) c_alias_unalias.so c_alias_unalias.cc

c_def_undef.so : c_def_undef.cc
	$(CC) $(CFLAGS) c_def_undef.so c_def_undef.cc

c_echo.so : c_echo.cc
	$(CC) $(CFLAGS) c_echo.so c_echo.cc

c_history.so : c_history.cc
	$(CC) $(CFLAGS) c_history.so c_history.cc

c_mdump.so : c_mdump.cc
	$(CC) $(CFLAGS) c_mdump.so c_mdump.cc

c_colon_comand.so : c_colon_comand.cc
	$(CC) $(CFLAGS) c_colon_comand.so c_colon_comand.cc

c_quit.so : c_quit.cc
	$(CC) $(CFLAGS) c_quit.so c_quit.cc

c_rmcirc.so : c_rmcirc.cc
	$(CC) $(CFLAGS) c_rmcirc.so c_rmcirc.cc

c_shell.so : c_shell.cc
	$(CC) $(CFLAGS) c_shell.so c_shell.cc

c_strcmp.so : c_strcmp.cc
	$(CC) $(CFLAGS) c_strcmp.so c_strcmp.cc

c_sysinfo.so : c_sysinfo.cc
	$(CC) $(CFLAGS) c_sysinfo.so c_sysinfo.cc

c_version.so : c_version.cc
	$(CC) $(CFLAGS) c_version.so c_version.cc













 
	
