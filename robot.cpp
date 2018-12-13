#include "robot.h"





Robot::Robot():
    mCommunication(nullptr),
    mPwmRoueDroite (0),
    mPwmRoueGauche (0),
    mPwmBrossePrincipale (0),
    mPwmBrosseLaterale (0),
    mPwmAspiration (0),
    mLedDock(false),
    mLedSpot(false),
    mLedDirtDetect(false),
    mLedCleanIntensite(0),
    mLedCleanCouleur(0)
{

}

void Robot::setCommunication(QIODevice *communication)
{
    mCommunication = communication;
}
/**
 * @brief Robot::connecter
 * Ouvre le canal de communication, et place le robot en mode Passive.
 */
void Robot::connecter()
{
    mCommunication->open(QIODevice::ReadWrite);//Ouvre la communication au périphérique.
    mCommunication->write(QByteArrayLiteral("\x80"));//Passage au mode Passive.
}
/**
 * @brief Robot::deconnecter
 * Envoie la commande d'arrêt du robot, et referme le canal de communication.
 */
void Robot::deconnecter()
{
    mCommunication->write(QByteArrayLiteral("\x85"));//Envoie de l'octet de la commande Power(opcode 133) pour la mise à l'arrêt du robot.
    mCommunication->close();
}
/**
 * @brief Robot::faireNettoyageModeClean
 * Envoie la commande de nettoyage en mode Clean.
 */
void Robot::faireNettoyageModeClean()
{
    mCommunication->write(QByteArrayLiteral("\x87"));//Passage au mode clean (opcode 135).
}
/**
 * @brief Robot::faireArret
 * Implémentation Commande Arrêt.
 */
void Robot::faireArret()
{
    mCommunication->write(QByteArrayLiteral("\x85"));//Envoie de l'octet de la commande Power(opcode 133) pour la mise à l'arrêt du robot.
}
/**
 * @brief Robot::setPWmRoueDroite
 * Définit la consigne de la roue droite, et envoie la commande au robot si la consigne a changé.
 * @param PwmRoueDroite
 * entier entre -255 et +255.
 *
 * Une valeur positive produit un mouvement du robot vers l'avant, une valeur négative vers l'arrière.
 */
void Robot::setPWmRoueDroite(int PwmRoueDroite)
{
    if(!(mPwmRoueDroite==PwmRoueDroite))//Si roue droite changée.
    {
        mPwmRoueDroite = PwmRoueDroite;

        envoyerCommandeRoues();
    }
}


/**
 * @brief Robot::PwmRoueDroite
 * Renvoie la consigne roue droite
 */
int Robot::pwmRoueDroite()
{
    return mPwmRoueDroite;
}

int Robot::pwmRoueGauche() const
{
    return mPwmRoueGauche;
}

void Robot::setPwmRoueGauche(int pwmRoueGauche)
{
    if(!(mPwmRoueGauche==pwmRoueGauche))//Si roue gauche changée.
    {
        mPwmRoueGauche = pwmRoueGauche;

        envoyerCommandeRoues();
    }
}

bool Robot::ledDock() const
{
    return mLedDock;
}

bool Robot::ledSpot() const
{
    return mLedSpot;
}

bool Robot::ledDirtDetect() const
{
    return mLedDirtDetect;
}

int Robot::ledCleanIntensite() const
{
    return mLedCleanIntensite;
}

int Robot::ledCleanCouleur() const
{
    return mLedCleanCouleur;
}

void Robot::setLedDock(bool ledDock)
{
    if(!(ledDock==mLedDock))
    {
        mLedDock=ledDock;
        envoyerCommandeLeds();
    }

}

void Robot::setLedSpot(bool ledSpot)
{
    if(!(ledSpot==mLedSpot))
    {
        mLedSpot = ledSpot;
        envoyerCommandeLeds();
    }

}

void Robot::setLedDirtDetect(bool ledDirtDetect)
{
    if(!(ledDirtDetect==mLedDirtDetect))
    {
        mLedDirtDetect = ledDirtDetect;
        envoyerCommandeLeds();
    }

}

void Robot::setLedCleanIntensite(int ledCleanIntensite)
{
    if(!(ledCleanIntensite==mLedCleanIntensite))
    {
        mLedCleanIntensite = ledCleanIntensite;
        envoyerCommandeLeds();
    }

}

