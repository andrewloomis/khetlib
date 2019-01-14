#include <pyramid.h>

Interaction Pyramid::laserInteraction(Direction laserIncidentDir) const
{
    Interaction interaction;
    if (this->angle() == 0 || this->angle() == 360)
    {
        switch (laserIncidentDir) {
        case Direction::NegX:
        case Direction::PosY:
            interaction = Interaction::Kill;
            break;
        case Direction::PosX:
            interaction = Interaction::ReflectPosY;
            break;
        case Direction::NegY:
            interaction = Interaction::ReflectNegX;
        }
    }
    else if (this->angle() == 90)
    {
        switch (laserIncidentDir) {
        case Direction::NegX:
        case Direction::NegY:
            interaction = Interaction::Kill;
            break;
        case Direction::PosX:
            interaction = Interaction::ReflectNegY;
            break;
        case Direction::PosY:
            interaction = Interaction::ReflectNegX;
        }
    }
    else if (this->angle() == 180)
    {
        switch (laserIncidentDir) {
        case Direction::PosX:
        case Direction::NegY:
            interaction = Interaction::Kill;
            break;
        case Direction::NegX:
            interaction = Interaction::ReflectNegY;
            break;
        case Direction::PosY:
            interaction = Interaction::ReflectPosX;
        }
    }
    else if (this->angle() == 270)
    {
        switch (laserIncidentDir) {
        case Direction::PosX:
        case Direction::PosY:
            interaction = Interaction::Kill;
            break;
        case Direction::NegX:
            interaction = Interaction::ReflectPosY;
            break;
        case Direction::NegY:
            interaction = Interaction::ReflectPosX;
        }
    }
    else interaction = Interaction::Error;
    return interaction;
}
