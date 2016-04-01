package metier.modele;

import java.io.Serializable;
import java.util.Date;
import java.util.List;
import javax.persistence.CascadeType;
import javax.persistence.Column;
import javax.persistence.Entity;
import javax.persistence.GeneratedValue;
import javax.persistence.GenerationType;
import javax.persistence.Id;
import javax.persistence.ManyToOne;
import javax.persistence.Temporal;
import javax.persistence.TemporalType;
import javax.persistence.Version;


@Entity
public class DemandeEvenement implements Serializable
{
   
    @Id
    @GeneratedValue(strategy = GenerationType.AUTO)
    private long id;
    
    @ManyToOne 
    private Adherent adherent;
    
    @ManyToOne 
    private Activite activite;
    
    @ManyToOne 
    private Evenement evenement;
    
    // Configuration de l'attribut de versionning.
    // permettant de gerer l'acces concurents.
    @Version
    @Column(name = "VERSION")
    private Long version;

    public Long getVersion() {
        return version;
    }

    public void setVersion(Long version) {
        this.version = version;
    }

    public Date getDateEvent() {
        return dateEvent;
    }

    public void setDateEvent(Date dateEvent) {
        this.dateEvent = dateEvent;
    }
    
    @Temporal (TemporalType.DATE)
    private Date dateEvent;

    public Adherent getAdherent() {
        return adherent;
    }

    public void setAdherent(Adherent adherent) {
        this.adherent = adherent;
    }

    public Activite getActivite() {
        return activite;
    }

    public void setActivite(Activite activite) {
        this.activite = activite;
    }

    public Evenement getEvenement() {
        return evenement;
    }

    public void setEvenement(Evenement evenement) {
        this.evenement = evenement;
    }

    public Date getDate() {
        return dateEvent;
    }

    public void setDate(Date date) {
        this.dateEvent = date;
    }
    
    
  
    public DemandeEvenement() {
    }

    @Override
    public String toString() {
        return "Event par équipe{" + "Evement=" + evenement + ", adherent =" + adherent+ "date =" + dateEvent + "Activite = " + activite +"}";
    }

    public Long getId() {
        return id;
    }

}
