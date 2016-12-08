#include <time.h>
#include <string.h>
#include <stdio.h>
#include "console.h"
#include <stdbool.h>
#include <inttypes.h>
#include "segment.h"
#include "cpu.h"
#include "process.h"
#include "start.h"

int32_t pid_actif = 0;
int32_t pid_a_creer = 0;
/**
* Première partie de gestion des processus
*/
/*
void idle(void) {
  printf("[idle] je tente de passer la main a proc1...\n");
  ctx_sw(tab[0].contexte, tab[1].contexte);
}

void proc1(void) {
  printf("[proc1] idle m’a donne la main\n");
  printf("[proc1] j’arrete le systeme\n");
  hlt();
}
*/
/**
*Deuxième partie de gestion des processus
*/
/*
void idle(void) {
  for (int i = 0; i < 3; i++) {
    printf("\n[idle] je tente de passer la main a proc1...\n");
    ctx_sw(tab[0].contexte, tab[1].contexte);
    printf("\n[idle] proc1 m’a redonne la main\n");
  }
  printf("[idle] je bloque le systeme\n");
  hlt();
}
void proc1(void) {
  for (;;) {
    printf("\n[proc1] idle m’a donne la main\n");
    printf("[proc1] je tente de lui la redonner...\n");
    ctx_sw(tab[1].contexte, tab[0].contexte);
  }
}
*/
/**
*Troisième partie de gestion des processus : politique d'ordonnancement
*/
/*
void idle(void) {
  for (;;) {
    printf("\n[%s] pid = %i\n", mon_nom(), mon_pid());
    ordonnance();
  }
}
void proc1(void) {
  for (;;) {
    printf("[%s] pid = %i\n", mon_nom(), mon_pid());
    ordonnance();
  }
}

void proc2(void) {
  for (;;) {
    printf("[%s] pid = %i\n", mon_nom(), mon_pid());
    ordonnance();
  }
}

void proc3(void) {
  for (;;) {
    printf("[%s] pid = %i\n", mon_nom(), mon_pid());
    ordonnance();
  }
}
*/
/**
*Quatrième partie de gestion des processus : politique d'ordonnancement
*/
/*
void idle(void) {
  for (;;) {
    printf("[%s] pid = %i\n", mon_nom(), mon_pid());
    sti();
    hlt();
    cli();
  }
}
void proc1(void) {
  for (;;) {
    printf("[%s] pid = %i\n", mon_nom(), mon_pid());
    sti();
    hlt();
    cli();
  }
}
void proc2(void) {
  for (;;) {
    printf("[%s] pid = %i\n", mon_nom(), mon_pid());
    sti();
    hlt();
    cli();
  }
}
void proc3(void) {
  for (;;) {
    printf("[%s] pid = %i\n", mon_nom(), mon_pid());
    sti();
    hlt();
    cli();
  }
}
*/

