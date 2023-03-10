/*******************************************************************************
+
+  LEDA 7.0  
+
+
+  monitor.h
+
+
+  Copyright (c) 1995-2023
+  by Algorithmic Solutions Software GmbH
+  All rights reserved.
+ 
*******************************************************************************/


/* Preliminary implementation of a general purpose monitor class wrapping
 * Pthread's condition variables pthread_cond_t.
 * Allows for easy implementations like blocking queues and other higher
 * level synchronisation constructs.
 */

#ifndef LEDA_MONITOR_H
#define LEDA_MONITOR_H


#include <LEDA/system/thread.h>

LEDA_BEGIN_NAMESPACE

#if !defined(LEDA_MULTI_THREAD) || defined(__win32__) || defined(__win64__)

class leda_monitor {
public:
  void signal()           {}
  void broadcast()        {}
  void wait(leda_mutex &) {}
};

#else
  
class leda_monitor {

protected:

  pthread_cond_t cond;

private:
  // no copies
  leda_monitor(const leda_mutex &);
  leda_monitor & operator=(const leda_monitor &);
  
public:
  leda_monitor() { pthread_cond_init(&cond,NULL); }
 ~leda_monitor() { pthread_cond_destroy(&cond); }
  
  /* No preconditions for this call.
   *
   * From pthread docs:
   *   [...] if predictable scheduling behaviour is required, then [the] mutex
   *   shall be locked by the thread calling signal() or broadcast().
   *
   *   [...] more than one thread can return from its call to wait() [...] as a
   *   result of one call to signal(). The effect is called "spurious wakeup".
   *   Note that the situation is self-correcting in that the number of threads
   *   that are so awakened is finite; [...]
   *
   *   An added benefit of allowing spurious wakeups is that the applications
   *   are forced to code a predicate-testing-loop around the condition
   *   [monitor] wait. This also makes the application tolerate superfluous
   *   condition [monitor] broadcasts or signals on the same condition variable
   *   [monitor] that may be coded in some other part of the application. The
   *   resulting applications are thus more robust.
   */

  void signal()    { pthread_cond_signal(&cond); }
  void broadcast() { pthread_cond_broadcast(&cond); }
  
  /* Precondition: the mutex must be locked */
  void wait(leda_mutex& mtx) { pthread_cond_wait(&cond, &mtx.mtx); }

};

#endif

LEDA_END_NAMESPACE

#endif
