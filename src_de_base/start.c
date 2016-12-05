#include "cpu.h"
#include <inttypes.h>
#include <string.h>
#include <stdio.h>
#include "console.h"
#include "time.h"
#include "process.h"

extern void traitant_IT_32(void) ;
extern void ctx_sw(uint32_t*, uint32_t*);
void kernel_start(void) {
    /********************************************************
     ******************Partie Ecran + Temps******************
     ********************************************************/
  /*
  //ecrit_car(1,0,car);
    efface_ecran();
    init_traitant_IT(32, traitant_IT_32);  // On initialise le vecteur d'intr 32
    printf("Bonjour \n");
    init_clock();
    //efface_ecran();
  // console_putbytes("bonjour",8);
    masque_IRQ(0, false); // On démasque l'IRQ0
     sti();
    */
    /*
    efface_ecran();
    for(int i = 0; i < 10; i++) {
      printf("Bonjour\n");
    }
    */
    /********************************************************
     ******************Partie Processus**********************
     ********************************************************/
    /**
     *Initialisations
     */
     //initialisation de la tab des process de idle()
    tab[0].pid = 0;
    strcpy(tab[0].nom,"idle");
    tab[0].etat = ELU;
    /*
    //initialisation de la tab des process de proc1()
    tab[1].pid = 1;
    strcpy(tab[1].nom,"proc1");
    tab[1].etat = ACTIVABLE;
    //la case de la zone de sauvegarde des registres (%esp)
    //doit pointer sur le sommet de pile
    tab[1].contexte[1] =(int)(&(tab[1].pile[511]));
    //la case en sommet de pile doit contenir l’adresse de la fonction proc1
    tab[1].pile[511] = (uint32_t)(proc1);
    */
    cree_processus(proc1, "proc1");
    cree_processus(proc2, "proc2");
    cree_processus(proc3, "proc3");
    //Demarrage du processus par defaut
    efface_ecran();
    init_traitant_IT(32, traitant_IT_32);
    init_clock();
    masque_IRQ(0, false); 
    idle();

    // on ne doit jamais sortir de kernel_start
/*
     while (1) {

        // cette fonction arrete le processeur
     hlt();
    }
    */
}
