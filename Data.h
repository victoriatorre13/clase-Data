#ifndef DATA_H
#define DATA_H
#include <string>
using namespace std;
class Data{
//Aquesta classe representa una data del calendari gregorià igual o posterior al dia 24 de febrer de 1582. 
//Les dates anteriors a aquesta no es consideren vàlides.
//Invariant: els objectes de la classe Data sempre contenen una data vàlida.

    private:
        //------------Atributs----------------
        int dia;
        int mes;
        int any;
        //--------Metodes consultors privats ---------
        int get_nombre_dia_setmana() const;
        //Pre: cert
        //Post: resultat = posició del dia de la setmana, on 0 és dilluns i 6 diumenge
        //-----------------Mètodes de classe privats -----------------
        static bool es_data_valida(int dia, int mes, int any);
        //Pre: cert
        //Post: resultat = cert si i només si la data dia/mes/any és vàlida

        //-------------Constants de classe privades ----------
        static const int MESOS_ANY; //Nombre de mesos de l'any
        static const int DIES_SETMANA; //Nombre de dies de la setmana
        static const int DIES_MES[]; //Nombre de dies de cada mes, assumint que no es any de traspàs
        static const string NOMS_DIES_SETMANA[]; //Noms dels dies de la setmana, la posicio 0 es dilluns i la 6 diumenge
        static const string NOMS_CURTS_DIES_SETMANA[]; //Noms abreviats dels dies de la setmana, la posicio 0 es dilluns i la 6 diumenge
        static const string NOMS_MES[]; //Noms dels mesos de l'any, la posicio 0 es gener i la 11 desembre
        static const int DECALATGE_MARC[]; //Diferència del primer dia del mes respecte el darrer març

    public:
        //------------Constructors------------
        Data();//Constructor per defecte
        //Pre: cert
        //Post: *this representa la data 1/1/2000
        Data(int dia, int mes, int any); //Constructor amb paràmetres
        //Pre: cert
        //Post: *this representa la data dia/mes/any si aquesta és vàlida
        //      altrament representa la data 1/1/2000
        Data(int dia, string mes, int any); //Constructor amb paràmetres
        //Pre: cert
        //Post: *this representa la data dia/mes/any si aquesta és vàlida
        //          mes ha d'estar escrit correctament i en minúscules, març serà marc
        //      altrament representa la data 1/1/2000
        Data(const Data &d); //Constructor de còpia
        //Pre: cert
        //Post: *this representa la data de l'objecte d

        
//--------Mètodes consultors---------
        void escriure() const;
        //Pre: cert
        //Post: escriu per pantalla la data de *this en format dd/mm/aaaa
        int get_dia() const;
        //Pre: cert
        //Post: resultat = dia del mes
        int get_mes() const;
        //Pre: cert
        //Post: resultat = nombre del mes
        int get_any() const;
        //Pre: cert
        //Post: resultat = any
        string get_mes_string() const;
        //Pre: cert
        //Post: resultat = nom del mes
        string get_dia_setmana() const;
        //Pre: cert
        //Post: resultat = nom del dia de la setmana, en minúscules
        bool es_ultim_dia_mes() const;
        //Pre: cert
        //Post: resultat = cert si i només si és l'últim dia del mes
        bool es_cap_de_setmana() const;
        //Pre: cert
        //Post: resultat = cert si i només si la data correspon a dissabte o diumenge
        int edat(const Data &data_avui) const;
        //Pre: cert
        //Post: resultat = edat en data data_avui de la persona nascuda en la data *this
        //---------Mètodes modificadors---------
        void set_dia(int dia);
        //Pre: la data dia/this->get_mes()/this->get_any() és vàlida
        //Post: *this representa la data dia/this->get_mes()/this->get_any()
        void set_mes(int mes);
        //Pre: la data this->get_dia()/mes/this->get_any() és vàlida
        //Post: *this representa la data this->get_dia()/mes/this->get_any()
        void set_any(int any);
        //Pre: la data this->get_dia()/this->get_mes()/any és vàlida
        //Post: *this representa la data this->get_dia()/this->get_mes()/any
        void avanca_un_dia();
        //Pre: *this = *THIS
        //Post: *this representa l'endemà de *THIS

        //-----------------Mètodes de classe-----------------
        static void escriure_calendari(int mes, int any);
        //Pre: mes>=1 i mes <= 12 i  any>=ANY_INICI_CALENDARI
        //Post: escriu per pantalla el calendari del mes $mes de l'any $any
        static void escriure_calendari(int any);
        //Pre: any>=ANY_INICI_CALENDARI
        //Post: escriu per pantalla el calendari de l'any $any
        static bool es_any_de_traspas(int any);
        //Pre: any>=ANY_INICI_CALENDARI
        //Post: resultat = cert si i només si $any és un any de traspàs
        static int dies_mes(int mes, int any);
        //Pre: mes>=1 i mes<=12 i any>=ANY_INICI_CALENDARI
        //Post: resultat =  nombre de dies del mes $mes de l'any $any

        //-------------Constants de classe públiques ----------
        static const int ANY_INICI_CALENDARI; //Any de la primera data vàlida, 1582

};
#endif // DATA_H
