/*************************************************************************
 -------------------
 dÈbut                : 15/01/2015
 copyright            : (C) 2015 par Antoine Breton et Arnaud Dupeyrat
 *************************************************************************/
#ifndef __TP4Forme__Vue__
#define __TP4Forme__Vue__

//--------------------------------------------------- Interfaces utilisÈes

//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// Rôle de la classe Vue:
//
// Classe permettant d'interagir avec l'utilisateur.
//
//------------------------------------------------------------------------

class Vue
{
    //----------------------------------------------------------------- PUBLIC
    
public:
    //----------------------------------------------------- MÈthodes publiques
    
    void AfficherErreur();
    // Mode d'emploi :
    // Permet l'affichage de "ERR".
    
    void AfficherOK();
    // Mode d'emploi :
    // Permet l'affichage de "OK".
    
    void AfficherMessageFigureNonPresente();
    // Mode d'emploi :
    // Permet de préciser que la figure recherché n'est pas présente dans le modéle actuellement (en commentaire).
    
    void AfficherMessagePointDedans();
    // Mode d'emploi :
    // Permet de préciser que le point est dans la figure.
    
    void AfficherMessagePointNONDedans();
    // Mode d'emploi :
    // Permet de préciser que le point est dans la figure.
    
    void AfficherSuppressionImpossible();
    // Mode d'emploi :
    // Permet de préciser que la suppresion ne s'est pas déroulé correctement.
    
    void AfficherActionImpossible();
    // Mode d'emploi :
    // Permet de préciser que l'annulation ne s'est pas déroulé.
    
    void AfficherCommandeNonDispo();
    // Mode d'emploi :
    // Permet de préciser que la commande n'est pas reconnue.
    
    void AfficherNbdispo();
    // Mode d'emploi :
    // Permet de préciser que le nombre de figures est nul.
    
    void SauvegardeNonFaite ();
    // Mode d'emploi :
    // Permet de préciser que la sauvegarde du modele n'est pas faite.
    
    void AfficherFinLoad();
    // Mode d'emploi :
    // Permet de préciser que la load est finis.
    
    // constructeur de la classe.
    Vue ();
    
    // Destructeur de la classe.
    virtual ~Vue ();
    
};

//----------------------------------------- Types dÈpendants de Rectangle


#endif /* defined(__TP4Forme__Vue__) */
