/*
 *  FILE: util.c
 *  AUTH: Michael J. Radwin <michael@radwin.org>
 *
 *  DESC: stubgen utility macros and funcs
 *
 *  DATE: Wed Sep 11 23:31:55 EDT 1996
 *
 *  Copyright (c) 2004  Michael J. Radwin
 *
 *  Redistribution and use in source and binary forms, with or
 *  without modification, are permitted provided that the following
 *  conditions are met:
 *
 *  - Redistributions of source code must retain the above
 *    copyright notice, this list of conditions and the following
 *    disclaimer.
 *
 *  - Redistributions in binary form must reproduce the above
 *    copyright notice, this list of conditions and the following
 *    disclaimer in the documentation and/or other materials
 *    provided with the distribution.
 *
 *  - Neither the name of stubgen nor the names of its contributors
 *    may be used to endorse or promote products derived from this
 *    software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND
 *  CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
 *  INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 *  MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 *  DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 *  CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 *  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 *  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF
 *  USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 *  AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 *  LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
 *  IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
 *  THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "util.h"

//static const char rcsid[] = "$Id: util.c,v 1.19 1998/05/27 22:55:20 mradwin Exp $";

#ifdef SGDEBUG
static FILE *logfile;

int log_open(const char *logfilename) 
{
  logfile = fopen(logfilename, "w");
  return (logfile != NULL);
}

void log_flush()
{
  fflush(logfile);
}

void log_close()
{
  fclose(logfile);
  logfile = NULL;
}

int log_printf(const char *format, ...)
{
  int retval;
  va_list ap;

  va_start(ap, format);
  retval = vfprintf(logfile, format, ap);
  va_end(ap);
 
  return retval;
}

int log_vprintf(const char *format, va_list ap)
{
  return vfprintf(logfile, format, ap);
}

#else
int log_printf(const char *format /*UNUSED*/, ...)
{
  return 0;
}
#endif /* SGDEBUG */


int inform_user(const char *format, ...)
{
  extern int opt_q;
  int retval = 0;
  va_list ap;

  if (!opt_q) {
    va_start(ap, format);
    retval = vfprintf(stderr, format, ap);
    va_end(ap);
  }
 
  return retval;
}

void fatal(int status, const char *format, ...)
{
  va_list ap;
 
  va_start(ap, format);
  log_vprintf(format, ap);
  log_flush();
  log_close();
  (void) vfprintf(stderr, format, ap);
  va_end(ap);
 
  fprintf(stderr, "\n");
  exit(status);
}

#if 0 /* removeDefaultValues() not needed */
/*
 * modifies s by putting a null char in place of the first trailing space
 */
static void removeTrailingSpaces(char *s)
{
    char *end = s + strlen(s) - 1;
    char *orig_end = end;
    
    while(*end == ' ') end--;
    if (end != orig_end) *++end = '\0';
}

/*
 * this both destructively modifies args and conses up a new string.
 * be sure to free it up.
 */
char * removeDefaultValues(char *args)
{
    char *token;
    char *new_arglist = (char *) malloc(strlen(args) + 1);
    int once = 0;
    
    strcpy(new_arglist, "");
    token = strtok(args, "=");
    
    while(token != NULL) {
	/* only append a comma if strtok got the comma off the arglist */
	if (once++) strcat(new_arglist, ",");
	removeTrailingSpaces(token);
	strcat(new_arglist, token);
	token = strtok(NULL, ",");   /* throw away the constant value */
	token = strtok(NULL, "=");   /* grab args up til the next = sign */
    }

    return new_arglist;
}
#endif /* removeDefaultValues() not needed */
