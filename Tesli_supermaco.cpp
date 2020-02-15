/********************************************************************
*                         TESLA'S ESCAPE ROOM                       *
*             Proyecto Final. Fundamentos de informática            *
*                           Version 1.0                             *
*              Hecho por: SOFÍA NÚÑEZ Y LAURA MOLINA                *
*         UPC, Profesor: ALFREDO VELLIDO - 18 de Junio de 2017      *
********************************************************************/


#include <iostream>
#include <fstream>
#include <time.h>
#include <windows.h>
#include <conio.h>
#include <cstdlib>
#include <iomanip>
using namespace std;

const int jugadores_max=600;
const int partidas_max=600;
const int reservas_max=600;
const int nranking=10;
const int nMisterios=4;
const int nAcertijos=6;
const int dias_abierto=6;//Abrimos de martes a domingo
const int n_horas_abierto=5; //de 16h a 21h

/////////////////////////////////////////////////////////////DATOS DE JUGADORES//////////////////////////////////////////////////////////////
struct t_jugador
{
    string nom;
    bool m1, m2, m3, m4;
    int puntuacio_total;

};

struct t_lljugadores
{
    int n_real_jugadores;
    t_jugador jugador[jugadores_max];
};

///////////////////////////////////////////////////////////////DATOS DE RESERVA//////////////////////////////////////////////////////////
struct t_data{
int hora,dia,mes;};

struct t_reserva
{
    string qui_reserva, codi_reserva;
    t_data data;
};

struct t_llreserva{
int n_real_reserves;
t_reserva reserva[reservas_max];
};

////////////////////////////////////////////////////////////////DATOS DE RANKING/////////////////////////////////////////////////////////
struct t_ranking{
string nom; int puntuacio;
};

struct t_llranking{
    int n_real_ranking;
    t_ranking ranking[nranking];};

///////////////////////////////////////////////////////////////COLECCIÓN DE ACERTIJOS////////////////////////////////////////////////////////
typedef string palabras [1000];

typedef string answer [50];

struct t_acertijo
{
    palabras p, ambientacion;
    answer a;
    int n_palabras, n_p_ambientacion;
};

struct t_misterio
{
    t_acertijo acertijo[nAcertijos];
};

struct t_llmisterios
{
    t_misterio misterio[nMisterios];
};

//////////////////////////////////////////////////////////////DATOS DE ESTRUCTURAS EN GENERAL////////////////////////////////////////////
struct t_todo{
t_lljugadores lljugadors;
t_llreserva llreserva;
t_llranking llranking;
t_llmisterios llmisterios;
palabras codis;
};

//////////////////////////////////////////////////////////////ENCABEZADO DE SUBPROGRAMAS//////////////////////////////////////////////////////
void gotoxy(int x,int y);
char menu();
void rellenar_datos(t_todo&t);
void rellenar_lljugadors(t_todo&t);
void rellenar_llreserva(t_todo&todo);
void rellenar_llranking(t_todo&todo);
void rellenar_acertijos(t_todo&t);
void rellenar_soluciones(t_todo&t);
void rellenar_codis(t_todo&t);

bool nombre_yaUsado(t_todo&tt, string nom);
void nuevo_usuario(t_todo&j);

void cuenta_atras(int mseconds);
bool verificacion_codi (t_todo todo, string c);
void jugarmisterio(t_todo todo, int& puntuation, int num_misterio);
void jugar(t_todo& g);

int maximo (t_todo todo);
string maximo_nom (t_todo todo);
void ranking_top10(t_todo todo);
bool ocupacio (t_todo todo, int m, int d,int h);
void reservar_sala(t_todo todo);

void dibujo_alien();
void dibujo_torre();
void dibujo_Tesla();


//////////////////////////////////////////////////////////////////INT MAIN///////////////////////////////////////////////////////////////////
int main ()
{
    t_todo todo;
    rellenar_datos(todo);

    char opcion =0;
    while(opcion != '5'){
        opcion = menu();
        switch(opcion){
            case '1':nuevo_usuario(todo);
            break;
            case '2':jugar(todo);
            break;
            case '3':ranking_top10(todo);
            break;
            case '4':reservar_sala(todo);
            break;
            case '5':cout<<"Hasta la proxima! " <<endl<<endl;
            break;
            default: cout<< "Error ......"<<endl<<endl;
        }
        cout<<"Para volver al inicio y elegir otra opcion, pulse una tecla"<<endl; getch();
    }
}

