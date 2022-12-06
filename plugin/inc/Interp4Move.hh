#ifndef COMMAND4MOVE_HH
#define COMMAND4MOVE_HH

#ifndef __GNUG__
#pragma interface
#pragma implementation
#endif

#include <unistd.h>

#include <cmath>

#include "Client.hh"
#include "Interp4Command.hh"
#include "MobileObj.hh"
#include "Scene.hh"
#include "Vector3D.hh"
/*!
 * \file
 * \brief Definicja klasy Interp4Move
 *
 * Plik zawiera definicję klasy Interp4Move ...
 */

/*!
 * \brief Modeluje polecenie dla robota mobilnego, które wymusza jego ruch do
 * przodu
 *
 *  Klasa modeluje ...
 */
class Interp4Move : public Interp4Command {
  /*
   *  Tu należy zdefiniować pola, które są niezbędne
   *  do przechowywania wartości parametrów danego polecenia.
   *  Ponieżej zdefiniowane jest tylko jedno pole jako przykład.
   */
  double _Speed_mmS;
  std::string _Name;
  double _Length_mm;

 public:
  /*!
   * \brief
   */
  Interp4Move();
  /*!
   * \brief Wyświetla postać bieżącego polecenia (nazwę oraz wartości
   * parametrów)
   */
  virtual void PrintCmd() const;
  /*!
   * \brief Wyświetla składnię polecenia
   */
  virtual void PrintSyntax() const;
  /*!
   * \brief Wyświetla nazwę polecenia
   */
  virtual const char* GetCmdName() const;
  /*!
   * \brief Wykonuje polecenie oraz wizualizuje jego realizację
   */
  virtual bool ExecCmd(Scene& scene) const;
  /*!
   * \brief Czyta wartości parametrów danego polecenia
   */
  virtual bool ReadParams(std::istream& Strm_CmdsList);
  /*!
   * \brief Wyświetla wartości wczytanych parametrów
   */
  virtual void PrintParams() {}
  /*!
   * \brief
   *
   *  Ta metoda nie musi być zdefiniowna w klasie bazowej.
   */
  static Interp4Command* CreateCmd();
};

#endif
