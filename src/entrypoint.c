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
    sqlite3_stmt* stmt = NULL; //initialise ma requete SQL
    const char* query = "SELECT LieuxID,LieuxName,LieuxDescript FROM LIEUX"; //Ce que ma requete fait

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
void CreerPerso(sqlite3*db, char Name[64], int Force, int HP){
    sqlite3_stmt* stmt = NULL; //initialise ma requete SQL
    const char* query = "INSERT INTO PLAYERS (JoueursID,JoueursName, JoueursVie, JoueursForce, LieuxJoueur) VALUES((SELECT COALESCE(MAX(JoueursID),0)+1 FROM PLAYERS),?,?,?,1)";
    if (sqlite3_prepare_v2(db, query, -1, &stmt, NULL) != SQLITE_OK) {
        LOG_SQLITE3_ERROR(db);
        return ;
    }
    if (sqlite3_bind_text(stmt, 1, Name, -1, SQLITE_STATIC) != SQLITE_OK ||
        sqlite3_bind_int(stmt, 2, HP) != SQLITE_OK ||
        sqlite3_bind_int(stmt, 3, Force) != SQLITE_OK) {
    
        LOG_SQLITE3_ERROR(db);
        sqlite3_finalize(stmt);
        return ;
    }
    if (sqlite3_step(stmt) != SQLITE_DONE) {
        LOG_SQLITE3_ERROR(db);
        sqlite3_finalize(stmt);
        return ;
    }
    sqlite3_finalize(stmt);

}
void AfficherVillage(sqlite3*db){
    sqlite3_stmt* stmt = NULL; 
    const char* query = "SELECT LieuxID,LieuxName,LieuxDescript FROM LIEUX WHERE LieuxID =1"; 

    if(sqlite3_prepare_v2(db, query, -1, &stmt, NULL)!= SQLITE_OK){
        sqlite3_finalize(stmt);
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
void AfficherPNJ(sqlite3*db){
    sqlite3_stmt* stmt = NULL; //initialise ma requete SQL
    const char* query = "SELECT PNJID, PNJNAME, PNJDescript, PNJ Dialogue, LieuxPNJ FROM PNJ WHERE PNJID=15"; //Ce que ma requete fait

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
void AfficherPNJ(sqlite3*db){
    sqlite3_stmt* stmt = NULL; //initialise ma requete SQL
    const char* query = "SELECT PNJID, PNJNAME, PNJDescript, PNJ Dialogue, LieuxPNJ FROM PNJ WHERE PNJID=15"; //Ce que ma requete fait

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
void AfficherQuete(sqlite3*db){
    sqlite3_stmt* stmt = NULL; //initialise ma requete SQL
    const char* query = "SELECT QuetesID, QuetesDescript, QuetesComplete, NPCID FROM QUETES WHERE QuetesID=17"; //Ce que ma requete fait

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
void AfficherQuete2(sqlite3*db){
    sqlite3_stmt* stmt = NULL; //initialise ma requete SQL
    const char* query = "SELECT QuetesID, QuetesDescript, QuetesComplete, NPCID FROM QUETES WHERE QuetesID=18"; //Ce que ma requete fait

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

void AfficherPNJ2(sqlite3*db){
    sqlite3_stmt* stmt = NULL; //initialise ma requete SQL
    const char* query = "SELECT PNJID, PNJNAME, PNJDescript, PNJ Dialogue, LieuxPNJ FROM PNJ WHERE PNJID=16"; //Ce que ma requete fait

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
void AfficherEnnemie1(sqlite3*db){
    sqlite3_stmt* stmt = NULL; //initialise ma requete SQL
    const char* query = "SELECT EnnemisName,EnnemisVie,EnnemisForce,LieuxEnnemis WHERE EnnemisID=10"; //Ce que ma requete fait

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
void AfficherStatEnnemie1(sqlite3*db){
    sqlite3_stmt* stmt = NULL; //initialise ma requete SQL
    const char* query = "SELECT EnnemisVie,EnnemisForce WHERE EnnemisID=10"; //Ce que ma requete fait

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
void AfficherObjects(sqlite3*db){
    sqlite3_stmt* stmt = NULL; //initialise ma requete SQL
    const char* query = "SELECT ObjectsName,ObjectsDescript,LieuxObjects WHERE ObjectsID=5"; //Ce que ma requete fait

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
    srand(time(NULL));
    sqlite3* db = NULL;
    sqlite3_open("./aventure_quete.db",&db);
    AfficherLieux(db);
    // see_state_fruits(db,"FL");
    // see_state_fruits(db,"CA");
    // see_state_fruits(db,"NC");
    // add_random_fruit(db); //Uncomment to add a random fruit...
    int game = 1;
    while(game == 1){

        printf("Creer votre personnage\nEntre le nom de votre personnage\n");
        char Name[64];
        scanf("%s",Name);
        printf("Vous avez 20 point a distribuer pour vos stat\n Entrer vos point de force\n");
        int Force;
        scanf("%d",&Force);
        printf("vos point de vie\n");
        int HP;
        scanf("%d",&HP);
        CreerPerso(db, Name, Force, HP);
        printf("Vous vous reveillez dans un village");
        AfficherVillage(db);
        printf("Vous rencontez un homme\n");
        AfficherPNJ(db);
        AfficherQuete(db);
        printf("1:oui 2:non\n");
        int choice;
        scanf("%d", choice);
        if(choice==2){
            printf("Vous refuser d'aider le Chef et vous quittez le village malheuresement en sortant du village vous rencontrer des loup et vous n'ete pas assez fort pour le vaincre\nGAME OVER\n");
            game = 2;
        }
        printf("Vous voyais les loups\n");
        AfficherEnnemie1(db);
        printf("le combat se lance\n les stats de l'ennemie sont:");
        AfficherStatEnnemie1(db);
        printf("Attaquer\n1:oui 2;non");
        scanf("%d", choice);
        if(choice==2){
            printf("Vous n'avez pas reussi a vous echaper, vous avez succomber\nGAME OVER");
            game = 2;
        }
        if(Force>=3){
            printf("Vous avez reussi a vaincre les loups\n");
        }
        else{
            printf("un loups vous a mordu mais vous avez reussi a le tuer - 2HP\n");
            HP-=2;
        }
        printf("Le Chef vous ofre une epee en guise de remerciment\n");
        AfficherObjects(db);
        printf("Vous faite la rencontre d'un homme misterieux");
        AfficherPNJ2(db);
        AfficherQuete2(db);
        printf("1:oui, 2:non");
        scanf("%d", choice);
        if(choice==2){
            printf("Vous continuez votre aventure malheuresement vous un serpent vous morde vous n'avez aucun moyen de vous soignez\n GAME OVER\n");
            game = 2;
        }
        printf("Vous ramenez les fleurs l'homme vous fabrique des potion capable de soigne n'importe quel blessure\n");
    }
    
    sqlite3_close(db);
    return;
}