//////////////////////////////////////////////////////////////////SUBPROGRAMAS////////////////////////////////////////////////////////////////
void gotoxy(int x,int y){
 HANDLE consola; COORD posicion;
 consola = GetStdHandle(STD_OUTPUT_HANDLE);
 posicion.X= x; posicion.Y= y;
 SetConsoleCursorPosition(consola, posicion);
}

char menu(){
     char opcion=0;
     system("cls");
     //gotoxy (60,1); dibujo_Tesla();
     gotoxy (45,5); cout<<"TESLA'S ESCAPE ROOM"<<endl;
     gotoxy (45,8); cout<<"1) Nuevo usuario"<<endl;
     gotoxy (45,9); cout<<"2) Jugar"<<endl;
     gotoxy (45,10); cout<<"3) Ranking"<<endl;
     gotoxy (45,11); cout<<"4) Reservar sala"<<endl;
     gotoxy (45,12); cout<<"5) Salir"<<endl;
     gotoxy (45,15); cout <<"Elija una opcion: ";
     opcion =getche();
     system("cls");
     return opcion;
}
///////////////////////////////////////////////////////////////////RELLENAR DATOS//////////////////////////////////////////////////////////////
void rellenar_datos(t_todo&t)
{
    rellenar_lljugadors(t);
    rellenar_llreserva(t);
    rellenar_llranking(t);
    rellenar_acertijos(t);
    rellenar_soluciones(t);
    rellenar_codis(t);
}

void rellenar_lljugadors(t_todo&t)
{
    ifstream fin ("e_lljugadors.txt");
    int N;
    fin>>N;
    t.lljugadors.n_real_jugadores=N;

    int k=0;
    string usuari;
    bool misteri1,misteri2,misteri3,misteri4;
    int puntuacio;
    while (!fin.eof())
    {
        fin>>usuari;
        t.lljugadors.jugador[k].nom=usuari;
        fin>>misteri1;
        t.lljugadors.jugador[k].m1=misteri1;
        fin>>misteri2;
        t.lljugadors.jugador[k].m2=misteri2;
        fin>>misteri3;
        t.lljugadors.jugador[k].m3=misteri3;
        fin>>misteri4;
        t.lljugadors.jugador[k].m4=misteri4;
        fin>>puntuacio;
        t.lljugadors.jugador[k].puntuacio_total=puntuacio;
        k++;
    }
}

void rellenar_llreserva(t_todo&t)
{
    ifstream fin ("e_llreserva.txt");

    int N;
    fin>>N;
    t.llreserva.n_real_reserves=N;

    int i;
    string reservador, key;
    int h, d, m;
    for (i=0; !fin.eof(); i++)
    {
        fin>>reservador;
        t.llreserva.reserva[i].qui_reserva=reservador;
        fin>>key;
        t.llreserva.reserva[i].codi_reserva=key;
        fin>>h;
        t.llreserva.reserva[i].data.hora=h;
        fin>>d;
        t.llreserva.reserva[i].data.dia=d;
        fin>>m;
        t.llreserva.reserva[i].data.mes=m;
    }

}

void rellenar_llranking(t_todo&t)
{
    ifstream fin ("e_llranking.txt");

    int N;
    fin>>N;
    t.llranking.n_real_ranking=N;

    int b;
    string usuario;
    int punts;
    for (b=0; !fin.eof(); b++)
    {
        fin>>usuario;
        t.llranking.ranking[b].nom=usuario;
        fin>>punts;
        t.llranking.ranking[b].puntuacio=punts;
    }

}

void rellenar_ambientacion (t_todo&t)
{
    ifstream fin("e_ambientacion.txt");

    int cont=0;
    string pal;
    bool stop=false;
    for (int i=0; i<nMisterios; i++)
    {
        for (int j=0; j<nAcertijos; j++)
        {
            for (int k=0; k<1000 and !stop; k++)
            {
                fin>>pal;
                if (pal!="/")
                {
                    t.llmisterios.misterio[i].acertijo[j].ambientacion[k]=pal;
                    cont++;
                }
                else
                {
                    stop=true;
                    t.llmisterios.misterio[i].acertijo[j].n_p_ambientacion=cont;
                }
            }
        }
    }

}

