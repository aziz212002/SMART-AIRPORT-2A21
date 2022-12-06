#include "stat_produit.h"
#include <QSqlQueryModel>
#include <QSqlQuery>


int stat_Produit :: Stat_1()
{

    int count=0 ;
    QSqlQuery requete("select * from Produit where Quantite BETWEEN '0' AND '30' ") ;
    while(requete.next())
    {
            count++ ;
    }

return count ;

}
int stat_Produit :: Stat_2()
{

    int count=0 ;
    QSqlQuery requete("select * from Produit where Quantite BETWEEN '30' AND '60'") ;
    while(requete.next())
    {
            count++ ;
    }

return count ;

}
int stat_Produit :: Stat_3()
{

    int count=0 ;
    QSqlQuery requete("select * from Produit where Quantite BETWEEN '60' AND '9999'") ;
    while(requete.next())
    {
            count++ ;
    }

return count ;


}
