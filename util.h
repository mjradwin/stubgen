/*
 *  FILE: util.h
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

#ifndef UTIL_HEADER
#define UTIL_HEADER

#ifdef	__cplusplus
extern "C" {
#endif

#include <stdarg.h>

extern int yylex();

/* prints a message to the logfile if debugging is enabled */
int log_printf(const char *format, ...);

#ifdef SGDEBUG
int log_vprintf(const char *format, va_list ap);
int log_open(const char *filename); 
void log_flush();
void log_close();
#else
#define log_vprintf(a,b)
#define log_open(arg)
#define log_flush()
#define log_close()
#endif /* SGDEBUG */

/* prints a message to stderr if the -q option is not set */
int inform_user(const char *format, ...);

/* prints a message to stderr and exits with return value 1 */
void fatal(int status, const char *format, ...);

#ifdef	__cplusplus
}
#endif

#endif /* UTIL_HEADER */
