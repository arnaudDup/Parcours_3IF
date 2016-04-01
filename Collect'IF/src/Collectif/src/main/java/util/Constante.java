/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package util;

import java.util.Date;

/**
 *
 * @author adupeyrat
 * Classe nous permettant de définir l'ensemble des dconstante qui définisent notre programme. 
 */
public class Constante {
    // définition des constantes.
    public static final String ADRESSMAIL = "collectif@collectif.org";
    public static final String BIENVENUE = "Bienvenue chez Collect'IF";
    public static final String EVENT = "Nouvel Evenement Collect'IF";
    public static final String EMAILRESP = "responsable.responsable@insa-lyon.fr";
    public static final String MDPRESP = "mpdResp";
    public static final int NBBOUCLE = 2;
    
    public static String FormatDate(Date d)
    {
       return d.getDate()+"/"+d.getMonth()+"/"+d.getYear();
    }
}
