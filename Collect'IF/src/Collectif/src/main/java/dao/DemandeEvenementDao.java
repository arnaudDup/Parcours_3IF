package dao;

import java.util.Date;
import java.util.List;
import javax.persistence.EntityManager;
import javax.persistence.Query;
import metier.modele.Activite;
import metier.modele.Adherent;
import metier.modele.DemandeEvenement;
import metier.modele.EvenementAvecEquipe;

public class DemandeEvenementDao {
    
    public void create(DemandeEvenement demandeEvenement) throws Throwable {
        EntityManager em = JpaUtil.obtenirEntityManager();
        try {
            em.persist(demandeEvenement);
        }
        catch(Exception e) {
            throw e;
        }
       
    }
    
    
    public DemandeEvenement update(DemandeEvenement demandeEvenement) throws Throwable {
        EntityManager em = JpaUtil.obtenirEntityManager();
        try {
            demandeEvenement = em.merge(demandeEvenement);
        }
        catch(Exception e){
            throw e;
        }
        return demandeEvenement;
    }
    
    public DemandeEvenement findById(long id) throws Throwable {
        EntityManager em = JpaUtil.obtenirEntityManager();
        DemandeEvenement demandeEvenement = null;
        try {
            demandeEvenement = em.find(DemandeEvenement.class, id);
        }
        catch(Exception e) {
            throw e;
        }
        return demandeEvenement;
    }
    
    public List<DemandeEvenement> findAll() throws Throwable {
        EntityManager em = JpaUtil.obtenirEntityManager();
        List<DemandeEvenement> demandeEvenements = null;
        try {
            Query q = em.createQuery("SELECT a FROM demandeEvenement a");
            demandeEvenements = (List<DemandeEvenement>) q.getResultList();
        }
        catch(Exception e) {
            throw e;
        }
        
        return demandeEvenements;
    }

    public void uptade() {
        throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
    }
    
     public List<DemandeEvenement> getAdherentsMemeDemande(Activite a, Date d)
    {
        EntityManager em = JpaUtil.obtenirEntityManager();
        List<DemandeEvenement> demandes = null;
        try {
            // Si l'évenement n'est pas null, on ne récupère pas la demande
            Query q = em.createQuery("SELECT d FROM DemandeEvenement d WHERE d.activite = :activite AND d.dateEvent = :date AND d.evenement = NULL");
            q.setParameter("activite", a);
            q.setParameter("date", d);
          // q.setParameter("event", null);
            
            demandes = (List<DemandeEvenement>) q.getResultList();
        }
        catch(Exception e) {
            throw e;
        }
        
        return demandes;
    }
     
     
    public List<DemandeEvenement> getDemandes(Adherent ad)
    {
        EntityManager em = JpaUtil.obtenirEntityManager();
        List<DemandeEvenement> demandes = null;
        
        try {
            // Si l'évenement n'est pas null, on ne récupère pas la demande
            Query q = em.createQuery("SELECT d FROM DemandeEvenement d WHERE d.adherent = :adherent");
            q.setParameter("adherent", ad);
            demandes = (List<DemandeEvenement>) q.getResultList();
        }
        catch(Exception e) {
            throw e;
        }
        
        return demandes;
    }
    
     public List<DemandeEvenement> getDemandesAvecEvenement(Adherent ad)
    {
        EntityManager em = JpaUtil.obtenirEntityManager();
        List<DemandeEvenement> demandes = null;
        
        try {
            // Si l'évenement n'est pas null, on ne récupère pas la demande
            Query q = em.createQuery("SELECT d FROM DemandeEvenement d WHERE d.adherent = :adherent AND d.evenement != NULL");
            q.setParameter("adherent", ad);
            demandes = (List<DemandeEvenement>) q.getResultList();
        }
        catch(Exception e) {
            throw e;
        }
        
        return demandes;
    }
    
     public boolean verifiePresence(Activite activite, Adherent adherent, DemandeEvenement demandeEvenement) 
     {
        EntityManager em = JpaUtil.obtenirEntityManager();
        
        List<DemandeEvenement> demandes = null;
        try {
            Query q = em.createQuery("SELECT e FROM DemandeEvenement e WHERE e.activite = :act AND e.adherent = :ad AND e.dateEvent = :date");
            q.setParameter("act", activite );
            q.setParameter("ad", adherent);
            q.setParameter("date", demandeEvenement.getDate());
            demandes = (List<DemandeEvenement>) q.getResultList();
        }
        catch(Exception e) {
            throw e;
        }
        
        return !demandes.isEmpty();
    }
}
