//
// Created By Luis Garduno || Southern Methodist University : 2021-09-04
//

#ifndef START_H
#define START_H

#include <iostream>
#include <mysql/mysql.h>

struct connection_info{
     const char * db, * port, * host, * user, * pass;
};

class Start {
     public:
          // Default Constructor
          Start();

          // Returns environment details
          connection_info env_details();

          // Connect to MySQL database using parameter data
          MYSQL* mysql_connection_setup(struct connection_info db_info);

          // MySQL Query
          MYSQL_RES* send_query(MYSQL * con, const char * db_query);


          // Print "SAVE" ASCII Logo
          void printLogo();

          // Default Destructor
          ~Start();

     private:
          // MySQL Connection Information
          connection_info connection;
};

#endif // START_H