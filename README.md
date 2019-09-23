# cachelib
Designing a Caching library

## Description
There are 2 projects. CacheCore has the caching library, and cache is the wrapper project.
In this one, only LRU cache is implemented

## Installation
This is a Visual studio based solution
Open cachelib.sln using Visual studio
Currently only debug versions are buildable
Once solution is built, Run solution from visual studio, or run the built exe file

## Design description
LRU cache is implemented as Doubly linked list.
Map is used for accessing the node pointer.

To visualize the cache, print function is added
