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
public class mainEvenement {
    
    public static void main(String[]args) throws Throwable 
    {
        ServicesMetier service = new ServicesMetier();
               
       // On récupère un adhérent       
       Adherent a = service.getAdherent(39);
       
       System.out.println("Adherent : "+a.getNom());
       List<Evenement> events = service.getEvenementByAdherent(a);
       
       for(Evenement e : events)
       {
           System.out.println(e.getActivite().getDenomination()+" "+e.getDate()+" "+e.getClass().getName());
       }
     }
 }

        
