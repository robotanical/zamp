#define ROTATE_SPEED     3
/*
 *  Przykładowy zestaw poleceń
 */
 // begin_parallel
  // Set   Podstawa 2 0 30    
  // Set   Podstawa.Ramie1.Ramie2 10 10 0   
  // end_parallel
  // begin_parallel
  // Rotate Podstawa.Ramie1 ROTATE_SPEED 40
  // end_parallel
  Pause 1000 
  Move  Podstawa.Ramie1  1 10
  begin_parallel
  Move Podstawa.Ramie1 1 6
  Move  Podstawa.Ramie1.Ramie2 1 20  
  end_parallel         
  