#include "connection.h"

Connection::Connection()
{

}

bool Connection::createconnect()
{bool test=false;
QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
db.setDatabaseName("projet2A");
db.setUserName("mahmoudi75");//inserer nom de l'utilisateur
db.setPassword("colognalh55");//inserer mot de passe de cet utilisateur

if (db.open())
test=true;





    return  test;
}
