#include "Timer.h"

Timer::Timer()
{
    // Initialisation des variables
    m_Demarre = false;
    m_EnPause = false;

    m_TempsDepart = 0;
    m_TempsPause = 0;
}

void Timer::demarre()
{
    // Commence le timer
    m_Demarre = true;
    m_EnPause = false;

    // On prend le temps actuel de l'horloge de l'ordinateur
	m_TempsDepart = clock.GetElapsedTime();
}

void Timer::arrete()
{
    // Arr�te le timer
    m_Demarre = false;
    m_EnPause = false;

    m_TempsDepart = 0;
    m_TempsPause = 0;
}

void Timer::pause()
{
    // Si le timer est d�ja en marche et n'est pas en pause
    if(m_Demarre && !m_EnPause)
    {
        // met le timer en pause
        m_EnPause = true;

        // en calcule le temps de pause
        m_TempsPause = clock.GetElapsedTime() - m_TempsDepart;
    }
}

void Timer::unpause()
{
    // Si le timer est en pause
    if(m_EnPause)
    {
        // on le remet en marche
        m_EnPause = false;

        // On remet le temps de d�part
        m_TempsDepart = clock.GetElapsedTime() - m_TempsPause;

        // et on r�initialise le temps de pause � 0
        m_TempsPause = 0;
    }
}


float Timer::getTemps() const
{
    // Si le timer fonctionne
    if (m_Demarre)
    {
        if (m_EnPause)
            return m_TempsPause;                        // On retourne l'accumulation du temps calcul� lors de la pause
        else
            return clock.GetElapsedTime() - m_TempsDepart;       // On retourne l'accumulation du temps depuis le d�but
    }
    else
        return 0;           // Si le timer est arret�
}


bool Timer::estDemarre() const
{
    return m_Demarre;
}

bool Timer::estEnPause() const
{
    return m_EnPause;
}
