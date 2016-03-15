package Client.Vue;

import java.awt.BorderLayout;
import java.awt.EventQueue;

import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.border.EmptyBorder;
import javax.swing.JButton;
import javax.swing.JTextField;
import javax.swing.JLabel;

import java.awt.event.ActionListener;
import java.awt.event.ActionEvent;
import java.util.HashMap;

/**
 *	Interface graphique representant la vue d'accueil.
 * 
 *  <p> La vue dispose de plusieurs disponibilités:
 *  - Choix du speudo
 *  - Choix de l'adresse du serveur que le client veut rejoindre. 
 *  - Le bouton permettant la connection au serveur.<p>
 *  
 * @author Antoine BRETON et Arnaud DUPEYRAT
 * 
 */
public class VueAccueil extends JFrame {
	
	/**
	 * Reference permettant d'obtenir un lien le gestionnaire des vues 
	 */
	private Vue vue;
	
	/**
	 * Conteneur de la Frame
	 */
	private JPanel contentPane;
	
	/**
	 * JtextField permettant de récupere le speudo
	 */
	private JTextField TF_Pseudo;
	
	/**
	 * JtextField permettant de récupere l'adresse IP
	 */
	private JTextField TF_IP;

	/**
	 * Instancie une nouvel objet de classe. 
	 * @param vue Reference sur le gestionnaire de vue 
	 */
	public VueAccueil(final Vue vue) {
		super();
		setResizable(false);
		setTitle("Accueil");
		this.vue = vue;
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		setBounds(100, 100, 442, 294);
		contentPane = new JPanel();
		contentPane.setBorder(new EmptyBorder(5, 5, 5, 5));
		setContentPane(contentPane);
		contentPane.setLayout(null);
		
		// Button connect
		JButton ButtonConnect = new JButton("Se connecter");
		ButtonConnect.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent arg0) {
				
				// A chaque clic on construit un evenement
				HashMap<String,Object> event = new  HashMap<String,Object>();
				event.put("Event", "ClicBoutonConnecter");
				vue.getControleur().considererEvent(event);
			}
		});
		
		ButtonConnect.setBounds(131, 161, 146, 23);
		contentPane.add(ButtonConnect);
		
		// TextFields
		TF_Pseudo = new JTextField();
		TF_Pseudo.setBounds(164, 59, 86, 20);
		contentPane.add(TF_Pseudo);
		TF_Pseudo.setColumns(10);
		
		TF_IP = new JTextField();
		TF_IP.setBounds(164, 110, 86, 20);
		contentPane.add(TF_IP);
		TF_IP.setColumns(10);
		
		JLabel lblPseudo = new JLabel("Pseudo");
		lblPseudo.setBounds(164, 39, 46, 14);
		contentPane.add(lblPseudo);
		
		JLabel lblIpServeur = new JLabel("IP Serveur");
		lblIpServeur.setBounds(164, 90, 86, 14);
		contentPane.add(lblIpServeur);
	}
	
	/**
	 * 
	 * @return Retourne le speudo choisi du client 
	 */
	public String getNom()
	{ 
		return TF_Pseudo.getText();
		
	}
	
	/**
	 * 
	 * @return Retourne l'adresse IP desire pour la connection. 
	 */
	public String getIP()
	{ 
		return TF_IP.getText();
	}
}
