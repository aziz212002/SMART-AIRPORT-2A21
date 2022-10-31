#include "CONECTION.h"

Connection::Connection()
{

}

bool Connection::createconnect()
{bool test=false;
QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
db.setDatabaseName("source_projet2A");
db.setUserName("mohamedaziz");//inserer nom de l'utilisateur
db.setPassword("aziz12");//inserer mot de passe de cet utilisateur

if (db.open())
test=true;





    return  test;
}
