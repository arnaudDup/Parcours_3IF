package dao;

import java.util.Date;
import java.util.List;
import javax.persistence.EntityManager;
import javax.persistence.Query;
import metier.modele.Activite;
import metier.modele.Adherent;
import metier.modele.Equipe;
import metier.modele.EvenementAvecEquipe;

public class EquipeDao {
    
    public void create(Equipe equipe) throws Throwable {
        EntityManager em = JpaUtil.obtenirEntityManager();
        try {
            em.persist(equipe);
        }
        catch(Exception e) {
            throw e;
        }
       
    }
    
    
    public Equipe findById(long id) throws Throwable {
        EntityManager em = JpaUtil.obtenirEntityManager();
        Equipe equipe = null;
        try {
            equipe = em.find(Equipe.class, id);
        }
        catch(Exception e) {
            throw e;
        }
        return equipe;
    }
    
    public List<Equipe> findAll() throws Throwable {
        EntityManager em = JpaUtil.obtenirEntityManager();
        List<Equipe> equipes = null;
        try {
            Query q = em.createQuery("SELECT a FROM equipe a");
            equipes = (List<Equipe>) q.getResultList();
        }
        catch(Exception e) {
            throw e;
        }
        
        return equipes;
    }

    public void uptade() {
        throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
    }
}