void rellenar_acertijos(t_todo&t)
{
    ifstream fin ("e_acertijos.txt");

    int cont=0;
    string pal;
    bool stop=false;
    for (int i=0; i<nMisterios; i++)
    {
        for (int j=0; j<nAcertijos; j++)
        {
            for (int k=0; k<1000 and !stop; k++)
            {
                fin>>pal;
                if (pal!="/")
                {
                    t.llmisterios.misterio[i].acertijo[j].p[k]=pal;
                    cont++;
                }
                else
                {
                    stop=true;
                    t.llmisterios.misterio[i].acertijo[j].n_palabras=cont;
                }
            }
        }
    }

}

void rellenar_soluciones(t_todo&t)
{
    ifstream fin ("e_soluciones.txt");

    int cont=0;
    string pal;
    bool stop=false;
    for (int i=0; i<nMisterios; i++)
    {
        for (int j=0; j<nAcertijos; j++)
        {
            for (int k=0; k<50 and !stop; k++)
            {
                fin>>pal;
                if (pal!="%")
                {
                    t.llmisterios.misterio[i].acertijo[j].a[k]=pal;
                    cont++;
                }
                else
                {
                    stop=true;
                    t.llmisterios.misterio[i].acertijo[j].n_palabras=cont;
                }
            }
        }
    }

}

void rellenar_codis(t_todo&t)
{
    ifstream fin ("e_codis.txt");

    int c;
    string key;
    for (c=0; !fin.eof(); c++)
    {
        fin>>key;
        t.codis[c]=key;
    }
}

////////////////////////////////////////////////////////////SUBPROGRAMAS NUUEVO USUARIO////////////////////////////////////////////////////////////////////////

bool nombre_yaUsado(t_todo&tt, string nom)
{
   int i;
   bool usado=false;
   for (i=0; i<tt.lljugadors.n_real_jugadores; i++)
   {
       if (nom==tt.lljugadors.jugador[i].nom) usado=true;
   }
   return usado;
}

void nuevo_usuario(t_todo&j)
{
    int i,y=1;
    string nuevo_nombre;
    bool nou_nom=false;
    gotoxy(5,y); cout<<"Introduce nuevo usuario: "<<endl;
    gotoxy(30,y); cin>>nuevo_nombre;
    y+=2;
    while(nombre_yaUsado(j,nuevo_nombre))
    {
        gotoxy(5,y);cout << "Este nombre ya esta en uso. Elija otro nombre.." << endl; y++;
        gotoxy(5,y);cin>>nuevo_nombre; y+=2;
    }

        gotoxy(5, y++); cout <<"Nombre de usuario correcto";
        gotoxy(5,y+2); cout<< "Bienvenido a TESLA'S ESCAPE ROOM !!" << endl << endl;

}

///////////////////////////////////////////////////////////SUBPROGRAMAS DE JUGAR/////////////////////////////////////////////////////////////////////
void cuenta_atras(int mseconds)
{
clock_t goal = mseconds + clock();
while (goal > clock());
}

bool verificacion_codi (t_todo todo, string c){
bool ok=false;

for (int i=0; i<todo.llreserva.n_real_reserves;i++){

    if (c==todo.llreserva.reserva[i].codi_reserva) ok=true;
}return ok;
}

