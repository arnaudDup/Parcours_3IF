package metier.modele;

import java.util.Date;
import javax.annotation.Generated;
import javax.persistence.metamodel.SingularAttribute;
import javax.persistence.metamodel.StaticMetamodel;
import metier.modele.Activite;
import metier.modele.Adherent;
import metier.modele.Evenement;

@Generated(value="EclipseLink-2.5.2.v20140319-rNA", date="2016-03-31T18:27:51")
@StaticMetamodel(DemandeEvenement.class)
public class DemandeEvenement_ { 

    public static volatile SingularAttribute<DemandeEvenement, Activite> activite;
    public static volatile SingularAttribute<DemandeEvenement, Date> dateEvent;
    public static volatile SingularAttribute<DemandeEvenement, Adherent> adherent;
    public static volatile SingularAttribute<DemandeEvenement, Long> id;
    public static volatile SingularAttribute<DemandeEvenement, Long> version;
    public static volatile SingularAttribute<DemandeEvenement, Evenement> evenement;

}