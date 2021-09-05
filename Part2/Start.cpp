//
// Created By Luis Garduno || Southern Methodist University : 2021-09-04
//

#include "Start.h"

#include <string>
#include <fstream>

using std::cout;
using std::endl;
using std::string;
using std::fstream;

Start::Start(){
     connection.db = "", connection.host = "";
     connection.user = "", connection.pass = "";
}

void Start::connectDB(){

     fstream db_file ("db_env.bat");

     if(!db_file) { std::cerr << "Error: Could not Open/Find file!\n"; exit;}

     int count = 1;
     std::string line;

     while(std::getline(db_file, line)){

          if(count == 4){
               line.erase(0,11);
               connection.pass = line.c_str();
          }

          if(count == 3){
               line.erase(0,11);
               connection.user = line.c_str();
          }

          if(count == 2){
               line.erase(0,11);
               connection.host = line.c_str();
          }

          if(count == 1){
               line.erase(0,9);
               connection.db = line.c_str();
          }

          count++;

          cout << line << endl;
     }
}

void Start::printLogo(){
     cout <<
     "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n" << 
     "@@@@@@@@@@@@@@@@@@@@@@@@             @@@@@@@@@@@@@@@@@@@@@@@\n" << 
     "@@@@@@@@@@@@@@@@                           @@@@@@@@@@@@@@@@@\n" << 
     "@@@@@@@@@@@@                                   @@@@@@@@@@@@@\n" << 
     "@@@@@@@@@@                                       @@@@@@@@@@@\n" << 
     "@@@@@@@                                             @@@@@@@@\n" << 
     "@@@@@@                  @@@@@@@@@@@@@                 @@@@@@\n" << 
     "@@@@@                 @@@@@@@@@@@@@@@@@                @@@@@\n" << 
     "@@@@               @@@@@@@      @@@@@@@@                @@@@\n" << 
     "@@@               @@@@@@           @@@@@                 @@@\n" << 
     "@@                @@@@@@@@           @@@                  @@\n" << 
     "@@                @@@@@@@@@@@@        @@;                 @@\n" <<
     "@@                 @@@@@@@@@@@@@@@@                       @@\n" <<
     "@@                  @@@@@@@@@@@@@@@@@@@                   @@\n" << 
     "@@                     @@@@@@@@@@@@@@@@@@                 @@\n" <<
     "@@                       @@@@@@@@@@@@@@@@@                @@\n" << 
     "@@                           @@@@@@@@@@@@@@@              @@\n" <<
     "@@                 @@@             @@@@@@@@               @@\n" << 
     "@@@                @@@@@            @@@@@@@              @@@\n" << 
     "@@@@               @@@@@@@@@        @@@@@@              @@@@\n" << 
     "@@@@@               @@@@@@@@@@@@@@@@@@@@@              @@@@@\n" <<
     "@@@@@@             @@@   @@@@@@@@@@@@                 @@@@@@\n" << 
     "@@@@@@@@                                           @@@@@@@@@\n" << 
     "@@@@@@@@@@                                       @@@@@@@@@@@\n" << 
     "@@@@@@@@@@@@@                                 @@@@@@@@@@@@@@\n" << 
     "@@@@@@@@@@@@@@@@@                         @@@@@@@@@@@@@@@@@@\n" <<
     "@@@@@@@@@@@@@@@@@@@@                   @@@@@@@@@@@@@@@@@@@@@\n" << 
     "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@" << endl;
}