void Robot::setLedCleanCouleur(int ledCleanCouleur)
{
    if(!(ledCleanCouleur==mLedCleanCouleur))
    {
        mLedCleanCouleur = ledCleanCouleur;
        envoyerCommandeLeds();
    }

}

void Robot::envoyerCommandeRoues()
{
    char pwmRoueDroiteLSB = mPwmRoueDroite & 0x00ff;//garde seulement le lsb  avec cette valeur
    char pwmRoueDroiteMSB = mPwmRoueDroite >>8 & 0x00ff;//decalage de 8 pour récupérer le msb et détruit le lsb.
    char pwmRoueGaucheLSB = mPwmRoueGauche & 0x00ff;
    char pwmRoueGaucheMSB= mPwmRoueGauche >>8 & 0x00ff;

    QByteArray trame;
    trame.append(131);//Octet 1 : Opcode Mode ...
    trame.append(146);// Octet 2 : Opcode DrivePWM
    trame.append(pwmRoueDroiteMSB);// Octet 3 : PWM roue droite, poids fort
    trame.append(pwmRoueDroiteLSB);//Octet 4 : PWM roue droite, poids faible
    trame.append(pwmRoueGaucheMSB);//Octet 5 : PWM roue gauche, poids fort
    trame.append(pwmRoueGaucheLSB);// Octet 6 : PWM roue gauche, poids faible
    mCommunication->write(trame);
}

void Robot::envoyerCommandeMoteur()
{
    char pwmBrossePrincipale=mPwmBrossePrincipale;
    char pwmBrosseLateral=mPwmBrosseLaterale;
    char pwmAspiration=mPwmAspiration;

    QByteArray trame;
    trame.append(131);
    trame.append(144);
    trame.append(pwmBrossePrincipale);
    trame.append(pwmBrosseLateral);
    trame.append(pwmAspiration);
    mCommunication->write(trame);
}

void Robot::envoyerCommandeLeds()
{
    bool ledDock=mLedDock;
    bool ledSpot=mLedSpot;
    bool ledDirtDetect=mLedDirtDetect;
    char ledCleanCouleur=mLedCleanCouleur;
    char ledCleanIntensite=mLedCleanIntensite;
    char ledBit=0;

    if(ledDirtDetect==true)
    {
        ledBit=ledBit | 0b0001;
    }else
    {
        ledBit=ledBit & 0b1110;
    }
    if(ledSpot==true)
    {
        ledBit=ledBit | 0b0010;
    }else
    {
        ledBit=ledBit & 0b1101;
    }
    if(ledDock==true)
    {
        ledBit=ledBit | 0b0100;
    }else
    {
        ledBit=ledBit & 0b1011;
    }
    /*
     * format de la trame LEDs
     *      octet 1: Opcode 139 (0x8b)
     *      octet 2: LED bits:
     *                  b7-b4 reservé
     *                  b3:check robot - non implémenté
     *                  b2: Dock
     *                  b1: Spot
     *                  b0: Debris
     *      Octet 3: Couleur: de 0=vert à 255=rouge
     *      Octet 4: Intensité
     * */

    QByteArray trame;
    trame.append(131);
    trame.append(139);
    trame.append(ledBit);
    trame.append(ledCleanCouleur);
    trame.append(ledCleanIntensite);
    mCommunication->write(trame);
}

int Robot::pwmBrossePrincipale()const
{
    return mPwmBrossePrincipale;
}

int Robot::pwmBrosseLaterale()const
{
    return mPwmBrosseLaterale;
}

int Robot::pwmAspiration()const
{
    return mPwmAspiration;
}
void Robot::setPwmBrossePrincipale(int pwmBrossePrincipale)
{
    if(!(pwmBrossePrincipale==mPwmBrossePrincipale))
    {
        mPwmBrossePrincipale=pwmBrossePrincipale;
        envoyerCommandeMoteur();
    }

}

void Robot::setPwmBrosseLaterale(int pwmBrosseLaterale)
{
    if(!(pwmBrosseLaterale==mPwmBrosseLaterale))
    {
        mPwmBrosseLaterale=pwmBrosseLaterale;
        envoyerCommandeMoteur();
    }

}

void Robot::setPwmAspiration(int pwmAspiration)
{
    if(!(pwmAspiration==mPwmAspiration))
    {
        mPwmAspiration=pwmAspiration;
        envoyerCommandeMoteur();
    }

}
