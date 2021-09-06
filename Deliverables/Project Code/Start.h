//
// Created By Luis Garduno || Southern Methodist University : 2021-09-04
//

#ifndef START_H
#define START_H

#include <string>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <mysql/mysql.h>

using std::cout;
using std::endl;
using std::setw;
using std::left;
using std::string;
using std::fstream;

struct connection_info{
     const char * db, * port, * host, * user, * pass;
};

class Start {
     public:
          // Default Constructor
          Start();

          // Connect to MySQL database using parameter data
          MYSQL* mysql_connection_setup(struct connection_info db_info);

          // MySQL Query
          MYSQL_RES* send_query(MYSQL * connect, const char * db_query);

          // Deploy Rule #1 | Rule #2
          void rule_1();
          void rule_2();


          // Print "SAVE" ASCII Logo
          void printLogo();

          // Default Destructor
          ~Start();

     private:
          // MySQL Connection Information
          struct connection_info connection;
          MYSQL * con;
};

#endif // START_H