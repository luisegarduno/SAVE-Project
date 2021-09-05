//
// Created By Luis Garduno || Southern Methodist University : 2021-09-04
//

#include "Start.h"

// Default Constructor
Start::Start(){
     //printLogo();

     // Load in connection details to struct object
     fstream db_file ("db_env.bat");
     if(!db_file) { std::cerr << "Error: Could not Open/Find file!\n"; exit; }

     std::string a, b, c, d, e;

     std::getline(db_file, a); a.erase(0,9);
     connection.db = a.c_str();

     std::getline(db_file, b); b.erase(0,11);
     connection.port = b.c_str();

     std::getline(db_file, c); c.erase(0,11);
     connection.host = c.c_str();

     std::getline(db_file, d); d.erase(0,11);
     connection.user = d.c_str();

     std::getline(db_file, e); e.erase(0,11);
     connection.pass = e.c_str();

     // ------- Connect to database ------- 
     con = mysql_connection_setup(connection);
}

// Connect to MySQL database using parameter data
MYSQL* Start::mysql_connection_setup(struct connection_info db_info){
     MYSQL * connect = mysql_init(NULL);

     if(!mysql_real_connect(connect, connection.host, connection.user, connection.pass, connection.db, std::atoi(connection.port), NULL, 0)){
          cout << "Connection Error: " << mysql_error(connect) << endl;
          exit(1);
     }

     return connect;
}

// MySQL Query
MYSQL_RES* Start::send_query(MYSQL * connect, const char * db_query){

     if(mysql_query(connect, db_query)){
          cout << "MySQL Query Error: " << mysql_error(connect) << endl;
          exit(1);
     }

     return mysql_use_result(connect);
}

// Deploy MySQL Query that obeys Rule #1
void Start::rule_1(){
     cout << "Rule 1" << endl;

     MYSQL_RES * rule1_query;
     MYSQL_ROW * row;
}

// Deploy MySQL Query that obeys Rule #2
void Start::rule_2(){
     MYSQL_ROW row;
     MYSQL_RES * rule2_query;

     rule2_query = send_query(con,
     "SELECT CONCAT_WS(' ', ai.first_name, ai.last_name) AS Name, \
             ai.account_number, t.transaction_number,             \
             ai.state, t.merchant_state                           \
     FROM account_info ai                                         \
          JOIN transactions t                                     \
          ON ai.account_number = t.account_number                 \
     WHERE ai.state != t.merchant_state;");

     std::ofstream fout("../Deliverables/Part2_Output.txt");

     // Output the results to both the screen & a file (Part2_Output.txt)
     cout << setw(20) << left << "Name";  fout << setw(20) << left << "Name";
     cout << setw(20) << left << "Account Number"; fout << setw(20) << left << "Account Number";
     cout << setw(25) << left << "Transaction Number"; fout << setw(25) << left << "Transaction Number";
     cout << setw(35) << left << "Expected Transaction Location"; fout << setw(35) << left << "Expected Transaction Location";
     cout << setw(35) << left << "Actual Transaction Location" << endl; fout << setw(35) << left << "Actual Transaction Location" << endl;

     while ((row = mysql_fetch_row(rule2_query)) != NULL){
          cout << setw(20) << left << row[0];          fout << setw(20) << left << row[0];
          cout << setw(20) << left << row[1];          fout << setw(20) << left << row[1];
          cout << setw(25) << left << row[2];          fout << setw(25) << left << row[2];
          cout << setw(35) << left << row[3];          fout << setw(35) << left << row[3];
          cout << setw(35) << left << row[4] << endl;  fout << setw(35) << left << row[4] << endl;
     }
     
     fout.close();

     mysql_free_result(rule2_query);
     mysql_close(con);
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