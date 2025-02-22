#include "Data.h"
#include <iostream>
#include <iomanip>
#include <string>
#include <cmath>

using namespace std;

//------------Constants de classe------------
const int Data::MESOS_ANY = 12;
const int Data::DIES_SETMANA = 7;
const int Data::DIES_MES[] = {31,28,31,30,31,30,31,31,30,31,30,31};
const string Data::NOMS_DIES_SETMANA[] = {"dilluns", "dimarts", "dimecres", "dijous", "divendres", "dissabte", "diumenge"};
const string Data::NOMS_CURTS_DIES_SETMANA[] = {"dl", "dm", "dc", "dj", "dv", "ds", "dg"};
const string Data::NOMS_MES[] = {"gener", "febrer", "marc", "abril", "maig", "juny", "juliol", "agost", "setembre", "octubre", "novembre", "desembre"};
const int Data::DECALATGE_MARC[] = {5,1,0,3,5,1,3,6,2,4,0,2};
const int Data::ANY_INICI_CALENDARI=1582;


//------------Constructors------------
Data::Data() : dia(1), mes(1), any(2000) 
{

}

Data::Data(int dia, int mes, int any) : dia(dia), mes(mes), any(any) 
{
    if (not es_data_valida(dia, mes, any)) {
        this->dia = 1;
        this->mes = 1;
        this->any = 2000;
    }
}

Data::Data(int dia, string mes, int any) : dia(dia), mes(0), any(any) 
{
    while (this->mes < MESOS_ANY && mes != NOMS_MES[this->mes]) {
        this->mes++;
    }
    this->mes++;

    if (not es_data_valida(dia, this->mes, any)) {
        this->dia = 1;
        this->mes = 1;
        this->any = 2000;
    }
}

Data::Data(const Data &d) : dia(d.dia), mes(d.mes), any(d.any) 
{

}

//------------Metodes privats------------
int Data::get_nombre_dia_setmana() const 
{
//Adaptat de la implementació de Tomohiko Sakamoto
//https://en.wikipedia.org/wiki/Determination_of_the_day_of_the_week
//Per fer el càlcul més fàcil, considerem que l’any comença al març
//D’aquesta manera, el 28 o 29 de febrer és l’últim dia de l’any
//i el decalatge de cada mes no varia si és any de traspàs
    int a = any;
    if (mes < 3)
        a--;
    return (a + a/4 - a/100 + a/400 + DECALATGE_MARC[mes-1] + dia + 1) % DIES_SETMANA;
}

bool Data::es_data_valida(int dia, int mes, int any) 
{
    return  any >= ANY_INICI_CALENDARI
        and mes >= 1 and mes <= MESOS_ANY
        and dia >= 1 and dia <= dies_mes(mes,any);
}

//--------Mètodes consultors---------
void Data::escriure() const 
{
    cout << setfill('0') << setw(2) << dia;
    cout << "/" << setfill('0') << setw(2) << mes;
    cout << "/" << setfill('0') << setw(4) << any;
}

int Data::get_dia() const 
{
    return dia;
}

int Data::get_mes() const 
{
    return mes;
}

int Data::get_any() const 
{
    return any;
}

string Data::get_mes_string() const 
{
    return NOMS_MES[mes - 1];
}

string Data::get_dia_setmana() const 
{
    return NOMS_DIES_SETMANA[get_nombre_dia_setmana()];
}

bool Data::es_ultim_dia_mes() const 
{
    return dia == dies_mes(mes, any);
}

bool Data::es_cap_de_setmana() const 
{
    int dia_setmana = get_nombre_dia_setmana();
    return dia_setmana == 5 || dia_setmana == 6;
}  

int Data::edat(const Data &data_avui) const 
{
    int edat = data_avui.any - any;
    if (data_avui.mes < mes || (data_avui.mes == mes && data_avui.dia < dia)) edat--;
    return edat;
}

//--------Mètodes modificadors---------
void Data::set_dia(int dia) 
{
    this->dia = dia;
}

void Data::set_mes(int mes) 
{
    this->mes = mes;
}

void Data::set_any(int any) 
{
    this->any = any;
}

void Data::avanca_un_dia() 
{
    dia++;
    if (dia > dies_mes(mes, any)) {
        dia = 1;
        mes++;
        if (mes > MESOS_ANY) {
            mes = 1;
            any++;
        }
    }
}   

void Data::escriure_calendari(int any){
    for(int mes = 1; mes <= MESOS_ANY; mes++) {
        escriure_calendari(mes, any);
    }
}

void Data::escriure_calendari(int mes, int any)
{
    //Ratlla separadora    
    for(int i = 0; i < DIES_SETMANA*3; i++)
        cout << "-";
    cout << endl;

    //Nom del mes i any
    cout << NOMS_MES[mes - 1] << " " << any <<  endl;

    //Ratlla separadora
    for(int i = 0; i < DIES_SETMANA*3; i++)
        cout << "-";
    cout << endl;

    //Noms dels dies de la setmana
    for(int i = 0; i < DIES_SETMANA; i++)
        cout << NOMS_CURTS_DIES_SETMANA[i] << " ";
    cout << endl;
    
    //Calculem en quin dia de la setmana cau el primer dia del mes
    Data inici(1,mes,any);
    int dia_de_setmana=inici.get_nombre_dia_setmana();

    //Espais en blanc fins al primer dia del mes
    for(int i = 0; i< dia_de_setmana; i++) 
        cout << "   ";
    
    //Mostrem els dies del mes
    int nombre_dies_mes = dies_mes(mes, any);
    for(int dia = 1; dia <= nombre_dies_mes; dia++) {
        if(dia < 10) cout << " ";
        cout << dia << " ";
        dia_de_setmana++;
        if (dia_de_setmana == DIES_SETMANA) {
            cout << endl;
            dia_de_setmana = 0;
        }
    }
    //Acabem la setmana si el mes no acaba en diumenge
    if(dia_de_setmana!=0) cout << endl; 

    //Ratlla separadora
    for(int i = 0; i < DIES_SETMANA*3; i++)
        cout << "-";
    cout << endl;
}

bool Data::es_any_de_traspas(int any) 
{
    return (any % 4 == 0 && any % 100 != 0) || any % 400 == 0;
}

int Data::dies_mes(int mes, int any) 
{
    int dies = DIES_MES[mes - 1];
    if (mes == 2 && es_any_de_traspas(any)) dies++;
    return dies;
}