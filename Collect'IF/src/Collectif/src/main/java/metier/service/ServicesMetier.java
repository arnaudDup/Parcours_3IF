/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package metier.service;

import com.google.maps.model.LatLng;
import dao.ActiviteDao;
import dao.AdherentDao;
import dao.DemandeEvenementDao;
import dao.EquipeDao;
import dao.EvenementDao;
import dao.JpaUtil;
import dao.LieuDao;
import java.io.File;
import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;
import java.util.Scanner;
import java.util.logging.Level;
import java.util.logging.Logger;
import javax.persistence.EntityNotFoundException;
import metier.modele.Activite;
import metier.modele.Adherent;
import metier.modele.DemandeEvenement;
import metier.modele.Equipe;
import metier.modele.Evenement;
import metier.modele.EvenementAvecEquipe;
import metier.modele.EvenementSansEquipe;
import metier.modele.Lieu;
import util.Constante;

/**
 *
 * @author abreton
 */
public class ServicesMetier {

    
    private AdherentDao aDao = new AdherentDao();
    private ActiviteDao actDao = new ActiviteDao();
    private LieuDao lieuDao = new LieuDao();
    private DemandeEvenementDao demandeEvDao = new DemandeEvenementDao();
    private EvenementDao evDao = new EvenementDao();
    private EquipeDao equipeDao = new EquipeDao();
        						// On conserve une trace des enregisrement dans des fichier du dossier "enregistrement"
  
    /**
     * Methode permettant de persister un nouvelle adherent à notre base de
     * données
     *
     * @param adherent nous adherent ajouté à la base de données
     * @return true si l'dherent est persisté dans la base de données
     * false si l'incription a échoué.
     */
    public boolean inscription(Adherent adherent) 
    {
        boolean test = false;
        
        JpaUtil.creerEntityManager();

        try {
            // On vérifie l'existance du nouvel adhérent  !!  s'il existe on
                      
            if (!aDao.exists(adherent.getMail(), adherent.getMdp())) {

                JpaUtil.ouvrirTransaction();
                
                LatLng coord = util.GeoTest.getLatLng(adherent.getAdresse());
                
                // Récupération des coordonnées
                adherent.setCoordonnees(coord);

                // Persistence
                aDao.create(adherent);
               
                // commit
                JpaUtil.validerTransaction();
                
                test = true;

            }
       } catch (Throwable ex) {
            Logger.getLogger(ServicesMetier.class.getName()).log(Level.SEVERE, null, ex);
            JpaUtil.annulerTransaction();
        }              
       finally {JpaUtil.fermerEntityManager();}
       return test;
    }

  
    /**
     * Methode permettant de simuler une pause à l'aide d'un appel bloquant
     */
    private void pause()
    {
        Scanner s = new Scanner(System.in);
        System.out.println("Pause en attente de réactivation");
        int n = s.nextInt();
    } 
    
    /**
     * Retourne l'adhérent si la connection s'est effectué correctement.
     * Retourne une exeption si l'adhérent n'arrive pas à se connecter.
     *
     * @param mail mail de l'utilisateur. 
     * @param mdp  mot de passe.
     * @return adherent associé au mot de passe et l'adresse en parametre
     */
    public Adherent connexion(String mail, String mdp) throws Throwable
    {
        JpaUtil.creerEntityManager();
        
        Adherent res = aDao.getByCredentials(mail, mdp);

        JpaUtil.fermerEntityManager();

        return res;
    }
    
    /**
     * Méthode permettant de récupérer l'ensemble des adhérents inscrit dans notre base de données.
     * @return ensemble des ahérents persisté dans notre base de données.
     * @throws java.lang.Throwable
     */
    public  List<Adherent> getAdherents() throws Throwable
    {
        
        List<Adherent> res;
        
        JpaUtil.creerEntityManager();
        
        res = aDao.findAll();

        JpaUtil.fermerEntityManager();

        return res;
    }
    
    /**
     * Méthode permettant de recupérer un adherent possédant l'identifiant unique id
     * @param id
     * @return
     * @throws Throwable EntityNotFound
     */
    public Adherent getAdherent(long id) throws Throwable
    {
        JpaUtil.creerEntityManager();
        
        Adherent res = aDao.findById(id);
        
        JpaUtil.fermerEntityManager();
        
        return res;
    }
    
