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
import metier.modele.Lieu;
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
public class mainLieux {
    
    public static void main(String[]args) 
    {
         List<Lieu> listLieux;
         ServicesMetier service = new ServicesMetier();
         
         try {
            
            listLieux =  service.getLieux(); 
            System.out.println("les différents lieux sont : " + listLieux); 
            
        } catch (Throwable ex) {
           ex.printStackTrace();
        }
        
       
     }
 }

        
