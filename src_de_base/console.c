#include "cpu.h"
#include <inttypes.h>
#include <string.h>
#include <stdio.h>
#include "console.h"

uint32_t col_curseur = 0;
uint32_t lig_curseur = 0;
//uint16_t pos_curseur = col_curseur + 80*lig_curseur;


// fonction pour retourner la case mémoire pointée
uint16_t *ptr_mem(uint32_t lig, uint32_t col){
  return (uint16_t*)( 0xB8000 + 2*(lig*80 + col));
}

// fonction pour afficher c à la position spécifiée
void ecrit_car(uint32_t lig, uint32_t col, char c){
  uint16_t *p;
  p = ptr_mem(lig,col);

  *p =  0x0F <<8 | c ;
  outb(0x0F,0x3D4);
  outb(1,0x3D5);
  outb(0x0E,0x3D4);
  outb(2,0x3D5);
}

// fonction pour effacer une ligne

void efface_ligne(uint32_t lig)
{
	for (int i = 1; i < 80; ++i)
	{
		ecrit_car(lig, i, ' ');
	}
}

//fonction pour placer le curseur à la position spécifiée

void place_curseur(uint32_t lig, uint32_t col){
  uint16_t posi, pos;
  //on actualise les positions du curseur
  lig_curseur = lig;
  col_curseur = col;


  pos = col + lig*80; //partie basse
  posi  = (col + lig*80) >> 8; //partie haute
  outb(0x0F,0x3D4);
  outb(pos,0x3D5);
  outb(0x0E,0x3D4);
  outb(posi,0x3D5);
}

// fonction pour effacer les contenus des cases de la mémoire
void efface_ecran(void){
  uint32_t i,j;
  for(i = 0; i < 25; i++){
    for(j = 0; j < 80; j++){
      ecrit_car(i,j,' ');
    }
  }
  place_curseur(0,0);
}

//traitement des caractères

void traite_car(char c) {
  if(c < 31 || c > 126){
    switch (c) {
    case 8 :
      if(col_curseur != 0) place_curseur(lig_curseur, col_curseur -1);
      else place_curseur(lig_curseur - 1, 79);
      break;
    case 9:
      if(col_curseur < 72) place_curseur(lig_curseur, col_curseur - (col_curseur%8) + 8);
      else place_curseur(lig_curseur, 79);
      break;
    case 10:
      place_curseur(lig_curseur + 1, 0);
      break;
    case 12:
      efface_ecran();
      place_curseur(0,0);
      break;
    case 13:
      place_curseur(lig_curseur, 0);
      break;
    default:
      break;
    }
  }
  else
    {
     if(col_curseur < 80){
        ecrit_car(lig_curseur,col_curseur, c);
        place_curseur(lig_curseur,col_curseur + 1);

     }
     else{
       place_curseur(lig_curseur + 1, 0);
     }
    }
}

// fonction pour remonter d'une ligne en haut
void defilement(void)
{/*
  uint16_t * ptr_ligne = NULL;
  uint16_t *ptr_ligne_suivant  = NULL;
  int i;
  for (i = 0; i < 25; ++i)
	{
		if (i == 24)
		{
			efface_ligne((uint32_t) 24);
      place_curseur(i-1,0);
			break;
		}
	    *ptr_ligne = (0xB8000 + 2 * ((uint32_t) (i * 80)));
	    *ptr_ligne_suivant = (0xB8000 + 2 * ((uint32_t) ((i + 1) * 80)));
		memmove(ptr_ligne, ptr_ligne_suivant, 160);
	}*/
  memmove(ptr_mem(0,0),ptr_mem(1,0),79 - 8);
  memmove(ptr_mem(1,0),ptr_mem(2,0),160*23);
  efface_ligne((uint32_t) 24);
}


void console_putbytes(const char *chaine, int32_t taille)
{
   int32_t i;
	for(i = 0; i < taille; ++i)
	{
		traite_car(chaine[i]);
	}
  if(lig_curseur == 25)
{
  defilement();
  lig_curseur = 24;
}

}

// 1ère fonction pour la gestion du temps
void ecrit_haut_droite(char * car)
{
	// On sauvegarde la position du curseur avant l'appel de la fonction
	uint32_t col_curseur_temp = col_curseur;
	uint32_t lig_curseur_temp = lig_curseur;
	col_curseur = 79;
	lig_curseur = 0;
	int i;
	for (i = strlen(car) - 1; i >= 0; i--)
	{
		ecrit_car(lig_curseur, col_curseur, car[i]);
		place_curseur(lig_curseur, col_curseur - 1);
	}
	// On restaure les valeurs sauvegardées
	place_curseur(lig_curseur_temp, col_curseur_temp);
}
