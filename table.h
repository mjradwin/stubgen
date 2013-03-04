/*
 *  FILE: table.h
 *  AUTH: Michael J. Radwin <michael@radwin.org>
 *
 *  DESC: stubgen symbol table goodies
 *
 *  DATE: 1996/08/14 22:04:47
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

#ifndef TABLE_HEADER
#define TABLE_HEADER

#ifdef	__cplusplus
extern "C" {
#endif

#define NELEMS              500     /* maximum number of symbols */

#define IGNORE_KIND           0     /* a variable or forward declaration */
#define FUNC_KIND             1     /* a method declaration */
#define CLASS_KIND            2     /* a class declaration */
#define INLINED_KIND          3     /* a method w/body in a class decl. */
#define SKEL_KIND             4     /* a method found in a code file */
#define STRUCT_KIND           5     /* a struct declaration that's a class */
#define DONE_FUNC_KIND       11     /* a fn that we've finished expanded */
#define DONE_CLASS_KIND      12     /* a class that we've finished expanded */

/* returns a pointer to a static string */
const char * string_kind(int some_KIND);

/*
 * Represents a single argument, often used in a list.
 */
typedef struct arg {
    char *type;       /* type of this arg.       may NOT be NULL */
    char *name;       /* formal parameter name.  may     be NULL */
    char *array;      /* any array dimensions    may     be NULL
                         appended to name.                       */
    struct arg *next; /* next argument.          may     be NULL */
} arg_t;

/* 
 * This structure is central to the program.  It might have been more
 * elegant with an object-oriented approach consisting of the following
 * objects: ignore, method, class, inlined, skeleton.
 *
 * Instead, however, we have a "throw-it-all-in-one" structure that has
 * unused pieces of data, depending on the kind field.
 *
 * A syntaxelem_t is "valid" if the name field is non-NULL.
 */
typedef struct syntaxelem {
    char *name;        /* name of class or func. may NOT be NULL  */
    char *ret_type;    /* return type.           may NOT be NULL  */
    arg_t *args;       /* argument list.         may     be NULL  */
    char *templ;       /* template declaration.  may     be NULL  */
    struct syntaxelem *parent;   /* parent class                  */
    struct syntaxelem *next;     /* next class or member          */
    struct syntaxelem *children; /* children of this class        */
    char *throw_decl;  /* throw() clause.        may     be NULL  */
    int const_flag;    /* 1 if the func is const, 0 if not.       */
    int kind;          /* some_KIND                               */
} syntaxelem_t;

/* defined in table.c */
void init_tables();
void free_tables();

#ifdef SGDEBUG
void print_se(syntaxelem_t *);
#else
#define print_se(arg)
#endif /* SGDEBUG */

/* used in scanning */
arg_t * reverse_arg_list(arg_t *);
void free_args(arg_t *);
syntaxelem_t *new_elem(char *, char *, arg_t *, int);
syntaxelem_t *reverse_list(syntaxelem_t *);

/* used in generating output.
   allocates memory; someone's gotta clean it up! */
char *args_to_string(arg_t *, int);

/* used in comparison with existing skeletons*/
int skel_elemcmp(syntaxelem_t *skel_elem, syntaxelem_t *hdr_elem);
int strict_elemcmp(syntaxelem_t *e1, syntaxelem_t *e2);

/* list management primitives */
void enqueue_class(syntaxelem_t *);
syntaxelem_t * dequeue_class();
int class_queue_empty();

void enqueue_skeleton(syntaxelem_t *);
syntaxelem_t * find_skeleton(syntaxelem_t *);
void clear_skeleton_queue();

#ifdef	__cplusplus
}
#endif

#endif /* TABLE_HEADER */
