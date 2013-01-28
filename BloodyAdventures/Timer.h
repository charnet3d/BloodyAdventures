#ifndef _SIMPLETIMER_H_
#define _SIMPLETIMER_H_

#include <SFML/Window.hpp>

class Timer
{
protected:
    // Le temps de début en milliseconde
    float m_TempsDepart;
    float m_TempsPause;

	sf::Clock clock;

    // L'état du timer
    bool m_Demarre;
    bool m_EnPause;

public:

    // Constructeur pour l'initialisation
    Timer();

    // Les différentes action du timer
    void demarre();
    void arrete();
    void pause();
    void unpause();

    // Retourne le temps indiqué dans le timer
    float getTemps() const;

    // Vérifie l'état du timer
    bool estDemarre() const;
    bool estEnPause() const;
};

#endif // _SIMPLETIMER_H_
