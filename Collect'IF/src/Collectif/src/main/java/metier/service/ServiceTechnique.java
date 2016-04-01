/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package metier.service;

import com.google.maps.model.LatLng;
import java.util.Iterator;
import metier.modele.Adherent;
import metier.modele.Evenement;
import metier.modele.EvenementAvecEquipe;
import metier.modele.EvenementSansEquipe;
import util.Constante;
import util.GeoTest;

/**
 *
 * @author abreton
 */
public class ServiceTechnique {
   
    public void envoyerMailInscriptionReussie(Adherent adherent, boolean estValide)
    {
        enTete(adherent); 
        if(estValide)
        {   
            System.out.println("Expéditeur :"+ Constante.BIENVENUE);
            System.out.println("Nous vons confirmons votre adhesion à notre association Collect'if. Votre Numéro d'adherent est le: "+ adherent.getId());
        }
        else
        {
            System.out.println("Votre adhesion à l'association Collect'IF a malencontreusement échoué... Merci de recommencez");
        }
        System.out.println("\nCordialement,");
        System.out.println("Collect'IF");
    }
    
     public void envoyerMailEvenement(Adherent adherent, Evenement evenement)
    {
        enTete(adherent);
        System.out.println("\n Comme vous l'aviez shouaité, Collect'IF organise un évenement de" /* Mettre à jour l'activité de l'évenement*/ +"le " + evenement.getDate() +".");
        System.out.println("\nVous trouverez ci-dessous les détails de cet évenement.");
        System.out.println();
        détailEvenement(evenement,adherent);
        System.out.println("\nCordialement,");
        System.out.println("Le responsable de Collect'IF");
        
    }
     private void enTete(Adherent adherent)
     {
        System.out.println("------------------------------- Mail -------------------------------");
        System.out.println("Expéditeur :"+ Constante.ADRESSMAIL);
        System.out.println("Pour :"+adherent.getMail());
        System.out.println("\nBonjour,"+adherent.getPrenom()+"\n");
     }
     
     private void détailEvenement(Evenement evenement, Adherent adherent)
     {
        System.out.println("Expéditeur :"+ Constante.EVENT);
        System.out.println("Evenement :"+ evenement.getActivite().getDenomination()); 
        System.out.println("Date :"+ evenement.getDate());
        System.out.println("Lieu :"+ evenement.getLieu().getAdresse());
        
        // on calcule la distance qui sépare l'adhérent de son evenement.
        double distance = 0; 
        LatLng adherentLocation = new LatLng(adherent.getLatitude(), adherent.getLongitude());
        LatLng evenementLocation = new LatLng(evenement.getLieu().getLatitude(), evenement.getLieu().getLongitude());
        distance = GeoTest.getFlightDistanceInKm(adherentLocation, evenementLocation); 
        
        System.out.println("Distance de chez vous,"+distance + " kilometres");
        
        // on affiche les coequipiers de l'adhérent qui fait appel au service
       if(evenement.getActivite().isParEquipe())
       {
           // on cherche dans quel équipe se trouve l'adherent associé à l'evenement
            boolean estDansA = false;
            Iterator iter  = (((EvenementAvecEquipe)evenement).getEquipeA().getAdherents()).iterator();
            while (iter.hasNext())
            {
                if(adherent.equals(iter.next()))
                    estDansA = true;
            }
           
            Iterator iteratorA  = (((EvenementAvecEquipe)evenement).getEquipeA().getAdherents()).iterator();
            Iterator iteratorB  = (((EvenementAvecEquipe)evenement).getEquipeB().getAdherents()).iterator();
            
            // on traite le cas si l'asherent se trouve dans l'équipeA
            if(estDansA)
            {
                // on affiche les coequipiers.
                System.out.println("\nVos coéquipiers sont :");
                while (iteratorA.hasNext())
                {   
                    Adherent ad = (Adherent) iteratorA.next();
                    if(!adherent.equals(ad))
                        System.out.println(ad.getNom()+ " "+ ad.getPrenom());
                 }
                
                //
                System.out.println("\nL'équipe adverses sera composé de :");
                while (iteratorB.hasNext())
                {
                    Adherent ad = (Adherent) iteratorB.next();
                    System.out.println(ad.getNom()+ " "+ ad.getPrenom());
                 }
            }
            
            // on traite le cas si l'adherent se trouve dans l'équie B
            else
            {
                 // on affiche les coequipiers.
                System.out.println("\nVos coéquipiers sont :");
                while (iteratorB.hasNext())
                {   
                    Adherent ad = (Adherent) iteratorB.next();
                    if(!adherent.equals(ad))
                        System.out.println(ad.getNom()+ " "+ ad.getPrenom());
                 }
                
                //
                System.out.println("\nL'équipe adverses sera composé de :");
                while (iteratorA.hasNext())
                {
                    Adherent ad = (Adherent) iteratorA.next();
                    System.out.println(ad.getNom()+ " "+ ad.getPrenom());
                 }        
            }
   
       }
       
       // l'evenement est alors sans équipes.
       else
       {
           // on itere sur le liste des participants
           Iterator iter  = ((EvenementSansEquipe)evenement).getParticipant().iterator();
           
           // affichage des partenaires de l'adherent.
           System.out.println(" \nVous serais accompagné de : ");
            while (iter.hasNext())
            {
                Adherent ad = (Adherent) iter.next();
                if(!adherent.equals(ad))
                    System.out.println(ad.getNom()+ " "+ ad.getPrenom());
            }
       }
       
     }
    public boolean connexionResponsable(String email, String mdp)
    {
        boolean verif = false; 
        
        if(email == Constante.EMAILRESP )
            if (mdp == Constante.MDPRESP)
                verif = true; 
        
        return verif; 
    }
    
    public void envoyerMailEvenement (Evenement evenement)
    {
        if(evenement.getActivite().isParEquipe())
        {
            // On envoi le mail a tous les adhérents de l'équipe A; 
            Iterator iterA = ((EvenementAvecEquipe)evenement).getEquipeA().getAdherents().iterator();
            while (iterA.hasNext())
            {
                System.out.println();
                Adherent adherent = (Adherent) iterA.next(); 
                envoyerMailEvenement(adherent, evenement);
                System.out.println();
            }

            // on envoi le mail à tous les adherents de l'équipe B
            Iterator iterB = ((EvenementAvecEquipe)evenement).getEquipeB().getAdherents().iterator();
            while (iterB.hasNext())
            {
                System.out.println();
                Adherent adherent = (Adherent) iterB.next(); 
                envoyerMailEvenement(adherent, evenement);
                System.out.println();
            }
        }
        else
        {
             Iterator iter = ((EvenementSansEquipe)evenement).getParticipant().iterator();
             
             while (iter.hasNext())
            {
                System.out.println();
                Adherent adherent = (Adherent) iter.next(); 
                envoyerMailEvenement(adherent, evenement);
                System.out.println();
            }
        }
        
    }
}