void jugarmisterio(t_todo todo, int& puntuation, int num_misterio){
    cuenta_atras(2400000);
    answer resposta;

    for (int medio=0; medio<2; medio++)
    {
        for (int f=0; f<todo.llmisterios.misterio[num_misterio].acertijo[medio].n_p_ambientacion; f++)cout<<todo.llmisterios.misterio[num_misterio].acertijo[medio].ambientacion;
        for (int g=0; g<todo.llmisterios.misterio[num_misterio].acertijo[medio].n_palabras; g++) cout<<todo.llmisterios.misterio[num_misterio].acertijo[medio].p[g];
        cuenta_atras(600000);
        for (int w=0; w<50; w++) cin>>resposta[w];
        //verificar respuesta
    }

    //elegir master o nivel bajo
    //si acierta los dos acertijos
    {
        for (int master=4; master<6; master++)
        {
            for (int f=0; f<todo.llmisterios.misterio[num_misterio].acertijo[master].n_p_ambientacion; f++)cout<<todo.llmisterios.misterio[num_misterio].acertijo[master].ambientacion;
            for (int g=0; g<todo.llmisterios.misterio[num_misterio].acertijo[master].n_palabras; g++) cout<<todo.llmisterios.misterio[num_misterio].acertijo[master].p[g];
            cuenta_atras(600000);
            for (int w=0; w<50; w++) cin>>resposta[w];
        }
    }
    //si acierta solo una o ninguna
    {
        for (int bajo=2; bajo<4; bajo++)
        {
            for (int f=0; f<todo.llmisterios.misterio[num_misterio].acertijo[bajo].n_p_ambientacion; f++)cout<<todo.llmisterios.misterio[num_misterio].acertijo[bajo].ambientacion;
            for (int g=0; g<todo.llmisterios.misterio[num_misterio].acertijo[bajo].n_palabras; g++) cout<<todo.llmisterios.misterio[num_misterio].acertijo[bajo].p[g];
            cuenta_atras(600000);
            for (int w=0; w<50; w++) cin>>resposta[w];
        }
    }
};

typedef string gamerss[5];

void jugar(t_todo& g)
{  int p;
   gamerss gamers;
   bool b1=false,b2=false,b3=false,b4=false, correcto=false;
   int y=3, num_jugadores;
   string codi_reserva, usuari;
   answer respuesta;

   gotoxy(5,1); cout<<"Antes de empezar la partida, introduce los siguientes datos:";
   gotoxy(10,3); cout<<"Codigo de reserva: ";
   gotoxy(29,y); cin>>codi_reserva; y+=2;
   //verificacion que es el codigo correcto
   correcto= verificacion_codi(g, codi_reserva);
   while (!correcto){
     gotoxy(10,y);cout << "Codigo de reserva no valido, introduzca otro codigo: " << endl;
     gotoxy(63,y); cin >> codi_reserva; y+=2;
     correcto= verificacion_codi(g, codi_reserva);
   }
    y+=2;
   gotoxy(10,y); cout<<"Numero de usuarios: ";
   gotoxy(30,y); cin>>num_jugadores; y++;
   while(num_jugadores<=0 or num_jugadores>5)
   {
       gotoxy(10,y); cout<<"Numero de jugadores no valido. Vuelve a introducir un numero de jugadores valido," ; y++;
       gotoxy(10,y); cout<<"recuerda que pueden jugar hasta un maximo de 5 jugadores"; y++;
       gotoxy(10,y); cin>>num_jugadores; y++;
   }
   y+=2;
   gotoxy(10,y); cout<<"Nombres de los usuarios: ";

   for (int v=0; v<num_jugadores; v++)
   {
      y+=v;
      gotoxy(35,y); cin>>usuari;
      gamers[v]=usuari;
   }
   y+=num_jugadores+2;

   gotoxy (5,y); cout<<"INICIO DE PARTIDA"<<endl<<endl;

   //Miramos que misterios ya han sido jugados por nustro usuario
   for (int i=0; i<g.lljugadors.n_real_jugadores;i++){
        for (int j=0; j<5;j++){
        if (g.lljugadors.jugador[i].nom==gamers[j]){
        if (g.lljugadors.jugador[i].m1) b1=true;
        if (g.lljugadors.jugador[i].m2) b2=true;
        if (g.lljugadors.jugador[i].m3) b3=true;
        if (g.lljugadors.jugador[i].m4) b4=true;
     }}}

     if (b1&&b2&&b3&&b4) {cout << "No podemos ofrecer nuevos acertijos a estos usuarios." << endl;
     cout<<"Para volver al inicio y elegir otra opcion, pulse una tecla"<<endl; getch();}

     //misterio 1
     else if (!b1){
        jugarmisterio(g,p,1);
     }

     //misterio 2
     else if (!b2){
        jugarmisterio(g,p,2);

     }

     //misterio 3
      else if (!b3){
        jugarmisterio(g,p,3);

     }

     //misterio 4
     else {
        jugarmisterio(g,p,4);

     }

     //sumamos puntuacion a nuestros usuarios

     for (int i=0; i<g.lljugadors.n_real_jugadores;i++){
        for (int j=0; j<5;j++){
     if (g.lljugadors.jugador[i].nom==gamers[j]){
        g.lljugadors.jugador[i].puntuacio_total+=p;
     }
     }
     }

     cout << "Partida finalizada. Esperamos que se lo hallan pasado en grande" << endl;
     cout << "Han obtenido una puntuacion de:  " << p << endl << "Hasta la proxima!" << endl;
}

