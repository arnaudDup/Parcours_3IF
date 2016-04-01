package dao;

import java.util.List;
import javax.persistence.EntityManager;
import javax.persistence.EntityNotFoundException;
import javax.persistence.Query;
import metier.modele.Adherent;
import metier.modele.DemandeEvenement;

public class AdherentDao {
    
    public void create(Adherent adherent) throws Throwable {
        EntityManager em = JpaUtil.obtenirEntityManager();
        try {
            em.persist(adherent);
        }
        catch(Exception e) {
            throw e;
        }
    }
    
    public Adherent update(Adherent adherent) throws Throwable {
        EntityManager em = JpaUtil.obtenirEntityManager();
        try {
            adherent = em.merge(adherent);
        }
        catch(Exception e){
            throw e;
        }
        return adherent;
    }
    
    public Adherent findById(long id) throws Throwable {
        EntityManager em = JpaUtil.obtenirEntityManager();
        Adherent adherent = null;
        try {
            adherent = em.find(Adherent.class, id);
        }
        catch(Exception e) {
            throw e;
        }
        return adherent;
    }
    
    public List<Adherent> findAll() throws Throwable {
        EntityManager em = JpaUtil.obtenirEntityManager();
        List<Adherent> adherents = null;
        try {
            Query q = em.createQuery("SELECT a FROM Adherent a");
            adherents = (List<Adherent>) q.getResultList();
        }
        catch(Exception e) {
            throw e;
        }
        
        return adherents;
    }
    /**
     * Retourne un adhérent a partir des ses identifiants.
     * @param mail mail de l'adherent 
     * @param mdp mot de passe de l'adherent
     * @return un adhérent
     * @throws Throwable 
     */
    public Adherent getByCredentials(String mail, String mdp) throws EntityNotFoundException {
        EntityManager em = JpaUtil.obtenirEntityManager();
        
        List<Adherent> adherents = null;
        try {
            Query q = em.createQuery("SELECT a FROM Adherent a WHERE a.mail='"+mail+"' AND a.mdp='"+mdp+"'");
            adherents = (List<Adherent>) q.getResultList();
        }
        catch(Exception e) {
            throw e;
        }
        
        
        // Si l'adérent n'existe pas, on retourne une exception
        if(adherents.isEmpty())
            throw new EntityNotFoundException();
        
        return adherents.get(0);
    }
    
        /**
     * Retourne vrai si l'adhérent existe
     * @param mail mail de l'adherent
     * @param mdp mot de passe de l'adherent
     * @return un adhérent
     * @throws Throwable 
     */
    public boolean exists(String mail, String mdp) throws Throwable {
        EntityManager em = JpaUtil.obtenirEntityManager();
        
        List<Adherent> adherents = null;
        try {
            Query q = em.createQuery("SELECT a FROM Adherent a WHERE a.mail='"+mail+"' AND a.mdp='"+mdp+"'");
            adherents = (List<Adherent>) q.getResultList();
        }
        catch(Exception e) {
            throw e;
        }
        
        return !adherents.isEmpty();
    }
    
}
