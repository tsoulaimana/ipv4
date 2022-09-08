#include "ipv4.h"



void IPv4::CalculerMasque(unsigned char _cidr)
{
    int indice;
    for(indice = 0; indice < 4; indice++){
        masque[indice] = 0;
    }
    indice = 0;
    while(_cidr >= 8){
        masque[indice++] = 255;
        _cidr -= 8;
    }
    unsigned char puissance = 128;
    while(_cidr-- > 0){
        masque[indice] += puissance;
        puissance /=2;
    }
}

int IPv4::NbButA1(unsigned char val)
{
    int n = 0;
    do{
        n+= val & 1;
    }while(val >>=1 );
    return n;
}

IPv4::IPv4(const unsigned char *_addresse, const unsigned char _cidr)
{
    adresse = new unsigned char [4];
    masque = new unsigned char [4];

    for (int indice = 0; indice < 4; indice++){
        adresse[indice] = _addresse[indice];
        if(_cidr <= 32)
            CalculerMasque(_cidr);
    }
}

IPv4::IPv4(const unsigned char *_addresse, const unsigned char *_masque)
{
    adresse = new unsigned char [4];
    masque = new unsigned char [4];
    for (int indice = 0; indice < 4; indice++){
        adresse[indice] = _addresse[indice];
        masque[indice] = _masque[indice];
    }
}

IPv4::~IPv4()
{
    delete [] adresse;
    delete []masque;

}

void IPv4::ObtenirMasque(unsigned char *_masque)
{
    for(int indice = 0; indice <4; indice++)
        _masque[indice] = masque[indice];
}

void IPv4::ObtenirAddresseReseau(unsigned char *_reseau)
{
    for(int indice = 0 ; indice < 4 ; indice++)
    _reseau[indice] = adresse[indice] & masque[indice] ;
}

void IPv4::ObtenirAdresseDiffusion(unsigned char *_diffusion)
{
    unsigned char adresseDuReseau[4];
    ObtenirAddresseReseau(adresseDuReseau);
    for(int indice = 0 ; indice < 4 ; indice++)
        _diffusion[indice] = adresseDuReseau[indice] | ~masque[indice] ;
}

void IPv4::ObtenirPremiereAdresse(unsigned char *_premiereAdresse)
{
    unsigned char adresseDuReseau[4];
    ObtenirAddresseReseau(adresseDuReseau);
    for(int indice = 0 ; indice < 4 ; indice++)
        _premiereAdresse[indice] = adresseDuReseau[indice] ;
    _premiereAdresse[3]++;
}

void IPv4::ObtenirDerniereAdresse(unsigned char *_derniereAdresse)
{
    unsigned char adresseDeDiffusion[4];
    ObtenirAdresseDiffusion(adresseDeDiffusion);
    for(int indice = 0 ; indice < 4 ; indice++)
        _derniereAdresse[indice] = adresseDeDiffusion[indice];
    _derniereAdresse[3]--;
}

unsigned int IPv4::ObtenirNombreMachine(){
    unsigned int nb = 0;
    for(int i = 0; i<4; i++)
        nb += NbButA1(masque[i]);
    return exp2(32-nb)-2;
}


