#include "djed.h"
#include <QDebug>

Interaction Djed::laserInteraction(Direction laserIncidentDir) const
{
    Interaction interaction;
    qDebug() << "Calculating interaction for piece" << index() << "at angle" << angle();
    if (this->angle() == 0 || this->angle() == 360 || this->angle() == 180)
    {
        switch (laserIncidentDir) {
        case Direction::NegX:
            interaction = Interaction::ReflectNegY;
            break;
        case Direction::PosY:
            interaction = Interaction::ReflectPosX;
            break;
        case Direction::PosX:
            interaction = Interaction::ReflectPosY;
            break;
        case Direction::NegY:
            interaction = Interaction::ReflectNegX;
            break;
        }
    }
    else if (this->angle() == 90 || this->angle() == 270)
    {
        switch (laserIncidentDir) {
        case Direction::NegX:
            interaction = Interaction::ReflectPosY;
            break;
        case Direction::NegY:
            interaction = Interaction::ReflectPosX;
            break;
        case Direction::PosX:
            interaction = Interaction::ReflectNegY;
            break;
        case Direction::PosY:
            interaction = Interaction::ReflectNegX;
            break;
        }
    }
    else interaction = Interaction::Error;
    return interaction;
}
