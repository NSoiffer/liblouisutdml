/* liblouisutdml Braille Transcription Library

   This file may contain code borrowed from the Linux screenreader
   BRLTTY, copyright (C) 1999-2006 by
   the BRLTTY Team

   Copyright (C) 2004, 2005, 2006
   ViewPlus Technologies, Inc. www.viewplus.com
   and
  Abilitiessoft, Inc. www.abilitiessoft.com
   All rights reserved

   This file is free software; you can redistribute it and/or modify it
   under the terms of the Lesser or Library GNU General Public License 
   as published by the
   Free Software Foundation; either version 3, or (at your option) any
   later version.

   This file is distributed in the hope that it will be useful, but
   WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the 
   Library GNU General Public License for more details.

   You should have received a copy of the Library GNU General Public 
   License along with this program; see the file COPYING.  If not, write to
   the Free Software Foundation, 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.

   Maintained by John J. Boyer john.boyer@abilitiessoft.com
   */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int
main (void)
{
  static const char *makefileStub[] = {
    "# Make liblouisutdml.dll and liblouisutdml.lib",
    " ",
    "# This file was generated by make_makefile.exe.",
    "# Do not edit this file. Change configure.mk.",
    "# Then run",
    "# nmake /f Make_makefile.msvc",
    "# If there are no errors run",
    "# nmake",
    "# to generate liblouisutdml.dll and liblouisutdml.lib",
    " ",
    "!include configure.mk",
    "!include $(LIBLOUIS_PATH)\\windows\\configure.mk",
    "SRCDIR = ..\\liblouisutdml",
    "HEADERS = $(SRCDIR)\\louisutdml.h $(SRCDIR)\\liblouisutdml.h liblouisutdml.def",
    "HEADERS = $(HEADERS) $(SRCDIR)\\sem_enum.h $(SRCDIR)\\sem_names.h",
"INCLUDES = /I$(LIBLOUIS_PTH)\\liblouis /I$(LIBLOUIS_PATH)\\windows\\include",
"INCLUDES = $(INCLUDES) /I$(LIBXML2_PATH)\\include\\libxml2\\libxml",
      "LIBLOUIS_DLL = $(LIBLOUIS_PATH)\\windows\\liblouis-2.dll",
      "LIBXML2_DLL = $(LIBXML2_PATH)\\lib\\libxml2.dll",
      "CFLAGS =  /nologo /O2 /W1 /c $(INCLUDES)",
    "DLLFLAGS = /dll /nologo /DEF:liblouisutdml.def",
    "OBJ = Jliblouisutdml.obj ",
    "!if \"$(UCS)\" == \"2\"",
    "CFLAGS = $(CFLAGS) /DWIDECHAR_TYPE=\"unsigned short int\"",
    "CFLAGS = $(CFLAGS) /DUNICODEBITS=16",
    "!else",
    "CFLAGS = $(CFLAGS) /DWIDECHAR_TYPE=\"unsigned int\"",
    "CFLAGS = $(CFLAGS) /DUNICODEBITS=32",
    "!endif",
    "CC = cl.exe",
    " ",
    "nativelib: liblouisutdml.dll",
    "    if not exists nativelib mddir nativelib",
    "    copy liblouisutdml.dll nativelib",
    "    copy $(LIBLOUIS_DLL) nativelib",
    "    copy $(LIBXML2_DLL) nativelib",
    "liblouisutdml.dll: liblouisutdml.lib liblouisutdml.def \\",
    "    $(LIBLOUIS_DLL) $(LIBXML2_DLL)",
    "    link  $(DLLFLAGS) $(OBJ) $(LIBXML2_DLL) \\",
    "    /OUT:liblouisutdml.dll",
    "liblouisutdml.lib: $(OBJ)",
    "   lib /nologo $(OBJ) /out:liblouisutdml.lib",
    " ",
    "Jliblouisutdml.obj: $(HEADERS) ..\\java\\Jliblouis.c",
    "    $(CC) $(CFLAGS) ..\\java\\Jliblouisutdml.c /I$(JAVA_HEADERS_PATH)",
    NULL
  };

  FILE *makefile_am;
  FILE *configure_ac;
  FILE *Makefile;
  char inbuf[256];
  char version[80];
  char module[50][50];
  int moduleCount = 0;
  char *curchar;
  int ch;
  int ignoreLine = 1;
  char *name;
  int nameLength;
  int k, kk;
  if ((makefile_am = fopen ("..\liblouisutdml\Makefile.am", "r")) == 
NULL)
    {
      fprintf (stderr, "Cannot open Makefile.am.\n");
      exit (1);
    }
  if ((configure_ac = fopen ("..\configure.ac", "r")) == NULL)
    {
      fprintf (stderr, "Cannot open configure.ac.\n");
      exit (1);
    }
  if ((Makefile = fopen ("Makefile", "w")) == NULL)
    {
      fprintf (stderr, "Cannot open Makefile.msvc.\n");
      exit (1);
    }

  // Get module names
  ignoreLine = 1;
  while (fgets (inbuf, sizeof (inbuf), makefile_am))
    {
      curchar = inbuf;
      while ((ch = *curchar++) <= 32 && ch != 0);
      name = curchar - 1;
      while ((ch = *curchar++) > 32 && ch != ',' && ch != '.');
      nameLength = curchar - name - 1;
      name[nameLength] = 0;
      if (strcmp (name, "liblouisutdml_la_SOURCES") == 0)
	{
	  ignoreLine = 0;
	  continue;
	}
      if (ignoreLine)
	continue;
      if (name[nameLength + 1] != 'c')
	continue;
      strcpy (module[moduleCount++], name);
      while ((ch = *curchar++) != 0 && ch != '\\');
      if (ch != '\\')
	break;
    }
  fclose (makefile_am);

  // Get version
  while ((fgets (inbuf, sizeof (inbuf), configure_ac)))
    {
      curchar = inbuf;
      while ((ch = *curchar++) <= 32 && ch != 0);
      name = curchar - 1;
      while ((ch = *curchar++) > 32 && ch != ',' && ch != '(');
      nameLength = curchar - name - 1;
      name[nameLength] = 0;
      if (strcmp (name, "AC_INIT") == 0)
	{
	  strcpy (version, "liblouisutdml-");
	  while (*curchar++ != ',');
	  while (*curchar++ == 32);
	  name = curchar - 1;
	  while ((ch = *curchar++) > 32 && ch != ',');
	  nameLength = curchar - name - 1;
	  name[nameLength] = 0;
	  strcat (version, name);
	  break;
	}
    }
  fclose (configure_ac);

  // Generate Makefile
  for (k = 0; makefileStub[k] != NULL; k++)
    {
      strcpy (inbuf, makefileStub[k]);
      curchar = inbuf;
      while ((ch = *curchar++) <= 32 && ch != 0);
      name = curchar - 1;
      while ((ch = *curchar++) > 32);
      nameLength = curchar - name - 1;
      name[nameLength] = 0;
      if (strcmp (name, "CC") == 0)
	fprintf (Makefile, "$(CCFLAGS) = $(CCFLAGS) -DPACKAGE_VERSION=%s\n",
		 version);
      if (strcmp (name, "OBJ") == 0)
	{
	  fprintf (Makefile, "%s ", makefileStub[k]);
	  for (kk = 0; kk < moduleCount; kk++)
	    fprintf (Makefile, "%s.obj ", module[kk]);
	  fprintf (Makefile, "\n");
	}
      else
	fprintf (Makefile, "%s\n", makefileStub[k]);
    }

  // Make the various object files.
  for (kk = 0; kk < moduleCount; kk++)
    {
      fprintf (Makefile, "%s.obj: $(HEADERS) $(SRCDIR)\\%s.c\n",
	       module[kk], module[kk]);
      fprintf (Makefile, "    $(CC) $(CCFLAGS) $(SRCDIR)\\%s.c\n", 
module[kk]);
    }
  fclose (Makefile);
  return 0;
}
