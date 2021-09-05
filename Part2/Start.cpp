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

// Default Constructor
Start::Start(){
     printLogo();

     this->connection = env_details();
}

// Load in connection details to struct object
connection_info Start::env_details(){

     // Load file containing connection details 
     fstream db_file ("db_env.bat");

     if(!db_file) { std::cerr << "Error: Could not Open/Find file!\n"; exit;}

     int count = 1;
     std::string line;

     for(int i = 1; i < 6; i++){
          std::getline(db_file, line);
          if(i == 1){ line.erase(0,9); connection.db = line.c_str(); }
          if(i == 2){ line.erase(0,11); connection.port = line.c_str(); }
          if(i == 3){ line.erase(0,11); connection.host = line.c_str(); }
          if(i == 4){ line.erase(0,11); connection.user = line.c_str(); }
          if(i == 5){ line.erase(0,11); connection.pass = line.c_str(); }
          cout << line << endl;
     }

     return connection;
}

// Connect to MySQL database using parameter data
MYSQL* Start::mysql_connection_setup(struct connection_info db_info){
     MYSQL * con = mysql_init(NULL);

     if(mysql_real_connect(con, db_info.host, db_info.user, db_info.pass, db_info.db, std::stoi(db_info.port), NULL, 0)){
          cout << "Connection Error: " << mysql_error(con) << endl;
          exit(1);
     }

     return con;
}

// MySQL Query
MYSQL_RES* Start::send_query(MYSQL * con, const char * db_query){

     if(mysql_query(con, db_query)){
          cout << "MySQL Query Error: " << mysql_error(con) << endl;
          exit(1);
     }

     return mysql_use_result(con);

}

// Print "SAVE" ASCII logo 
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
     "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n\n\n" << endl;
}

// Default destructor
Start::~Start()= default;