    /**
     * Permet de modifier les paramétre d'un adherent, 
     * @param adherent
     * @return true si la mise a jour s'est terminé correctement.
     * false si la mise à jour a échoué.
     */
    public boolean MiseAJourAdherent (Adherent adherent)  
    {
        boolean test = false;
         
        try {
            JpaUtil.creerEntityManager();
            JpaUtil.ouvrirTransaction();
            aDao.update(adherent);
            JpaUtil.validerTransaction();
            test = true;
            
        } catch (Throwable ex) {
            Logger.getLogger(ServicesMetier.class.getName()).log(Level.SEVERE, null, ex);
            JpaUtil.annulerTransaction();
            
        }finally{
            JpaUtil.fermerEntityManager(); 
            return test; 
        }
     
    }
    
    /**
     * Méthode permettant de creer une nouvelle activité. 
     * @param activite
     * @return true si l'ajout s'est terminé correctement.
     * false si l'ajout a échoué.
     */
    public boolean creerActivite(Activite activite) 
    {
        boolean test = false;
        
        
        try {
            
            JpaUtil.creerEntityManager();

            if(!actDao.verifiePresence(activite))
            {
                JpaUtil.ouvrirTransaction();

                actDao.create(activite);

                // commit
                JpaUtil.validerTransaction();

                test = true;
            }
                        
         } catch (Throwable ex) {
            Logger.getLogger(ServicesMetier.class.getName()).log(Level.SEVERE, null, ex);
            JpaUtil.annulerTransaction();
        }              
       finally {
                JpaUtil.fermerEntityManager();
                return test; 
                 
       }
                      
       
    }
    
    /**
     * Permet de récupérer l'esemble des activites persité dans notre base de donées
     * @return Ensemble des activités
     * @throws Throwable 
     */
    public  List<Activite> getActivites() throws Throwable
    {  
        List<Activite> res;
        
        JpaUtil.creerEntityManager();
        
        res = actDao.findAll();

        JpaUtil.fermerEntityManager();

        return res;
    }
    
    /**
     * Retourne l'activité identifie de maniere unique par son ID
     * @param id
     * @return l'activite identifie  de maniere unique par son id
     * @throws Throwable 
     */
    public Activite getActivite(long id) throws Throwable 
    { 
        JpaUtil.creerEntityManager();
        
        Activite res = actDao.findById(new Integer ((int) id));

        JpaUtil.fermerEntityManager();
        
        return res;
    }
    
    /**
     * Méthode permettant de mettre a jour une activité. 
     * @param activite
     * @return true si la mise a jour s'est terminé correctement.
     * false si la mise à jour a échoué.
     */
    public boolean MiseAJourActivite(Activite activite)  
    {
        boolean test = false;
         
        try {
            JpaUtil.creerEntityManager();
            JpaUtil.ouvrirTransaction();
            actDao.update(activite);
            JpaUtil.validerTransaction();
            test = true;
            
        } catch (Throwable ex) {
            Logger.getLogger(ServicesMetier.class.getName()).log(Level.SEVERE, null, ex);
            JpaUtil.annulerTransaction();
        }finally{
            JpaUtil.fermerEntityManager();
            return test;
        }
     
    }
    
    /**
     * Méthode permettant de renvoyer l'esenble des lieux
     * @return l'ensemble des lieux present dans notre base de données
     * @throws Throwable 
     */   
    public  List<Lieu> getLieux() throws Throwable
    {  
        List<Lieu> res;
        
        JpaUtil.creerEntityManager();
        
        res = lieuDao.findAll();

        JpaUtil.fermerEntityManager();

        return res;
    }
    
    /**
     * Méthode permettant de récuperer l'ensemble des lieux
     * @param evenement
     * @return true si la mise a jour s'est terminé correctement.
     * false si la mise à jour a échoué.
     */
    public  boolean  MiseAJourEvenement(Evenement evenement) 
    {  

        boolean test = false;
        try {
            JpaUtil.creerEntityManager();
            JpaUtil.ouvrirTransaction();
            evDao.update(evenement);
            JpaUtil.validerTransaction();
            test = true; 
        } catch (Throwable ex) {
            Logger.getLogger(ServicesMetier.class.getName()).log(Level.SEVERE, null, ex);
            JpaUtil.annulerTransaction();
        }finally{
            JpaUtil.fermerEntityManager();
            return test; 
        }     
    }
    
