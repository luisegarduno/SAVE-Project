//
// Created By Luis Garduno || Southern Methodist University : 2021-09-04
//

#ifndef START_H
#define START_H

#include <iostream>

struct connection_info{
     const char * db, * host, * user, * pass;
};

class Start {
     public:
          Start();                 // Default Constructor
          void connectDB();
          void printLogo();

     private:
          connection_info connection;
};

#endif // START_H