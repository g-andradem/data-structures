#ifndef _REGISTRODEHUMOR_H
#define _REGISTRODEHUMOR_H

extern int IdGlobal;

//Estrutura que define e enumera os humores;
typedef enum humor{
    FELIZ,
    TRISTE,
    ANSIOSO,
    CANSADO,
    MOTIVADO,
    ESTRESSADO,
    NEUTRO,
}Humor;

//Estrutura da data; 
typedef struct data{
    int Dia, Mes, Ano;
}Data;

//Estrutura do registro de humor;
typedef struct registrodehumor{
    int id;
    Data dat;
    Humor animo;
    char Motivo[100];
    int NotaDoDia;
}RegistroDeHumor;

RegistroDeHumor *criarRegistro();
void ImprimirRegistro(RegistroDeHumor *regist);
void LiberarRegistro(RegistroDeHumor *p);

#endif