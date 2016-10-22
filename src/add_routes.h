#ifndef ADD_ROUTES_H
#define ADD_ROUTES_H

#include <pebble.h>
#include "buses.h"

#define MENU_CELL_HEIGHT_BUS 60

void AddRoutesUpdate(Routes, Buses*);
void AddRoutesInit(Stop, Buses*);

#endif /* end of include guard: ADD_ROUTES_H */