    /**
     * Méthode de connexion de l'administrateur. 
     * @param login
     * @param mdp
     * @return Retourne vrai si la connexion est acceptée
     */
    public boolean connexionAdmin(String login, String mdp)
    {
        if(Constante.EMAILRESP.equals(login) && Constante.MDPRESP.equals(mdp) )
            return true;
        return false;
    }
    /**
     * Méthode permettant de persister une demande d'évenement, 
     * Si le nombre de demandes est suffissant alors un événement est associé aux nombres à l'ensemble des demandes précédente.
     * 
     * @param demandeEvenement demande d'événémenent creer
     * @param activite         activité lié à la demande
     * @param adherent         adhérent qui a effectué une demande.
     * @return true si la transaction s'est correctement effectué. 
     * false si la transaction a echoué.
     */
   private boolean persiterDemandeEvenement(DemandeEvenement demandeEvenement, Activite activite, Adherent adherent) 
    {
        boolean test = false;
             
        try{
            JpaUtil.creerEntityManager();
            
            // On vérifie que l'utilisateur n'a pas effectué deux fois la meme demandes
            if(!demandeEvDao.verifiePresence(activite, adherent, demandeEvenement)) 
            {
                // Mise a jour des parametres de la demande d'evenement. 
                demandeEvenement.setActivite(activite);
                demandeEvenement.setAdherent(adherent);

                // On récupere la demande identique à la premiere. 
                List<DemandeEvenement> memeDemande = demandeEvDao.getAdherentsMemeDemande(activite, demandeEvenement.getDate());

                JpaUtil.ouvrirTransaction(); 

                demandeEvDao.create(demandeEvenement);
                
                // Si le nombre de demandes est suffisant on crée un évènement 
                 if(activite.getNbParticipants() != null && memeDemande != null && memeDemande.size() >= activite.getNbParticipants() -1)
                 {
                    System.out.println("Création d'un évènement");
                    
                    Evenement e;

                    ArrayList<Adherent> adherentMemeDemande = new ArrayList<Adherent>() {};

                    pause();


                    Iterator<DemandeEvenement> it = memeDemande.iterator();

                    while(it.hasNext())
                    {                    
                        adherentMemeDemande.add(it.next().getAdherent());
                    }
                    
                    String debug = "<";
                    for(final Adherent ad : adherentMemeDemande )
                        debug+=ad.getNom()+", ";
                    debug += ">";
                    
                     System.out.println("Adherent même demande : "+debug);
                    
                    // on ajoute l'adherent qui a fait la demande a la liste des participants.
                    // NE FONCTIONNE PAS.
                    adherentMemeDemande.add(adherent); 
                    
                     // Création évenement
                     if(activite.isParEquipe())
                     {
                         e = new EvenementAvecEquipe();

                         Equipe equipeA = new Equipe();
                         equipeA.setAdherents( adherentMemeDemande.subList(0, (adherentMemeDemande.size()/2) ) );

                        Equipe equipeB = new Equipe();
                        equipeB.setAdherents( adherentMemeDemande.subList(adherentMemeDemande.size()/2, adherentMemeDemande.size() ));

                        // On persiste les equipes
                        equipeDao.create(equipeB);
                        equipeDao.create(equipeA);


                         //Ajout des Equipe
                         ( (EvenementAvecEquipe)e).setEquipeA(equipeA); 

                         ( (EvenementAvecEquipe)e).setEquipeB(equipeB); 

                        System.out.println("\n\nEquipes : "+equipeA.getAdherents());
                        System.out.println("Equipes : "+equipeB.getAdherents());
                     }
                     else
                     {
                        e = new EvenementSansEquipe();

                        //Ajout des participants
                        ( (EvenementSansEquipe)e).setParticipant(adherentMemeDemande);
                     }
                     
                     // Mise à jour des parametre de l'evenement; 
                     e.setActivite(demandeEvenement.getActivite());
                     e.setDate(demandeEvenement.getDate());

                    // Persistance de l'évènement
                    evDao.create(e);


                    System.out.println("on essai de persister un evenement");
                    System.out.println("");

                    // Mise a jour des demandes                
                    it = memeDemande.iterator();

                    while(it.hasNext())
                    {
                        DemandeEvenement de = it.next();
                        de.setEvenement(e);      
                        demandeEvDao.update(de);
                    }

                }
                // commit
                JpaUtil.validerTransaction();
                
          }
        else
        {
              System.out.println("La demande éxistante !");
        }
            test = true ;
          
                        
        } catch (Throwable ex) {
            Logger.getLogger(ServicesMetier.class.getName()).log(Level.SEVERE, null, ex);
            JpaUtil.annulerTransaction();
        } finally {
            JpaUtil.fermerEntityManager();
            return test; 
        }
    }
    
    
    /**
     * Méthode permettant de persister la demande d'evenement s'il y eu un acces concurents lors de la création d'actités.
     * Si le nombre de demandes est suffissant alors un événement est associé aux nombres à l'ensemble des demandes précédente.
     * 
     * @param demandeEvenement Demande d'événémenent creer
     * @param activite         Activité lié à la demande
     * @param adherent         Adhérent qui a effectué une demande.
     * @return true si la transaction s'est correctement effectué.
     * false si apres 10 essais l'utilisateurs n'a pas pu étre persisté.
     */
    public boolean creerDemandeEvenement(DemandeEvenement demandeEvenement, Activite activite, Adherent adherent) 
    {
        for ( int i = 0 ; i < Constante.NBBOUCLE ; i++)
        {
            if(persiterDemandeEvenement(demandeEvenement, activite,adherent))
            {
                return true; 
            }
             
        }
        System.out.println(); 
        System.out.println("La demande n'a pas été persistée"); 
        System.out.println();
        return false;
        
    }