///////////////////////////////////////////////////////////////////////SUBPROGRAMAS DE RANKING///////////////////////////////////////////////////
int maximo (t_todo todo){
int maxi;

for (int i=0; i<todo.lljugadors.n_real_jugadores;i++){
    if (todo.lljugadors.jugador[i].puntuacio_total>=maxi){maxi=todo.lljugadors.jugador[i].puntuacio_total;}
}return maxi;}

string maximo_nom (t_todo todo){
int maxi;
string maxinom;

for (int i=0; i<todo.lljugadors.n_real_jugadores;i++){
    if (todo.lljugadors.jugador[i].puntuacio_total>=maxi){
            maxi=todo.lljugadors.jugador[i].puntuacio_total;
            maxinom=todo.lljugadors.jugador[i].nom;}
}return maxinom;}

void ranking_top10(t_todo todo)
{
    gotoxy(5,2); cout<<"** TOP 10 MEJORES JUGADORES **"<<endl<<endl;

    for (int i=0;i<todo.llranking.n_real_ranking;i++){

        if (maximo(todo)>todo.llranking.ranking[i].puntuacio){
                todo.llranking.ranking[i].puntuacio=maximo(todo);
                todo.llranking.ranking[i].nom=maximo_nom(todo);
                todo.llranking.n_real_ranking++;
        }}

        for (int k=0;k<todo.llranking.n_real_ranking;k++){

            gotoxy(5,7); cout << todo.llranking.ranking[k].nom << "  con la puntuacion:  " << todo.llranking.ranking[k].puntuacio << endl;
        }
}

//////////////////////////////////////////////////////////////////////SUBPROGRAMAS DE RESERVAS//////////////////////////////////////////////////
bool ocupacio (t_todo todo, int m, int d,int h){
bool trobat=false;

for (int i=0; i<todo.llreserva.n_real_reserves and !trobat;i++){

    if (m==todo.llreserva.reserva[i].data.mes && d==todo.llreserva.reserva[i].data.dia && h==todo.llreserva.reserva[i].data.hora){
      trobat =true;
    }
}

return trobat;
}


