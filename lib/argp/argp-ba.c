/* Default definition for ARGP_PROGRAM_BUG_ADDRESS.
   Copyright (C) 1996, 1997, 1999, 2004, 2007 Free Software Foundation, Inc.
   This file is part of the GNU C Library.
   Written by Miles Bader <miles@gnu.ai.mit.edu>.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Library General Public License as
   published by the Free Software Foundation; either version 2 of the
   License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Library General Public License for more details.

   You should have received a copy of the GNU Library General Public
   License along with the GNU C Library; see the file COPYING.LIB.  If not,
   write to the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.  */

/* If set by the user program, it should point to string that is the
   bug-reporting address for the program.  It will be printed by argp_help if
   the ARGP_HELP_BUG_ADDR flag is set (as it is by various standard help
   messages), embedded in a sentence that says something like `Report bugs to
   ADDR.'.  */
const char *argp_program_bug_address = 0;
