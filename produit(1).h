 #ifndef PRODUIT_H
#define PRODUIT_H
#include <QString>
#include <QSqlQueryModel>
#include <QTableView>

class Produit
{
public:
    Produit();
    Produit(int,QString,QString,int,QString,QString);

        int getID();
        QString getNom();
        QString getType();
        int getQuantite();
        QString getDelai();
        QString getPrix();

            void setID(int n);
            void setNom(QString n);
            void setType(QString n);
            void setQuantite(int n);
            void setDelai(QString n);
            void setPrix(QString n);

                bool ajouter();
                QSqlQueryModel* afficher();
                bool supprimer(int);
                bool modifier(int);
                void searchRegexp(QTableView *table, int x);
                QSqlQueryModel *rechercheID(QString x);
                QSqlQueryModel * rechercheNom(QString x);
                QSqlQueryModel * rechercheQuantite(QString x);
                QSqlQueryModel * recherchePrix(QString x);
                QSqlQueryModel * trierDelai();
                QSqlQueryModel * trierQuant();
                QSqlQueryModel * trierNom();
                void alerte_fin_stock();


private slots:
void on_recherche_textChanged(const QString &arg1);


private:
    QString Nom, Type, Delai;
    int ID,Quantite;
    QString Prix;
};

#endif // PRODUIT_H
