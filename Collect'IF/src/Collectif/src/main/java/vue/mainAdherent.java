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
public class mainAdherent {
    
    public static void main(String[]args) 
    {
         List<Adherent> listAdherents;
        // Inscription d'un client existant
        ServicesMetier service = new ServicesMetier();
       
        Adherent adherent1 = new Adherent(); 
        adherent1.setMail("arnaud.dupeyrat@gmail.com"); 
        adherent1.setAdresse("35 chemin du suye, peymeinade 06530");
        adherent1.setMdp("mdp");
        adherent1.setNom("dupeyrat");
        adherent1.setPrenom("Arnaud");
        
        Adherent adherent2 = new Adherent(); 
        adherent2.setMail("antoine.breton@gmail.com"); 
        adherent2.setAdresse("157 grand rue saint claire, caluire et cuire 69300");
        adherent2.setMdp("mdp");
        adherent2.setNom("Breton");
        adherent2.setPrenom("Antoine");
        
        // incripstion d'un adhérents.
        if(!service.inscription(adherent1))
                System.out.println("Probleme au niveau de l'incription");
        else
            System.out.println("Inscription correctement effectué"); 
         
        // incripstion d'un adhérents.
        if(!service.inscription(adherent2))
                System.out.println("Probleme au niveau de l'incription");
        else
            System.out.println("Inscription correctement effectué"); 
           
        // Inscription d'un client existant  
        if(!service.inscription(adherent1))
                System.out.println("existe deja");
        else 
            System.out.println("Inscription correctement effectué"); 
           
        // on récupére l'ensmeble des adhérents qui ont été persisté dans notre base de données.
        try {
            
            listAdherents = service.getAdherents();
            System.out.println("Les adhérents sont : " + listAdherents); 
            
        } catch (Throwable ex) {
           ex.printStackTrace();
        }
        
        // on récupere un adhérent avec son id. 
        Adherent test = new Adherent();
         try {
            
            test = service.getAdherent(1);
            System.out.println("Les adhérents sont : " + test); 
            
        } catch (Throwable ex) {
           ex.printStackTrace();
        }
         
        // update d'un adhérent
        test.setNom("Dupeyrat");
        
        if(service.MiseAJourAdherent(test))
                System.out.println("modification validé");
        else 
            System.out.println("modification invalide");
        // connexion d'un adhérent présent dans notre base de données.
        try
        {
            System.out.println("Connexion de l'adherent arnaud: " ); 
            Adherent ar = service.connexion("arnaud.dupeyrat@gmail.com","mdp");
            System.out.println(ar);
        }
        catch(Throwable e)
        {
            e.printStackTrace();
        }
        
        // connexion d'un adhérent pas présent dans notre base de données.
        try
        {
            Adherent ar = service.connexion("rborrotimatiasdantas4171@free.fr","mdp");
            System.out.println(ar);
        }
        catch(Throwable e)
        {
            e.printStackTrace();
        }
       
     }
 }

        
