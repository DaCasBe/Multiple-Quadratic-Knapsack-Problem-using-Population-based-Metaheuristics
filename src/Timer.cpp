/***************************************************************************
                          Timer.cc  -  description
                             -------------------
    begin                : Fri Feb 1 2013
    copyright            : (C) 2013 by Christian Blum
    email                : christian.blum@ehu.es
 *
 *  modified by Carlos García on Dic 9 2013
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/
#include "Timer.h"

/*
 *  The virtual time of day and the real time of day are calculated and
 *  stored for future use.  The future use consists of subtracting these
 *  values from similar values obtained at a later time to allow the user
 *  to get the amount of time used by the algorithm.
 */
Timer::Timer(void) {
  getrusage( RUSAGE_SELF, &res );
  virtual_time = (double) res.ru_utime.tv_sec +
    (double) res.ru_stime.tv_sec +
    (double) res.ru_utime.tv_usec * 1.0E-6 +
    (double) res.ru_stime.tv_usec * 1.0E-6;
  
  gettimeofday( &tp, NULL );
  real_time =    (double) tp.tv_sec + (double) tp.tv_usec * 1.0E-6;
}

/*
 *  Stop the stopwatch and return the time used in seconds (either
 *  REAL or VIRTUAL time, depending on ``type'').
 */
double Timer::elapsed_time(const TYPE& type) {
  if (type == REAL) {
    gettimeofday( &tp, NULL );
    return( (double) tp.tv_sec + (double) tp.tv_usec * 1.0E-6 - real_time );
  }
  else {
    getrusage( RUSAGE_SELF, &res );
    return( (double) res.ru_utime.tv_sec +
	    (double) res.ru_stime.tv_sec +
	    (double) res.ru_utime.tv_usec * 1.0E-6 +
	    (double) res.ru_stime.tv_usec * 1.0E-6
	    - virtual_time );
  }
}

//Carlos García
void Timer::reset(){
  getrusage( RUSAGE_SELF, &res );
  virtual_time = (double) res.ru_utime.tv_sec +
    (double) res.ru_stime.tv_sec +
    (double) res.ru_utime.tv_usec * 1.0E-6 +
    (double) res.ru_stime.tv_usec * 1.0E-6;
  
  gettimeofday( &tp, NULL );
  real_time =    (double) tp.tv_sec + (double) tp.tv_usec * 1.0E-6;
}
