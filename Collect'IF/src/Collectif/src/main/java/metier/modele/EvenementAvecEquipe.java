package metier.modele;

import java.io.Serializable;
import java.util.List;
import javax.persistence.Entity;
import javax.persistence.GeneratedValue;
import javax.persistence.GenerationType;
import javax.persistence.Id;
import javax.persistence.ManyToMany;
import javax.persistence.OneToOne;


@Entity
public class EvenementAvecEquipe extends Evenement implements Serializable 
{
   
    @OneToOne
    private Equipe equipeA;
    
    @OneToOne
    private Equipe equipeB;   

    public Equipe getEquipeA() {
        return equipeA;
    }

    public void setEquipeA(Equipe equipeA) {
        this.equipeA = equipeA;
    }

    public Equipe getEquipeB() {
        return equipeB;
    }

    public void setEquipeB(Equipe equipeB) {
        this.equipeB = equipeB;
    }

   
    public EvenementAvecEquipe() {
    }

    @Override
    public String toString() {
        return "Event par équipe{" + "equipe A=" + equipeA + ", equipe B=" + equipeB + "}";
    }
       
}