/**
*Cinquième partie de gestion des processus
*/
void idle() {
  for (;;) {
    sti();
    hlt();
    cli();
  }
}
void proc1(void) {
  //for (;;) {
<<<<<<< HEAD
  for (int i = 0; i < 2; i++){
=======
  for (int32_t i = 0; i < 3; i++){
>>>>>>> bdae8209a2f6342f02a5c0fa87e51c533fa26dc4
    printf("[temps = %u] processus %s pid = %i\n", nbr_secondes(),
    mon_nom(), mon_pid());
    dors(2);
  }
<<<<<<< HEAD
  cree_processus(proc4,"proc4");
}
void proc2(void) {
  for (int i = 0; i < 4; i++){
    printf("[temps = %u] processus %s pid = %i\n", nbr_secondes(),
    mon_nom(), mon_pid());
    dors(3);
  }
    cree_processus(proc5,"proc5");
}

void proc3(void) {
  for (int i = 0; i < 8; i++){
=======
  fin_processus();
  //}
}
void proc2(void) {
// for (;;) {
for (int32_t i = 0; i < 2; i++){
    printf("[temps = %u] processus %s pid = %i\n", nbr_secondes(),
    mon_nom(), mon_pid());
    dors(3);
}
    fin_processus();
//  }
}

void proc3(void) {
//  for (;;) {
  for (int32_t i = 0; i < 3; i++){
>>>>>>> bdae8209a2f6342f02a5c0fa87e51c533fa26dc4
    printf("[temps = %u] processus %s pid = %i\n", nbr_secondes(),
    mon_nom(), mon_pid());
    dors(5);
  }
    fin_processus();
  //}
}

void proc4(void){
    printf("processus cree par proc1 [%s] pid = %i\n", mon_nom(),mon_pid());
    for(int i=0;i<2;i++){
        printf("[temps = %u] processus [%s] pid = %i\n",nbr_secondes(),mon_nom(),mon_pid() );
        dors(2);
    }
}

void proc5(void){
    printf("processus cree par proc2 [%s] pid = %i\n", mon_nom(),mon_pid());
    for(int i=0;i<2;i++){
        printf("[temps = %u] processus [%s] pid = %i\n",nbr_secondes(),mon_nom(),mon_pid() );
        dors(2);
    }
}
/**
*fonction pour créer et initialiser les processus
*/
int32_t cree_processus(void (*code)(void), char *nom) {
  int pid_mort = -1;
    int i =0;
    for(int j=0;j<NB_PROC;j++){
        if(tab[j].etat == MORT){
            pid_mort = j;
        }
    }

    if (pid_a_creer == (NB_PROC -1) && pid_mort == -1) return -1;
    else{
        if(pid_mort == -1) i = pid_a_creer +1;
        else i = pid_mort;

        tab[i].pid = i;
        tab[i].temps_reveil = 0;
        strcpy(tab[i].nom,nom);
        tab[i].etat = ACTIVABLE;

        tab[i].contexte[1] = (int) &(tab[i].pile[510]);
        tab[i].pile[511] = (int) fin_processus;
        tab[i].pile[510] = (int) code;

        pid_a_creer++;
        return pid_a_creer;
    }
}
/**
*fonction pour endormir le processus appelant pdt nbr_secs
*/
void dors(uint32_t nbr_secs) {
  tab[pid_actif].temps_reveil = nbr_secondes() + nbr_secs;
  tab[pid_actif].etat = ENDORMI;
  sti();
  hlt();
  cli();
}
/**
*fonction qui termine un processus en le plaçant dans l'etat mort
*/
void fin_processus(void) {
  tab[pid_actif].etat = MORT;
  sti();
  hlt();
}

/**
*Fonction qui retourne le pid du processus en cours d'exécution
*/
int32_t mon_pid(void) {
  int32_t le_pid;
  for (int i = 0; i < NB_PROC; i++) {
    if (tab[i].etat == ELU) {
      le_pid = (int32_t)(tab[i].pid);
    }
  }
  return le_pid;
}

/*
*Fonction qui retourne le nom du processus en cours d'exécution
*/
char *mon_nom(void) {
  char *elu;
  for (int i = 0; i < NB_PROC; i++) {
    if (tab[i].etat == ELU) {
      elu = (char*)(tab[i].nom);
    }
  }
  return elu;
}
/**
*fonction qui endors le processus appelant
*/
void dors(uint32_t nbr_secs) {
  tab[pid_actif].temps_reveil = nbr_secs + nbr_secondes();
  tab[pid_actif].etat = ENDORMI;
  ordonnance();
}
/**
*fonction qui termine un processus en le plaçant dans l'etat mort
*/
void fin_processus(void) {
  tab[pid_actif].etat = MORT;
  ordonnance();
}
/**
*Implantation de la politique d'ordonnancement collaboratif
*/
void ordonnance(void) {
<<<<<<< HEAD
  //process temps;
  int32_t new_proc = mon_pid();
  
  if(tab[new_proc].etat == ELU) {
    tab[new_proc].etat = ACTIVABLE;
  }
  pid_actif = (new_proc+1)%NB_PROC;
  /*if(tab[pid_actif].etat == MORT) {
    pid_actif = (pid_actif + 1)%NB_PROC;
  }*/
  
  while (tab[pid_actif].etat == ENDORMI || tab[pid_actif].etat == MORT ) {
        if(tab[pid_actif].etat == MORT || (tab[pid_actif].etat == ENDORMI && tab[pid_actif].temps_reveil > nbr_secondes())){
            pid_actif=(pid_actif+1)%NB_PROC;
        }
        else if(tab[pid_actif].etat == ENDORMI && tab[pid_actif].temps_reveil <= nbr_secondes()){
            tab[pid_actif].etat = ACTIVABLE;
        }
    }
  tab[pid_actif].etat = ELU;
  ctx_sw(tab[new_proc].contexte,tab[pid_actif].contexte);
  /*
=======
  process temps;
  int i;
  int32_t activable;
  pid_actif = mon_pid();
>>>>>>> bdae8209a2f6342f02a5c0fa87e51c533fa26dc4
  while(tab[pid_actif].etat == ENDORMI && tab[pid_actif].temps_reveil <= nbr_secondes()) {
    i = (pid_actif + 1)%NB_PROC;
    activable = (i + 1)%NB_PROC;
    temps = tab[i];
    temps.etat = ACTIVABLE;
    tab[activable].etat = ELU;
    ctx_sw(temps.contexte, tab[activable].contexte);
    pid_actif = activable;
<<<<<<< HEAD
  }
  
  activable = (pid_actif + 1)%NB_PROC;
  tab[pid_actif].etat = ACTIVABLE;
  tab[(pid_actif + 1)%NB_PROC].etat = ELU;
ctx_sw(tab[pid_actif].contexte, tab[activable].contexte);*/
=======
  }
  if(tab[pid_actif].etat == MORT) {
    pid_actif = (pid_actif + 1)%NB_PROC;
  }
  activable = (pid_actif + 1)%NB_PROC;
  tab[pid_actif].etat = ACTIVABLE;
  tab[(pid_actif + 1)%NB_PROC].etat = ELU;
  ctx_sw(tab[pid_actif].contexte, tab[activable].contexte);

/*  for (i = 0; i < NB_PROC; i++) {
    if (tab[i].etat == ENDORMI){
      j = 0;
      while(j <= tab[i].temps_reveil) {
        j++;
      }
      tab[i].etat = ACTIVABLE;
    }
    else {
      pid_actif = mon_pid();
      activable = (pid_actif + 1)%NB_PROC;
      tab[pid_actif].etat = ACTIVABLE;
      tab[(pid_actif + 1)%NB_PROC].etat = ELU;
      ctx_sw(tab[pid_actif].contexte, tab[activable].contexte);
    }
  }*/
>>>>>>> bdae8209a2f6342f02a5c0fa87e51c533fa26dc4
}