void reservar_sala(t_todo todo)
{
    int mes_u,dia_u,hora_u; string nombre;
    bool ocupat=false;

    gotoxy(5,2); cout<<" Disponibilidad de la sala "<<endl<<endl;

    cout << "Introduzca mes, dia y hora :" << endl;
    cin>> mes_u>>dia_u>>hora_u;
    ocupat= ocupacio(todo,mes_u,dia_u,hora_u);

    while (ocupat){
        cout<< "  Hora NO disponible, porfavor introducir otra fecha: " << endl;
        cin>> mes_u>>dia_u>>hora_u;
        ocupat= ocupacio(todo,mes_u,dia_u,hora_u);
    }

    if (!ocupat){ cout << " Hora DISPONIBLE ! " << endl;

    cout << "Introducir su nombre:" << endl;
    cin>>nombre;



    todo.llreserva.reserva[todo.llreserva.n_real_reserves].qui_reserva=nombre;
    todo.llreserva.reserva[todo.llreserva.n_real_reserves].data.mes=mes_u;
    todo.llreserva.reserva[todo.llreserva.n_real_reserves].data.dia=dia_u;
    todo.llreserva.reserva[todo.llreserva.n_real_reserves].data.hora=hora_u;
    todo.llreserva.reserva[todo.llreserva.n_real_reserves].codi_reserva=todo.codis[todo.llreserva.n_real_reserves];
    todo.llreserva.n_real_reserves++;

    cout << " Su codigo de reserva de sala es : " << todo.codis[todo.llreserva.n_real_reserves] << endl << endl;
}}
/////////////////////////////////////////////////////////////////////////////ARTE C++////////////////////////////////////////////////////////////////
void dibujo_alien()
{
    cout<<endl;
    cout<<"                      $$$$$$$$$$$$                             "<<endl;
    cout<<"                   $$$$$$$$$$$$$$$$$$                          "<<endl;
    cout<<"                 $$$$$$$$$$$$$$$$$$$$$$$                       "<<endl;
    cout<<"               $$$$$$$$$$$$$$$$$$$$$$$$$$                      "<<endl;
    cout<<"              $$$$$$$$$$$$$$$$$$$$$$$$$$$$                     "<<endl;
    cout<<"             $$$$$__$$$$$$$$$$$$$$$$__$$$$$                    "<<endl;
    cout<<"             $$$$_____$$$$$$$$$$$$_____$$$$                    "<<endl;
    cout<<"             $$$$$_____$$$$$$$$$$_____$$$$$                    "<<endl;
    cout<<"              $$$$$____$$$$$$$$$$____$$$$$                     "<<endl;
    cout<<"               $$$$$$__$$$$$$$$$$__$$$$$$                      "<<endl;
    cout<<"                 $$$$$$$$$$$$$$$$$$$$$$                        "<<endl;
    cout<<"                   $$$$$$$$$$$$$$$$$$                          "<<endl;
    cout<<"                    $$$$$$$$$$$$$$$$                           "<<endl;
    cout<<"                      $$$------$$$                             "<<endl;
    cout<<"                       $$$$$$$$$$                              "<<endl;
    cout<<"                        $$$$$$$$                               "<<endl;
    cout<<"                         %%%%%%                                "<<endl;
    cout<<"                        %%%%%%%%                               "<<endl;
    cout<<"                      %%%%%%%%%%%%                             "<<endl;

}

void dibujo_torre()
{
    cout<<"                               *      *      *                           "<<endl;
    cout<<"                         *      *     *     *       *                    "<<endl;
    cout<<"                           *     *    *    *      *                      "<<endl;
    cout<<"                    *        *    *   *   *     *        *               "<<endl;
    cout<<"                        *      *   * %%% *   *      *                    "<<endl;
    cout<<"                             *   * %((|))% *   *                         "<<endl;
    cout<<"                                * %(((|)))% *                            "<<endl;
    cout<<"                *   *   *   *   * %%%%%%%%% *   *   *   *   *            "<<endl;
    cout<<"                                     %%%                                 "<<endl;
    cout<<"                                     %%%                                 "<<endl;
    cout<<"                                    % % %                                "<<endl;
    cout<<"                                   %><%><%                               "<<endl;
    cout<<"                                   %  %  %                               "<<endl;
    cout<<"                                   %><%><%                               "<<endl;
    cout<<"                                   %  %  %                               "<<endl;
    cout<<"                                   %><%><%                               "<<endl;
    cout<<"                                   %  %  %                               "<<endl;
    cout<<"                                   %><%><%                               "<<endl;
}

void dibujo_Tesla()
{
    cout<<endl;
    cout<<"                                                     "<<endl;
    cout<<"                NNNNNNN>NNNNNNNNNN                   "<<endl;
    cout<<"               NNNNNNNN>NNNNNNNNNN                   "<<endl;
    cout<<"               NNNNNNNN>NNNNNNNNNN                   "<<endl;
    cout<<"               NN                N                   "<<endl;
    cout<<"               NN                N                   "<<endl;
    cout<<"               NN  =====   ===== N                   "<<endl;
    cout<<"                N   __       __  N                   "<<endl;
    cout<<"                || < 0> | | < 0> |                   "<<endl;
    cout<<"                |]|     | |      |                   "<<endl;
    cout<<"                |]{|    | |      }                   "<<endl;
    cout<<"                |]|     | |      |                   "<<endl;
    cout<<"                |]]|   <. .>     |                   "<<endl;
    cout<<"                 ]]{| MMMMMMM    |                   "<<endl;
    cout<<"                 |]|    ---     |                    "<<endl;
    cout<<"                   |           |                     "<<endl;
    cout<<"                     ||      ||                      "<<endl;
    cout<<"                       |||||                         "<<endl;
    cout<<"                                                     "<<endl;
}



