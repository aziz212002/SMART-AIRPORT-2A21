#include "connection.h"

Connection::Connection()
{

}

bool Connection::createconnection()

{
    db = QSqlDatabase::addDatabase("QODBC");
    bool test=false;

db.setDatabaseName("source_projet2A");
db.setUserName("ilyess");//inserer nom de l'utilisateur
db.setPassword("ilyess");//inserer mot de passe de cet utilisateur

if (db.open())
test=true;





    return  test;
}
