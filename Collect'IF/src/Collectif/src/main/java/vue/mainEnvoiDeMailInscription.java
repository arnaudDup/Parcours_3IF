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
import static metier.modele.DemandeEvenement_.adherent;
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


public class mainEnvoiDeMailInscription {
    
    final static int CONSTANTEADHERENT  = 39;
    
    
    public static void main(String[]args) 
    {
         ServicesMetier serviceMet = new ServicesMetier();
         ServiceTechnique serviceTec = new ServiceTechnique();
         Adherent adherent = new Adherent(); 
         
         // On récupere un adherent identifié par l'id 1; 
        try { 
            adherent = serviceMet.getAdherent(CONSTANTEADHERENT);
            
        } catch (Throwable ex) {
            Logger.getLogger(mainEnvoiDeMailInscription.class.getName()).log(Level.SEVERE, null, ex);
        }
       
       // on envoi les mails a tous les adhérents present dans le listes des participants.
       serviceTec.envoyerMailInscriptionReussie(adherent, true);
       System.out.println(); 
       serviceTec.envoyerMailInscriptionReussie(adherent, false);
        
        
         
    }
}
        