    /**
     * Permet de récuperer les demande d'évenement deja lié à un événement
     * @param adherent
     * @return 
     */
    public List <DemandeEvenement> recupererDemandesAdherentAvecEvenement (Adherent adherent)
    {
            List<DemandeEvenement> res;

            JpaUtil.creerEntityManager();

            res = demandeEvDao.getDemandesAvecEvenement(adherent);

            JpaUtil.fermerEntityManager();

            return res;
    }
    /**
     * Méthode permettant de retourner l'ensemble des demandes associé à un adherents
     * La liste retourner contient aussi bien les demandes que l'utilisateur a éffectué que 
     * les demandes à venir
     * @param adherent Adherent donct 
     * @return 
     */
    public List <DemandeEvenement> recupererDemandesAdherent (Adherent adherent)
    {
            List<DemandeEvenement> res;

            JpaUtil.creerEntityManager();

            res = demandeEvDao.getDemandes(adherent);

            JpaUtil.fermerEntityManager();

            return res;
    }
    
    /**
     * Méthode permettant de mettre à jour un demande d'événement
     * Permettant de modifié la demande si besoin.
     * 
     * @param demande demande d'evenement modifié.
     * @return true si la mise à jour s'est effectué avec succes
     * false si la mise à jour a échoué.
     */
    public boolean MiseAJourDemandesEvenement (DemandeEvenement demande)  
    {
        
        boolean test = false;
        try {
            JpaUtil.creerEntityManager();
            JpaUtil.ouvrirTransaction();
            demandeEvDao.update(demande);
            JpaUtil.validerTransaction();
            return true;
            
        } catch (Throwable ex) {
            Logger.getLogger(ServicesMetier.class.getName()).log(Level.SEVERE, null, ex);
            JpaUtil.annulerTransaction();
        }finally{
            JpaUtil.fermerEntityManager(); 
            return test;
        }
     
    }
    /**
     * retourne tous les évenements crée, utile pour l'administrateur qui veux visualiser les évènements en cour
     * @return  Liste d'évènement
     */
    public List<Evenement> getEvenements()
    {
           List<Evenement> res= new ArrayList<Evenement>();

            JpaUtil.creerEntityManager();

        try {
            res = evDao.findAll();
        } catch (Throwable ex) {
            Logger.getLogger(ServicesMetier.class.getName()).log(Level.SEVERE, null, ex);
        }

            JpaUtil.fermerEntityManager();

            return res;
    }
    /**
     * Retourne un évenement identifié par l'ID en parametre
     * @param id
     * @return 
     * @throws Throwable 
     */
    public Evenement getEvenement (long id) throws Throwable
    {
            Evenement res;

            JpaUtil.creerEntityManager();

            res = evDao.findById(id);

            JpaUtil.fermerEntityManager();

            return res;
    }
   
        /**
     * Retourne un évenement identifié par l'ID en parametre
     * @param id
     * @return 
     * @throws Throwable 
     */
    public List<Evenement> getEvenementByAdherent (Adherent a) throws Throwable
    {
            List<Evenement> res;

            JpaUtil.creerEntityManager();

            res = evDao.findByAdherent(a);

            JpaUtil.fermerEntityManager();

            return res;
    }
    
    /**
     * Méthode permettant de retourner l'ensemble des evenement dont le lieu n'est pas encore défini.
     * @return
     * @throws Throwable 
     */
    public  List <Evenement> getEvenementsSansLieux() throws Throwable
    {  
        List<Evenement> res;
        
        JpaUtil.creerEntityManager();
        
        res = evDao.EvenementsSansLieux();

        JpaUtil.fermerEntityManager();

        return res;
    }
    
}