/** 
 * Copyright 2016 Kevin Michael Woley (kmwoley@gmail.com)
 * All rights reserved.
 * 
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * 
 *     http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License. 
 */
 
#ifndef BUSES_H
#define BUSES_H

#include <pebble.h>
#include <pebble-math-sll/math-sll.h>
#include "memlist.h"

// WARNING:
// CHANGING THIS STRUCT WILL CAUSE A PERSISTENT STORAGE VERSION CHANGE
// MODIFY WITH CARE
typedef struct {
  // struct {
    sll lat;
    sll lon;
  // } Coordinates;
  char* route_id;
  char* stop_id;
  char* route_name;
  char* stop_name;
  char* direction;
  char* description;
} __attribute__((__packed__)) Bus;
// WARNING:
// CHANGING THIS STRUCT WILL CAUSE A PERSISTENT STORAGE VERSION CHANGE
// MODIFY WITH CARE

typedef struct {
  Bus* data;
  uint32_t count;

  // used to geographically filter nearby buses
  uint32_t* filter_index;
  uint32_t filter_count;
} __attribute__((__packed__)) Buses;

typedef struct {
  uint16_t index;
  char* stop_id;
  char* stop_name;
  char* detail_string;
  sll lat;
  sll lon;
  char* direction;
} __attribute__((__packed__)) Stop;

typedef struct {
  MemList* memlist;
  uint16_t total_size; // total number of stops
  uint16_t index_offset; // what index does the memlist start at
} __attribute__((__packed__)) Stops;

typedef struct {
  char* route_id;
  char* route_name;
  char* description;
  bool favorite;
} __attribute__((__packed__)) Route;

typedef struct {
  Route* data;
  uint32_t count;
} __attribute__((__packed__)) Routes;

void ListBuses(const Buses* buses);
void ListStops(const Stops* stops);
void CreateStopsFromBuses(const Buses* buses, Stops* stops);
void CreateRoutesFromBuses(const Buses* buses, const Stop* stop, Routes* routes);
void FilterBusesByLocation(const sll lat, const sll lon, Buses* buses);
void BusesDestructor(Buses* buses);
bool AddBus(const Bus* bus, Buses* buses);
bool AddBusFromStopRoute(const Stop* stop, const Route* route, Buses* buses);
void RemoveBus(uint32_t index, Buses *buses);
int32_t GetBusIndex(const char* stop_id,
                    const char* route_id,
                    const Buses* buses);
void AddStop(const uint16_t index,
             const char* stop_id,
             const char* stop_name,
             const char* detail_string,
             const sll lat,
             const sll lon,
             const char * direction,
             Stops* stops);
void AddRoute(const char *route_id,
              const char *routeName,
              const char *description,
              const bool favorite,
              Routes* routes);
Stop StopConstructor(const uint16_t index,
                     const char* stop_id,
                     const char* stop_name,
                     const char* detail_string,
                     const sll lat,
                     const sll lon,
                     const char* direction);
void StopDestructor(Stop* stop);
void StopsConstructor(Stops* stops);
void StopsDestructor(Stops* stops);
Route RouteConstructor(const char* route_id,
                       const char* route_name,
                       const char* description,
                       const bool favorite);
void RouteDestructor(Route *t);
void RoutesConstructor(Routes *r);
void RoutesDestructor(Routes *r);

#endif /* end of include guard: BUSES_H */
