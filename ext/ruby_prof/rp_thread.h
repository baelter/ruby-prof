/* Copyright (C) 2005-2019 Shugo Maeda <shugo@ruby-lang.org> and Charlie Savage <cfis@savagexi.com>
   Please see the LICENSE file for copyright and distribution information */

#ifndef __RP_THREAD__
#define __RP_THREAD__

#include <stdbool.h>

/* Profiling information for a thread. */
typedef struct
{
    // Runtime
    VALUE object;                     /* Cache to wrapped object */
    VALUE fiber;                      /* Fiber */
    prof_stack_t* stack;              /* Stack of frames */
    bool trace;                    /* Are we tracking this thread */

    VALUE thread_id;                  /* Thread id */
    VALUE fiber_id;                   /* Fiber id */
    VALUE methods;                    /* Array of RubyProf::MethodInfo */
    st_table* method_table;           /* Methods called in the thread */
} thread_data_t;

void rp_init_thread(void);
st_table * threads_table_create(void);
thread_data_t *threads_table_lookup(void *profile, VALUE fiber);
thread_data_t* threads_table_insert(void *profile, VALUE thread, VALUE fiber);
void switch_thread(void *profile, thread_data_t *thread_data, double measurement);
void threads_table_free(st_table *table);
VALUE prof_thread_wrap(thread_data_t *thread);
void prof_thread_mark(thread_data_t *thread);
int pause_thread(st_data_t key, st_data_t value, st_data_t data);
int unpause_thread(st_data_t key, st_data_t value, st_data_t data);

#endif //__RP_THREAD__
