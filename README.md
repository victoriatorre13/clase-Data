#include <iostream>
#include "Data.h"
#include <iostream>
#include <iomanip>
#include <string>
#include <cmath>

using namespace std;
const double p=2.5;

int comptar_dimarts_13(int any) {
    int compt = 0;
    for (int mes = 1; mes <= 12; mes++) {
        Data d(13, mes, any);  // Crear una fecha con el día 13 del mes
        if (d.get_dia_setmana() == "dimarts") {  // Suponiendo que 2 representa martes
            compt++;
        }
    }
    return compt;
}

void examen(Data d, double &punts){
    punts=0;
    int primer_cap,dias_mes,dimars,dias_any;
    cout<<"Quin dia comenca el primer cap de setmana d'aquest mes?"<<endl;
    cin>>primer_cap;
    Data d1=d;
    d1.set_dia(primer_cap);
    if(d1.es_cap_de_setmana()){
        cout<<"Correcte! (+2.5 punts)"<<endl;
        punts+=p;
    }
    else{
        cout<<"Incorrecte!"<<endl;
    }
    cout<<"Quants dies te aquest mes?"<<endl;
    cin>>dias_mes;
    int mes=d.get_mes();
    int any=d.get_any();
    if(dias_mes==d.dies_mes(mes,any)){
        cout<<"Correcte! (+2.5 punts)"<<endl;
        punts+=p;
    }
    else{
        cout<<"Incorrecte!"<<endl;
    }
    cout<<"Quants dimarts 13 hi ha aquest any?"<<endl;
    cin>>dimars;

    int correctes = comptar_dimarts_13(any); // Llamamos a la función

    if (dimars == correctes) {
        cout << "Correcte! (+2.5 punts)" << endl;
        punts += p;
    } else {
    cout << "Incorrecte!" << endl;
    }

    cout<<"Quants dies te aquest any?"<<endl;
    cin>>dias_any;

    if(d.es_any_de_traspas(d.get_any()) && dias_any==366){
        cout<<"Correcte! (+2.5 punts)"<<endl;
        punts+=p;
    }
    else if(!d.es_any_de_traspas(d.get_any()) and dias_any==365){
        cout<<"Correcte! (+2.5 punts)"<<endl;
        punts+=p;
    }
    else{
        cout << "Incorrecte!" << endl;
    }
    cout<<"Examen finalitzat amb "<<punts<<" punts"<<endl;
}

int main()
{
    int dia, mes, any,dia_avui,mes_avui,any_avui;
    cout << "Examen per obtenir el titol de viatger del temps" << endl;
    cout << "Introdueix la teva data de naixement (dd mm aaaa):" << endl;
    cin>>dia>>mes>>any;
    cout << "Introdueix la data d'avui (dd mm aaaa):" << endl;
    cin>>dia_avui>>mes_avui>>any_avui;

    Data p(dia,mes,any);
    Data a(dia_avui,mes_avui,any_avui);

    int edat=p.edat(a);

    if(edat>=18){
        int dia_v,mes_v,any_v;
        double punts;
        cout<<"Tens "<<edat<<" anys"<<endl;
        cout<<"Comencem l'examen"<<endl;
        cout<<"Introdueix la data a on vols viatjar (dd mm aaaa):"<<endl;
        cin>>dia_v>>mes_v>>any_v;
        Data v(dia_v,mes_v,any_v);
        examen(v,punts);
        if (punts<5){
            cout<<"Millor que no t'apropis a cap maquina del temps"<<endl;
        }
        else{
            cout<<"Enhorabona! Has obtingut el titol de viatger del temps"<<endl;
        }
        char c;
        cout<<"Vols veure el calendari per comprovar les teves respostes? (s/n)"<<endl;
        cin>>c;
        if (c=='s'){
            v.escriure_calendari(mes_v,any_v);
        }
    }
    else{
        cout<<"Tens "<<edat<<" anys"<<endl;
        cout<<"No pots conduir una maquina del temps!"<<endl;
    }


    return 0;
}
