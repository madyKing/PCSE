#ifndef __CONSOLE_H__
#define __CONSOLE_H__
#include <inttypes.h>

/*
 * This is the function called by printf to send its output to the screen. You
 * have to implement it in the kernel and in the user program.
 */

extern void console_putbytes(const char *s, int len);

/*
 *fonction pour retourner la case mémoire pointée
 */
uint16_t *ptr_mem(uint32_t lig, uint32_t col);

/*
 *fonction pour afficher c à la position spécifiée
 */
void ecrit_car(uint32_t lig, uint32_t col, char c);

/*
 *fonction pour effacer une ligne
 */
void efface_ligne(uint32_t lig);

/*
 *fonction pour effacer les contenus des cases de la mémoire
 */
void efface_ecran(void);

/*
 *fonction pour placer le curseur à la position spécifiée
 */
void place_curseur(uint32_t lig, uint32_t col);

/*
 *traitement des caractères
 */
void traite_car(char c);

/*
 * fonction pour remonter d'une ligne en haut
 */
void defilement(void);

/*
 *1ère fonction pour la gestion du temps: écrire tout en haut de l'écran
 */
void ecrit_haut_droite(char * car);
#endif
