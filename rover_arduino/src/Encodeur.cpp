#ifndef ENCODEUR_H
#define ENCODEUR_H

#include <Arduino.h>
#include "gestionaireTimer2.cpp"
class Encodeur
{
protected:
    static float _position[10];
    static int _derniereLecture[10];
    static int _pin[10];

    static bool initialisation;
    static int nbr;
    static void update();

    int id;

public:
    Encodeur(int pin);
    float ReadAngle();
};

int Encodeur::nbr = 0;
bool Encodeur::initialisation = false;

float Encodeur::_position[10] = {0,0,0,0,0,0,0,0,0,0};
int Encodeur::_derniereLecture[10] = {0,0,0,0,0,0,0,0,0,0};
int Encodeur::_pin[10] = {0,0,0,0,0,0,0,0,0,0};

Encodeur::Encodeur(int pin)
{
    id = nbr;
    nbr++;
    _position[id] = analogRead(_pin[id]);
    _pin[id] = pin;
    pinMode(_pin[id],INPUT);
    _derniereLecture[id] = analogRead(_pin[id]);

    if(!initialisation)
    {
        gestionaireTimer2::ajouter(update);
        initialisation = true;
    }
}

void Encodeur::update()
{
    for(int i = 0; i < nbr;i++)
    {
        int lecture = analogRead(_pin[i]);
        float  delta = lecture - _derniereLecture[i];
        delta = delta*360/1026;
        _derniereLecture[i] = lecture;

        if(delta < -180)
        {
           delta += 360;
        }
        if(delta > 180)
        {
            delta -= 360;
        }
        _position[i] += delta;
    }


}
float Encodeur::ReadAngle()
{
    return _position[id];
}

#endif