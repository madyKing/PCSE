#include <time.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <inttypes.h>
#include "segment.h"
#include "cpu.h"
#include "process.h"
#include "start.h"

#define CLOCKFREQ 50     //fréquence de l'horloge (en Hz)
#define NB_ITER CLOCKFREQ
#define QUARTZ 0x1234DD   //fréquence du circuit (~1,19 MHz)
#define IMPULSION QUARTZ/CLOCKFREQ

static int hr;
static int min;
static int sec;
static int iter;
static uint32_t uptime = 0; //mesure du temps écoulé dépuis le démarrage du systeme
static char clock_str[256];

/**
 *Masquage et démasquage de l'IRQ
 */
void masque_IRQ(uint32_t num_IRQ, bool masque){
  uint8_t it = inb(0x21); // on récupère l'état des it
  uint8_t bitN = 0x01;
  uint8_t bitN2 ;
  bitN = bitN << num_IRQ ; // on scrute l'état du bit num_IRQ
  if(masque == true){/*Si l'on souhaite masquer l'IRQ */
    it = it | bitN;
  }
  else {/*l'on souhaite démasquer*/
    bitN2 = ~(bitN);
    it = it & bitN2;
  }
  outb(it, 0x21);
}

/**
 *traitant de l'interruption 32
 *affiche à l'écran le temps écoulé depuis le démarrage du système
 */
void tic_PIT(void){
  outb(0x20,0x20); // acquittement de l'IT
  iter++;
  uptime++;
  masque_IRQ(0,false);
  if (iter >= NB_ITER){

      sec++;
      iter = 0;
      if (sec >= 60){
	 min++;
	 sec = 0;
	 if (min >= 60){
	   hr ++;
	   min = 0;
	   if (hr >= 24){
	    hr = 0;
	   }
	 }
       }
      sprintf(clock_str, "%02d : %02d : %02d", hr, min, sec);
  }
  ecrit_haut_droite(clock_str);
  ordonnance();
}

uint32_t nbr_secondes() {
  return uptime;
}

/**
 *initialisation de l'entrée 32 dans la table des vecteurs d'interruptions
 */
void init_traitant_IT(int32_t num_IT, void (*traitant)(void)){
    uint32_t * idt1 = (uint32_t *) (0x1000 | 8*num_IT);
    //16 bits de poids faibles de l’adresse du traitant et les 16 bits du KERNEL_CS
    *idt1 = (uint32_t)(KERNEL_CS << 16) | ((uint32_t)traitant & 0x0000FFFF) ;
    //16 bits de poids forts de l’adresse du traitant et la constante 0x8E00
    uint32_t * idt2 = (uint32_t *) (0x1000 |( 8*num_IT + 4));
    *idt2 = ((uint32_t)traitant & 0xFFFF0000) | (uint32_t) 0x8E00 ;
}
uint32_t nbr_secondes() {
  return uptime;
}
/**
 * Initialiser l'horloge
 */
void init_clock(void) {
  hr = min = sec = iter = 00;
// Réglage de l'horloge programmable
  outb(0x34, 0x43);
  outb(IMPULSION  % 256,0x40);
  outb((IMPULSION >> 8), 0x40);
}
