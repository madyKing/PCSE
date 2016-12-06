#ifndef _PROCESS_H
#define _PROCESS_H

#include <time.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <inttypes.h>
#include "segment.h"
#include "cpu.h"
#include "start.h"
#include "console.h"

#define NB_PROC 4


extern void ctx_sw(uint32_t*,uint32_t*);

/**
 *type enumeration pour les differents etats d'un processus
 */
typedef enum struct_etat{
  ELU,
  ACTIVABLE,
  ENDORMI,
  MORT,
} ETAT;
/**
 *definition de la structure de donnee d'un processus
 */
typedef struct struct_process {
  int pid;
  char nom[30];
  uint32_t temps_reveil;
  ETAT etat;
  uint32_t temps_reveil;
  uint32_t contexte[5];
  uint32_t pile[512];
} process;

process tab[NB_PROC];
/**
 *Processus par defaut : toujours actif
 */
void idle(void);
/**
 *Processus 1 : quelconque
 */
void proc1(void);
void proc2(void);
void proc3(void);

/**
*Fonction qui retourne le pid du processus en cours d'exécution
*/
int32_t mon_pid(void);
/*
*Fonction qui retourne le nom du processus en cours d'exécution
*/
char *mon_nom(void);
/**
*fonction pour endormir le processus appelant pdt nbr_secs
*/
void dors(uint32_t nbr_secs);
void elir(uint32_t pid);
/**
*Implantation de la politique d'ordonnancemen collaboratif
*/
void ordonnance(void);
/**
*fonction qui endors le processus appelant
*/
void dors(uint32_t nbr_secs);
/**
*fonction qui termine un processus en le plaçant dans l'etat mort
*/
void fin_processus(void);
/**
*fonction pour créer et initialiser les processus
*/
int32_t cree_processus(void (*code)(void), char *nom);

#endif
