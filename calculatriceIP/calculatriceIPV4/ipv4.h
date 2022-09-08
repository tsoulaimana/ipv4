#ifndef IPV4_H
#define IPV4_H

#include <math.h>

class IPv4
{
private:
    int NbButA1(unsigned char val);
    unsigned char * adresse;
    unsigned char * masque ;
    void CalculerMasque(unsigned char _cidr);
public:
    IPv4(const unsigned char *_addresse, const unsigned char _cidr);
    IPv4(const unsigned char *_addresse, const unsigned char *_masque);
    ~IPv4();
    void ObtenirMasque(unsigned char *_masque);
    void ObtenirAddresseReseau(unsigned char *_reseau);
    void ObtenirAdresseDiffusion(unsigned char *_diffusion);
    void ObtenirPremiereAdresse(unsigned char *_premiereAdresse);
    void ObtenirDerniereAdresse(unsigned char *_derniereAdresse);
    unsigned int ObtenirNombreMachine();

};

#endif // IPV4_H
