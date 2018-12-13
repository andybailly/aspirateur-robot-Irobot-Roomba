/** @file
 *  @copyright GPLv3
 *  @date 12/10/2017
 *  @author AB
 */
#ifndef ROBOT_H
#define ROBOT_H
#define TEST_ROBOT_CONNECTER
#define TEST_ROBOT_DECONNECTER

/**
 * @brief Modèle logiciel du robot
 * @details La classe Robot implémente les méthodes pour envoyer les commandes au robot,
 * réaliser une acquisition de mesures, exporter les valeurs dans un fichier.
 */
#include<QIODevice>
class Robot
{
private:
    QIODevice *mCommunication;
    int mPwmRoueDroite;
    int mPwmRoueGauche;
    int mPwmBrossePrincipale;
    int mPwmBrosseLaterale;
    int mPwmAspiration;
    bool mLedDock;
    bool mLedSpot;
    bool mLedDirtDetect;
    int mLedCleanIntensite;
    int mLedCleanCouleur;
    /**
     * @brief envoyerCommandeRoues
     * Envoie au robot la commande des roues droites et gauches, à partir des attributs pwmRoueDroite et pwmRoueGauche.
     */
    void envoyerCommandeRoues();
    void envoyerCommandeMoteur();
    void envoyerCommandeLeds();
public:
    Robot();
    void connecter();
    void deconnecter();
    void faireNettoyageModeClean();
    void faireArret();
    void setPWmRoueDroite(int PwmRoueDroite);
    void setPWmRoueGauche(int PwmRoueGauche);
    void setPwmBrossePrincipale(int pwmBrossePrincipale);
    void setPwmBrosseLaterale(int pwmBrosseLaterale);
    void setPwmAspiration(int pwmAspiration);
    /**
     * @brief Robot::setCommunication
     * Définit le périphérique de communication avec le robot.
     */
    void setCommunication(QIODevice *communication);
    int pwmRoueDroite();
    int pwmRoueGauche() const;
    void setPwmRoueGauche(int pwmRoueGauche);

    int pwmBrossePrincipale() const;
    int pwmBrosseLaterale() const;
    int pwmAspiration() const;
    bool ledDock() const;
    bool ledSpot() const;
    bool ledDirtDetect() const;
    int ledCleanIntensite() const;
    int ledCleanCouleur() const;
    void setLedDock(bool ledDock);
    void setLedSpot(bool ledSpot);
    void setLedDirtDetect(bool ledDirtDetect);
    void setLedCleanIntensite(int ledCleanIntensite);
    void setLedCleanCouleur(int ledCleanCouleur);
};

#endif // ROBOT_H
