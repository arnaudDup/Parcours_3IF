package metier.modele;

import java.io.Serializable;
import java.util.List;
import javax.persistence.CascadeType;
import javax.persistence.Entity;
import javax.persistence.GeneratedValue;
import javax.persistence.GenerationType;
import javax.persistence.Id;
import javax.persistence.ManyToMany;


@Entity
public class EvenementSansEquipe extends Evenement implements Serializable 
{
   
    @ManyToMany
    private List<Adherent> participants;

    public List<Adherent> getParticipant() {
        return participants;
    }

    public void setParticipant(List<Adherent> participant) {
        this.participants = participant;
    }

   
    public EvenementSansEquipe() {
    }

    @Override
    public String toString() {
        return "Event par équipe{ Participant=" + participants + "}";
    }
       
}
