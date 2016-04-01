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
public class mainActivites {
    
    public static void main(String[]args) 
    {
         List<Activite> listActivite;
        // Inscription d'un client existant
        ServicesMetier service = new ServicesMetier();
       
        Activite activite1 = new Activite(); 
        activite1.setDenomination("bowling");
        activite1.setNbParticipants(4);
        activite1.setParEquipe(false);
        
        Activite activite2 = new Activite(); 
        activite2.setDenomination("volley");
        activite2.setNbParticipants(12);
        activite2.setParEquipe(true);
        
        Activite activite3 = new Activite(); 
        activite3.setDenomination("tata");
        activite3.setNbParticipants(12);
        activite3.setParEquipe(true);
        
        // incripstion d'un adhérents.
        if(!service.creerActivite(activite1))
                System.out.println("Probleme au niveau de l'incription");
        else
            System.out.println("Ajout de l'activé correct"); 
         
        // incripstion d'un adhérents.
        if(!service.creerActivite(activite1))
                System.out.println("Probleme au niveau de l'incription");
        else
            System.out.println("Ajout de l'activé correct");  
           
        // incripstion d'un adhérents.
        if(!service.creerActivite(activite2))
                System.out.println("Probleme au niveau de l'incription");
        else
            System.out.println("Ajout de l'activé correct");  
        
        if(!service.creerActivite(activite2))
                System.out.println("Probleme au niveau de l'incription");
        else
            System.out.println("Ajout de l'activé correct"); 
           
        // on récupére l'ensmeble des adhérents qui ont été persisté dans notre base de données.
        try {
            
            listActivite = service.getActivites();
            System.out.println("Les activites présentes sont : " + listActivite); 
            
        } catch (Throwable ex) {
           ex.printStackTrace();
        }
        
        // on récupere un adhérent avec son id. 
        Activite test = new Activite();
         try {
            
            test = service.getActivite(1);
            System.out.println("L'activite est : " + test); 
            
        } catch (Throwable ex) {
           ex.printStackTrace();
        }
         
        // update d'une activite
        test.setDenomination("toto");
        
        if(service.MiseAJourActivite(test))
                System.out.println("modification validé");
        else 
            System.out.println("modification invalide");
       
     }
 }

        
