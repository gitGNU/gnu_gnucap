/*                               -*- C++ -*-
 * Copyright (C) 2007 Albert Davis
 * Author: Albert Davis <aldavis@gnu.org>
 *
 * This file is part of "Gnucap", the Gnu Circuit Analysis Package
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
 * 02110-1301, USA.
 *------------------------------------------------------------------
 */
#include "e_cardlist.h"
#include "c_comand.h"
//#include "constant.h"
#include "globals.h"
#include <sys/stat.h>
#include <libgen.h> //basename, dirname
//#include <sys/types.h>
#include <sys/wait.h>
/*--------------------------------------------------------------------------*/
// lets assume 26 is the interface and 138 is some sort of revision
// eventually, SOME_NUMBER might become the distance to the last gittag?
#define SOME_NUMBER "138"
#define PATCHLEVEL "0.0.0 GIT 0xcdc260d." SOME_NUMBER

// needed?
#define HAVE_GIT_REPO 1

static const unsigned iv = 0xcdc260d;
static const char* in = "gnucap-uf";
extern "C" {
unsigned interface_version(){return iv;}
const char* interface_name(){return in;}
}
/*--------------------------------------------------------------------------*/
namespace {
/*--------------------------------------------------------------------------*/
std::map<const std::string, void*> attach_list;
/*--------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------*/
class CMD_ATTACH : public CMD {
  static void compile(std::string& filename, std::string source);
  static void* do_attach(std::string filename, int flags, bool force=false);
public:
  void do_it(CS& cmd, CARD_LIST*)
  {
    unsigned here = cmd.cursor();
    int dl_scope = RTLD_LOCAL;
    int check = RTLD_NOW;
    bool force = false;
    // RTLD_NOW means to resolve symbols on loading
    // RTLD_LOCAL means symbols defined in a plugin are local
    do {
      if (cmd.umatch("public ")) {
	dl_scope = RTLD_GLOBAL;
	// RTLD_GLOBAL means symbols defined in a plugin are global
	// Use this when a plugin depends on another.
      }else if (cmd.umatch("lazy ")) {
	check = RTLD_LAZY;
	// RTLD_LAZY means to defer resolving symbols until needed
	// Use when a plugin will not load because of unresolved symbols,
	// but it may work without it.
      }else if (cmd.umatch("force ")) {
	force = true;
	// ignore version mismatch of some kind
      }else{
      }
    } while (cmd.more() && !cmd.stuck(&here));

    std::string file_name;
    cmd >> file_name;

    if(file_name==""){
      // no arg, list plugins loaded
      OMSTREAM out = IO::mstdout;
      outset(cmd, &out);
      
      std::string comma;
      for (std::map<std::string, void*>::iterator
	     ii = attach_list.begin(); ii != attach_list.end(); ++ii) {untested();
	if (ii->second) {untested();
	  out << comma << ii->first;
	  comma = ",\n";
	}else{untested();
	}
      }
      out << "\n";
      return;
    }

    void* handle = attach_list[file_name];
    trace2("...", file_name, handle);
    if (handle) {
      if (CARD_LIST::card_list.is_empty()) {
	cmd.warn(bDANGER, here, "\"" + file_name + "\": already loaded, replacing");
	dlclose(handle);
	attach_list[file_name] = NULL;
      }else{untested();
	cmd.reset(here);
	throw Exception_CS("already loaded, cannot replace when there is a circuit", cmd);
      }
    }else{
    }

    std::string source_filename(file_name);
    if (file_name.size()>3 && !strcmp(file_name.c_str()+file_name.size()-3,".cc")) {
      file_name[file_name.size()-2]='s';
      file_name[file_name.size()-1]='o';

      if(file_name[0]=='/') { untested();
      } else {
	char* cwd = get_current_dir_name(); // POSIX, no C++ implementation available
	source_filename = std::string(cwd) + "/" + source_filename;
	free(cwd);
      }
    } else {
      source_filename = "";
    }

    if (source_filename!=""){
      assert(source_filename[0]=='/');
      try {
	compile(file_name, source_filename);
      }catch(Exception& e){
	cmd.reset(here);
	throw Exception_CS(e.message(), cmd);
      }
    }

    try {
      assert(!handle);
      handle = do_attach(file_name, check | dl_scope, force);
    } catch (Exception& e) {
      trace0("do_attach threw");
      cmd.reset(here);
      throw Exception_CS(e.message(), cmd);
    }
    trace0("done attach");
  }
} p1;
DISPATCHER<CMD>::INSTALL dd1(&command_dispatcher, "attach|load", &p1);
/*--------------------------------------------------------------------------*/
void* CMD_ATTACH::do_attach(std::string file_name, int flags, bool force)
{
  void* handle = dlopen(file_name.c_str(), flags);
  char* e_e = dlerror();
  if(e_e || !handle ) {
    throw Exception("cannot attach (" + std::string(e_e) + ")");
  }else if (handle) {
    const char* (*name)() = (const char*(*)()) dlsym(handle, "interface_name");
    e_e = dlerror();
    if (1 || force) {
      trace1("forced load...", file_name);
    } else if (e_e && !force) {
      dlclose(handle);
      throw Exception(file_name + " lacks interface information");
    } else if ((e_e || !name) && !force) { untested();
      dlclose(handle); untested();
      throw Exception("lacks interface name");
    } else {}

    unsigned (*version)() = (unsigned(*)()) dlsym(handle, "interface_version");
    e_e = dlerror();
    if (1 || force) {
    } else if ((e_e || !version) && !force) { untested();
      dlclose(handle);
      throw Exception("lacks interface version");
    } else if (strcmp(name(), interface_name())) {
      std::string n(name());
      dlclose(handle);
      throw Exception("wrong interface ("+ n +
		      ", not " + std::string(interface_name()) + ")");
    } else if (interface_version() == version()) {
    } else if (HAVE_GIT_REPO) { untested();
      throw Exception("plugin (" + to_string(version()) + ") doesnt match git revision (" + to_string(interface_version()) + ")");
    } else { untested();
      throw Exception("plugin too " + (interface_version() < version())?"new":"old");
    }
    assert(handle);
    return handle;
  }else{itested();
    throw Exception(dlerror());
  }
}
/*--------------------------------------------------------------------------*/
void CMD_ATTACH::compile(std::string &filename, std::string source_filename)
{
  struct stat ccattrib;
  int ccstat = stat(source_filename.c_str(), &ccattrib);
  if (ccstat) { untested();
    throw Exception("cannot compile: " + source_filename +
		    " does not exist (" + to_string(ccstat) + ")\n");
  } else {
  }

  struct stat soattrib;
  int sostat = stat(filename.c_str(), &soattrib);
  std::string make = "make"; // OS::getenv("GNUCAP_MAKE", GNUCAP_MAKE);
  std::string gnucap_cppflags = ""; //OS::getenv("GNUCAP_CPPFLAGS", GNUCAP_CPPFLAGS);

  FILE* f = NULL;
  char* sf2 = strdup(filename.c_str());
  std::string f1(basename(sf2)); free(sf2);
  char* tmplt = NULL;
  char* t = NULL;

  if (filename[0]!='/') {
    filename = "./" + filename;
  }

  if (!sostat && ccattrib.st_mtime < soattrib.st_mtime) {
    trace0("so exists and is newer");
    return;
  } else if(!sostat) {
    trace0("so needs to be refreshed");
    f = fopen(filename.c_str(),"a");
    if (f) { untested();
      trace0("so is writable");
      fclose(f);
    } else { untested();
      tmplt = strdup("/tmp/soXXXXXX");
      t = mkdtemp(tmplt);
      if (!t) throw Exception("cannot create temporary file");
      filename = std::string(t) + "/" + f1;
    }
  } else {
  }
  free(tmplt);
  t = NULL;

  char* sf1 = strdup(source_filename.c_str());
  char* fn1 = strdup(filename.c_str());
  std::string d1(dirname(fn1));
  std::string d2(dirname(sf1));

  int childret;
  pid_t p = vfork();
  if (p) {
    waitpid(p, &childret, 0);
  } else {
    error(bDEBUG, "calling " + make + " -C" + d1 + " VPATH=" + d2 + " " + f1 + "\n");
    int ret = execlp( make.c_str(), make.c_str(),
		      "-C", d1.c_str(),
		      ("GNUCAP_CPPFLAGS="+gnucap_cppflags+"").c_str(),
		      ("VPATH=" + d2).c_str(),
		      f1.c_str(), (char*) NULL);
    _exit(ret);
  }
  free(sf1);
  free(fn1);
//  if (t) { incomplete();
//    // rm -r t;
//  }

  if(childret){
    throw Exception("cannot make " + filename + "(" + to_string(childret) + ")");
  }
}
/*--------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------*/
class CMD_DETACH : public CMD {
public:
  void do_it(CS& cmd, CARD_LIST*)
  {
    if (CARD_LIST::card_list.is_empty()) {
      unsigned here = cmd.cursor();
      std::string file_name;
      cmd >> file_name;
      
      void* handle = attach_list[file_name];
      if (handle) {
	dlclose(handle);
	attach_list[file_name] = NULL;
      }else{itested();
	cmd.reset(here);
	throw Exception_CS("plugin not attached", cmd);
      }
    }else{itested();
      throw Exception_CS("detach prohibited when there is a circuit", cmd);
    }
  }
} p2;
DISPATCHER<CMD>::INSTALL d2(&command_dispatcher, "detach|unload", &p2);
/*--------------------------------------------------------------------------*/
class CMD_DETACH_ALL : public CMD {
public:
  void do_it(CS& cmd, CARD_LIST*)
  {
    if (CARD_LIST::card_list.is_empty()) {
      for (std::map<std::string, void*>::iterator
	     ii = attach_list.begin(); ii != attach_list.end(); ++ii) {
	void* handle = ii->second;
	if (handle) {
	  dlclose(handle);
	  ii->second = NULL;
	}else{
	  // plugin in the list but not attached.  
	}
      }
    }else{
      throw Exception_CS("detach prohibited when there is a circuit", cmd);
    }
  }
} p3;
DISPATCHER<CMD>::INSTALL d3(&command_dispatcher, "detach_all", &p3);
/*--------------------------------------------------------------------------*/
}
/*--------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------*/
// vim:ts=8:sw=2:noet
