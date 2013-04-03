stubgen
=======

a member function stub generator for C++

stubgen is a C++ development tool that keeps code files in sync with
their associated headers.  When it finds a member function declaration
in a header file that doesn't have a corresponding implementation, it
creates an empty skeleton with descriptive comment headers.  stubgen has
several options, but see the "Brief Example" section below for an idea
of what it can do.

Brief Example
-------------

Suppose you have the following header file Point.h:
 
          class Point {
          public:
              Point(int x, int y);
              void addTo(const Point& other);
 
              int xValue, yValue;
          };
 
Running "stubgen -s Point.h" would produce the following file:
 
          /***********************************************
           * AUTHOR: Michael J. Radwin <mjr@acm.org>
           *   FILE: Point.cpp
           *   DATE: Mon Apr 20 17:39:05 1998
           *  DESCR:
           ***********************************************/
          #include "Point.h"
 
          /*
           *  Method: Point::Point()
           *   Descr:
           */
          Point::Point(int x, int y)
          {
          }
 
          /*
           *  Method: Point::addTo()
           *   Descr:
           */
          void
          Point::addTo(const Point& other)
          {
          }

