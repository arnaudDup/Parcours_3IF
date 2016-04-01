package dao;

import java.util.List;
import javax.persistence.EntityManager;
import javax.persistence.Query;
import metier.modele.Activite;
import metier.modele.Adherent;
import metier.modele.Evenement;
import metier.modele.EvenementAvecEquipe;

public class EvenementDao {
    
    public void create(Evenement evenment) throws Throwable {
        EntityManager em = JpaUtil.obtenirEntityManager();
        try {
            em.persist(evenment);
        }
        catch(Exception e) {
            throw e;
        }
    }
    
    public Evenement update(Evenement event) throws Throwable {
        EntityManager em = JpaUtil.obtenirEntityManager();
        try {
            event = em.merge(event);
        }
        catch(Exception e){
            throw e;
        }
        return event;
    }
    
    public Evenement findById(long id) throws Throwable {
        EntityManager em = JpaUtil.obtenirEntityManager();
        Evenement event = null;
        try {
            event = em.find(Evenement.class, id);
        }
        catch(Exception e) {
            throw e;
        }
        return event;
    }
    
    public List<Evenement> findAll() throws Throwable {
        EntityManager em = JpaUtil.obtenirEntityManager();
        List<Evenement> event = null;
        try {
            Query q = em.createQuery("SELECT a FROM Evenement a");
            event = (List<Evenement>) q.getResultList();
        }
        catch(Exception e) {
            throw e;
        }
        
        return event;
    }

    public void uptade() {
        throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
    }
    
     public List<Evenement> EvenementsSansLieux() throws Throwable {
        EntityManager em = JpaUtil.obtenirEntityManager();
        List<Evenement> event = null;
        try {
            Query q = em.createQuery("SELECT e FROM Evenement e WHERE e.lieu = NULL ");
            event = (List<Evenement>) q.getResultList();
        }
        catch(Exception e) {
            throw e;
        }
        
        return event;
    }

     /**
      * Cette fonction récupère une liste d'évenement qui concernent un adhérent
      * @param adherent
      * @return liste d'évènement
      */
    public List<Evenement> findByAdherent(Adherent a) {
       
        EntityManager em = JpaUtil.obtenirEntityManager();
        List<Evenement> events = null;
        
        try {
               /* Query q = em.createQuery("SELECT d FROM DemandeEvenement d WHERE d.adherent = :adherent");
            q.setParameter("adherent", ad);*/

            // Si l'évenement n'est pas null, on ne récupère pas la demande
            Query q = em.createQuery("SELECT d.evenement FROM DemandeEvenement d WHERE d.adherent = :adherent AND d.evenement != NULL");
            q.setParameter("adherent", a);
       //   Query q = em.createQuery("SELECT a FROM Evenement a");
       // Query q = em.createQuery("SELECT e FROM EvenementAvecEquipe e, Equipe a WHERE e");
            events = (List<Evenement>) q.getResultList();
        }
        catch(Exception e) {
            throw e;
        }
        
        return events;
    }
}
