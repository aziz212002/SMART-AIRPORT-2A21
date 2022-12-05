#include "connection.h"

Connection::Connection()
{

}

bool Connection::createconnect()
{bool test=false;
 db = QSqlDatabase::addDatabase("QODBC");
db.setDatabaseName("source_projet2A");
db.setUserName("ilyess");//inserer nom de l'utilisateur
db.setPassword("ilyess");//inserer mot de passe de cet utilisateur

if (db.open())
test=true;


//test


    return  test;
}
void Connection::closeconnect(){db.close();}
