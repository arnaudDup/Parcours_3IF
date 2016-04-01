package vue;


import dao.AdherentDao;
import dao.JpaUtil;
import java.util.Date;
import java.util.List;
import java.util.logging.Level;
import java.util.logging.Logger;
import metier.modele.Activite;
import metier.modele.Adherent;
import metier.modele.DemandeEvenement;
import metier.modele.Evenement;
import metier.modele.EvenementAvecEquipe;
import metier.service.ServiceTechnique;
import metier.service.ServicesMetier;

/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/**
 *
 * @author abreton
 */


public class mainEnvoiDeMailEvenement {
    
    final static int CONSTANTEEVEMEENTEQUIPE  = 404;
    final static int CONSTANTEEVEMEENTSANSEQUIPE  = 456;
    final static int CONSTANTELIEUX  = 1;
    
    
    public static void main(String[]args) 
    {
         ServicesMetier serviceMet = new ServicesMetier();
         ServiceTechnique serviceTec = new ServiceTechnique();
         Evenement evenement1 = null;
         Evenement evenement2 = null;
         
         // On récupere l'evenement avec equipes
        try { 
            evenement1 = serviceMet.getEvenement(CONSTANTEEVEMEENTEQUIPE);
            
        } catch (Throwable ex) {
            Logger.getLogger(mainEnvoiDeMailEvenement.class.getName()).log(Level.SEVERE, null, ex);
        }
        
        // On récupere l'evenement sans equipes
        try { 
            evenement2 = serviceMet.getEvenement(CONSTANTEEVEMEENTSANSEQUIPE);
            
        } catch (Throwable ex) {
            Logger.getLogger(mainEnvoiDeMailEvenement.class.getName()).log(Level.SEVERE, null, ex);
        }
       
        // on récupere le lieux pour mettre a jour l'evenement.
        try {
            evenement1.setLieu(serviceMet.getLieux().get(CONSTANTELIEUX));
        } catch (Throwable ex) {
            Logger.getLogger(mainEnvoiDeMailEvenement.class.getName()).log(Level.SEVERE, null, ex);
        }
        
         // on récupere le lieux pour mettre a jour l'evenement.
        try {
            evenement2.setLieu(serviceMet.getLieux().get(CONSTANTELIEUX));
        } catch (Throwable ex) {
            Logger.getLogger(mainEnvoiDeMailEvenement.class.getName()).log(Level.SEVERE, null, ex);
        }
        
       // on met a jour l'evenment
       serviceMet.MiseAJourEvenement(evenement1);
       
       // on met a jour l'evenment
       serviceMet.MiseAJourEvenement(evenement2);
       
               
       // on envoi les mails a tous les adhérents present dans le listes des participants.
       //serviceTec.envoyerMailEvenement(evenement1);
       
       // on envoi les mails a tous les adhérents present dans le listes des participants.
       serviceTec.envoyerMailEvenement(evenement2);
        
        
         
    }
}
        
