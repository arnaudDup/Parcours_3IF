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
public class mainDemandeEvenement {
    
    final static int  CONSTANTEACTIVITE = 15;
    
    public static void main(String[]args) 
    {
         
        // Inscription d'un client existant
        ServicesMetier service = new ServicesMetier();
        Activite activite = null;
        List<Adherent> test = null;
        // on récupere l'activite dans la liste des activités possible.
        try {
            activite = service.getActivite(CONSTANTEACTIVITE);
            
        } catch (Throwable ex) {
            Logger.getLogger(mainDemandeEvenement.class.getName()).log(Level.SEVERE, null, ex);
        }
        
        // on récupere la liste des utilisateurs présent dans la base de données.
        try {
            
            test = service.getAdherents();
            
        } catch (Throwable ex) {
            Logger.getLogger(mainDemandeEvenement.class.getName()).log(Level.SEVERE, null, ex);
        }
        
        
        // définition d'un nouvelle date.
        Date d = new Date();
        d.setDate(18);
        d.setYear(16);
        d.setMonth(3);
        
       
        
        //System.out.println(test);
        // on creer les demandes d'evenements. 
        for(int i = 0; i< 13; i++)
        {
            
            // creation de la demande
            DemandeEvenement dem = new DemandeEvenement ();

            // on affecte la date a la demande.
            dem.setDate(d);
                     
            
            System.out.println(i+" Demande de :  "+ test.get(i).getNom());
            // affectation de la demande+
            service.creerDemandeEvenement (dem,activite,test.get(i)); 
           // System.out.println("dem :" +dem);
        }
     }
}
        
