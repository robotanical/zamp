#define ROTATE_SPEED     30
/*
 *  Przykładowy zestaw poleceń
 */
  Set   Podstawa 2 0 30    
  Set   Podstawa.Ramie1.Ramie2 10 10 0   
  Rotate Podstawa.Ramie1 ROTATE_SPEED 40
  Pause 1000 
  Move  Podstawa.Ramie1  10 10
  Rotate Podstawa.Ramie1 ROTATE_SPEED 60 
  Move  Podstawa.Ramie1.Ramie2 10 20           
  