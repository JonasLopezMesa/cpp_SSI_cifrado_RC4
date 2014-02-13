//
//  main.cpp
//  Cifrado_RC4
//
//  Created by jonas on 25/02/13.
//  Copyright (c) 2013 jonas. All rights reserved.
//

#include <iostream>
#include <vector>
#include <string.h>
#include "dectobin.h"
#include <stdlib.h>
using namespace std;

#define length(x) (sizeof(x)/sizeof(x[0]))
#define  Entero_A_Caracter(entero) entero+0x30

int S[256] = {0};
int K[256] = {0};
int S1[256] = {0};
int K1[256] = {0};
int semilla[256];
int size_semilla = 0;

//funciones utilizadas en el código
void intercambiar(int si, int sj/*, int* S*/);
void inicializar();
int generar_secuencia();

void intercambiar(int si, int sj/*, int* S*/) { //intercambia dos elementos del vector
    int temp = S[si];
    S[si] = S[sj];
    S[sj] = temp;
}

void inicializar() { //Primer algoritmo de inicializar 
    for (int i = 0; i < 256; i++) { //recorre los vectores S y K
        S[i] = i; //inicializa cada elemento de vector con números consecutivos del 0 al 255
        K[i] = semilla[i%size_semilla]; //inicializa cada elemento del vector con lo que hay en semilla, repitiendose tantas veces como sea necesario, para ello está el módulo de la longitud del vector semilla.
        
        S1[i] = i;
        K1[i] = semilla[i%size_semilla];
    }
    int j = 0;
    for (int i = 0; i < 256; i++) { 
        j = (j + S[i] + K[i])%256; //asigna a j el elemento correspondiente a la S[i] y a la clave de K
        intercambiar(i, j/*, S*/); //intercambia la j por la i
    }
}

int generar_secuencia(){
    int i = 0; int j = 0;
    i = (i + 1)%256;  //se le da a i su valor más uno y que se vaya repitiendo en módulo 256
    j = (j + S[i])%256; //se le da a j su valor más lo que haya en S[i]
    intercambiar(i, j/*, S*/); //se intercambian la S[i] por la S[j]
    int t = (S[i]+S[j])%256;
    return t; //la función devuelve la suma de S[i]+S[j], siempre dentro del vector usando el módulo.
}

int main()
{
    //////////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////////
    int mensaje[256];
    cout << "Introduce el mensaje: (introduce -1 para dejar de introducir datos)" << endl;
    int pr = 0;
    int p = 0;
    while (pr != -1){ //introducir los valores del mensaje por teclado.
        cin >> pr;
        if (pr != -1) { //parar con el -1
            mensaje[p] = pr;
            p++;
        }
    }
    int size;
    for (int i = 0; i < 256; i++) { //calculo del tamaño de los valores válidos del mensaje
        if (mensaje[i] == '\0') {
            size = i;
            i = 256;
        }
    }
    //////////////////////////////////////////////////////////////////////////////////////////////
    cout << "Introduce la semilla: (introduce -1 para dejar de introducir datos)" << endl;
    int xi = 0;
    int m = 0;
    while (xi != -1) {
        cin >> xi;
        if (xi != -1) {
            semilla[m] = xi;
            m++;
        }
    }
    for (int i = 0; i < 256; i++) { //calculo del tamaño de los valores válidos de la semilla
        if (semilla[i] == '\0') {
            size_semilla = i;
            i = 256;
        }
    }
    //////////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////////
    inicializar(); //uso de la función inicializar.
    /*for (int i = 0; i < 256; i++) { //Mostrar el mensaje de salida
        cout << "S[" << i << "]= " << S1[i] << ", K[" << i << "]= " << K1[i] << " produce f = " << S[i] << ", S["<<i <<"] = " <<S[i] <<", S[" <<S[i] <<"] =" << S[S[i]] << endl;
    }*/
    for (int i = 0; i < 256; i++) {
        cout << S[i] << ", ";
    }
    cout << endl;
    cout << endl;
    for (int i = 0; i < 256; i++) {
        cout << K[i] << ", ";
    }
    
    
    
    int sec;
    cout << endl;
    int a = 0; int b = 0;
    //////////////////////////////////////////////////////////////////////////////////////////////
    for (int i = 0; i < size; i++) { //generar la secuencia cifrante por cada uno de los elementos del mensaje.
        //GENERAR SECUENCIA
        a = (a + 1)%256;  //se le da a i su valor más uno y que se vaya repitiendo en módulo 256
        b = (b + S[a])%256; //se le da a j su valor más lo que haya en S[i]
        intercambiar(a, b/*, S*/); //se intercambian la S[i] por la S[j]
        sec = (S[a]+S[b])%256;
        
        //sec = generar_secuencia();
        cout << "Byte " << i+1 << " de secuencia cifrante: Salida= S[" << sec << "] = " << S[sec] << "->" << '\t'<< '\t'<< '\t'; binario2(S[sec],0); cout << endl;
        cout << "Byte " << i+1 << " de texto original: Entrada= M[" << i << "] = " << mensaje[i] << "->" << '\t'<< '\t'<< '\t'<< '\t'; binario2(mensaje[i],0); cout << endl;
        int ixor = S[sec] ^ mensaje[i];
        cout << "Byte " << i+1 << " de texto cifrado: Salida= C[" << i << "] = " << ixor << "->" << '\t'<< '\t'<< '\t'<< '\t'; binario2(ixor, 0); cout << endl;
    }
    

}

