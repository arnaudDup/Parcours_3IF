package dao;

import java.util.List;
import javax.persistence.EntityManager;
import javax.persistence.Query;
import metier.modele.Activite;

public class ActiviteDao {
    
    public void create(Activite activite) throws Throwable {
        EntityManager em = JpaUtil.obtenirEntityManager();
        try {
            em.persist(activite);
        }
        catch(Exception e) {
            throw e;
        }
    }
    
    public Activite update(Activite activite) throws Throwable {
        EntityManager em = JpaUtil.obtenirEntityManager();
        try {
            activite = em.merge(activite);
        }
        catch(Exception e){
            throw e;
        }
        return activite;
    }
    
    public Activite findById(Integer id) throws Throwable {
        EntityManager em = JpaUtil.obtenirEntityManager();
        Activite activite = null;
        try {
            activite = em.find(Activite.class, id);
        }
        catch(Exception e) {
            throw e;
        }
        return activite;
    }
    
    public List<Activite> findAll() throws Throwable {
        EntityManager em = JpaUtil.obtenirEntityManager();
        List<Activite> activites = null;
        try {
            Query q = em.createQuery("SELECT a FROM Activite a");
            activites = (List<Activite>) q.getResultList();
        }
        catch(Exception e) {
            throw e;
        }
        
        return activites;
    }
    
     public boolean verifiePresence(Activite activite) 
     {
        EntityManager em = JpaUtil.obtenirEntityManager();
        
        List<Activite> activites = null;
        try {
            Query q = em.createQuery("SELECT a FROM Activite a WHERE a.denomination = :deno AND a.parEquipe = :parEqu AND a.nbParticipants = :NB");
            q.setParameter("deno", activite.getDenomination() );
            q.setParameter("NB", activite.getNbParticipants());
            q.setParameter("parEqu", activite.isParEquipe());
            activites = (List<Activite>) q.getResultList();
        }
        catch(Exception e) {
            throw e;
        }
        
        return !activites.isEmpty();
    }    

    public void uptade() {
        throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
    }
}
