/***************************************************************************
                          Timer.h  -  description
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
#ifndef __TIMER_H__
#define __TIMER_H__

using namespace std;

#include <sys/time.h>
#include <sys/resource.h>
#include <stdio.h>

class Timer {
private:
  struct rusage res;
  struct timeval tp;
  double virtual_time, real_time;

public:
  enum TYPE {REAL, VIRTUAL};
  Timer(void);
  double elapsed_time(const TYPE& type);
  
  void reset(); //Carlos García
};
#endif
