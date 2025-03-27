#include "entrypoint.h"
#include "sqlite3.h"
#include "knob.h"

#include <time.h>
#include <stdlib.h>

#define LOG_SQLITE3_ERROR(db) knob_log(KNOB_ERROR, "%s:%d: SQLITE3 ERROR: %s\n", __FILE__, __LINE__, sqlite3_errmsg(db))

// void see_state_fruits(sqlite3* db,char* state_name){
//     sqlite3_stmt* stmt = NULL;
//     char content[] =
//     "SELECT fruit,price\n"
//     "FROM FruitsForSale\n"
//     "WHERE etat=?;";
//     int ret = sqlite3_prepare_v2(db,content,-1,&stmt,NULL);

//     if(ret != SQLITE_OK){
//         LOG_SQLITE3_ERROR(db);
//     }

//     if(sqlite3_bind_text(stmt,1,state_name,-1,SQLITE_STATIC) != SQLITE_OK){
//         LOG_SQLITE3_ERROR(db);
//     }

//     for(int ret = sqlite3_step(stmt);ret != SQLITE_DONE;ret = sqlite3_step(stmt)){
//         if(ret != SQLITE_ROW){
//             LOG_SQLITE3_ERROR(db);
//         }
//         int column = 0;
//         const unsigned char* fruit = sqlite3_column_text(stmt,column++);
//         float price = sqlite3_column_double(stmt,column);
//         knob_log(KNOB_INFO,"Etat %s a le fruit %s avec le prix %.2f$",state_name,fruit,price);
//     }

//     sqlite3_finalize(stmt);
// }
// const char* fruits[] = {
//     "Banana",
//     "Orange",
//     "Grape",
//     "Pear",
//     "Kumqat"
// };
// const char* states[] = {
//     "CA",
//     "SC",
//     "NC",
//     "FL",
//     "HA"
// };
// void add_random_fruit(sqlite3* db){
//     if (sqlite3_exec(db, "BEGIN;", NULL, NULL, NULL) != SQLITE_OK) {
//         LOG_SQLITE3_ERROR(db);
//         return;
//     }
//     sqlite3_stmt* stmt = NULL;
//     char content[] =
//     "INSERT INTO FruitsForSale(fruit,etat,price)\n"
//     "VALUES\n"
//     "(?,?,?);";
//     int ret = sqlite3_prepare_v2(db,content,-1,&stmt,NULL);
//     int fruit = rand() %5;
//     int state = rand() %5;
//     double price = ((rand()+1) % 100) /100 + rand() % 2;
//     if(sqlite3_bind_text(stmt,1,fruits[fruit],-1,SQLITE_STATIC) != SQLITE_OK){
//         LOG_SQLITE3_ERROR(db);
//     }
//     if(sqlite3_bind_text(stmt,2,states[state],-1,SQLITE_STATIC) != SQLITE_OK){
//         LOG_SQLITE3_ERROR(db);
//     }
//     if(sqlite3_bind_double(stmt,3,price) != SQLITE_OK){
//         LOG_SQLITE3_ERROR(db);
//     }
//     ret = sqlite3_step(stmt);
//     if (sqlite3_exec(db, "COMMIT;", NULL, NULL, NULL) != SQLITE_OK) {
//         LOG_SQLITE3_ERROR(db);
//     }
// }
void AfficherLieux(sqlite3*db){
    printf("Burger");
    sqlite3_stmt* stmt = NULL; //initialise ma requete SQL
    const char* query = "SELECT LieuxID, LieuxName, LieuxDescript FROM LIEUX;"; //Ce que ma requete fait

    if(sqlite3_prepare_v2(db, query, -1, &stmt, NULL)!= SQLITE_OK){//convertire la requete en sqlite
        sqlite3_finalize(stmt);//liberer memoire après de la requete(stmt)
        return;
    }
    while(sqlite3_step(stmt)==SQLITE_ROW){
        int id = sqlite3_column_int(stmt,0);
        unsigned const char* name = (unsigned const char*)sqlite3_column_text(stmt,1);
        unsigned const char* description = (unsigned const char*)sqlite3_column_text(stmt,2);
        printf("ID: %d\nNom: %s\nDescription: %s\n", id, name, description);
    }

    sqlite3_finalize(stmt);
}
void raylib_start(void){
    printf("Bruh");
    srand(time(NULL));
    sqlite3* db = NULL;
    sqlite3_open("./aventure_quete.db",&db);
    AfficherLieux(db);
    // see_state_fruits(db,"FL");
    // see_state_fruits(db,"CA");
    // see_state_fruits(db,"NC");
    // add_random_fruit(db); //Uncomment to add a random fruit...
    sqlite3_close(db);
    return;
}