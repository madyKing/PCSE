#ifndef _TIME_H
#define _TIME_H
#include <inttypes.h>
#include <stdbool.h>

extern void traitant_IT_32(void) ;
/***
* Démasquage de l'IRQ0 pour autoriser les signaux en provenance de l'horloge
 ***/
void masque_IRQ(uint32_t num_IRQ, bool masque);

/***
* fonction pour écrire en haut à droite de l'écran
***/
void ecrit_haut_droite (char *car);

/**
*fonction qui retourne le nombre de secondes depuis le démarrage du systeme
*/
uint32_t nbr_secondes();
/***
* Initialiser l'horloge
***/
void init_clock(void);

/**
*fonction pour retourner uptime
*/
uint32_t nbr_secondes();
/***
* Traitant de l'IT 32 qui affiche à l'écran le temps écoulé depuis le
démarrage du système
***/
void tic_PIT(void);

/***
* Initialisation de l'entrée 32 dans la table des vecteurs d'IT
 ***/
extern void init_traitant_IT(int32_t num_IT, void (*traitant)(void));



#endif
