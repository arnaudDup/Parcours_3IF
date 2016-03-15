package Client.Vue;

import java.awt.BorderLayout;
import java.awt.EventQueue;

import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.border.EmptyBorder;
import javax.swing.JProgressBar;
import javax.swing.JLabel;

/**
 *	Interface graphique representant la fenetre d'attente.
 * 
 *  <p> Vue permettant d'informer l'utilisateur que l'application est en changement.<p>
 *  
 * @author Antoine BRETON et Arnaud DUPEYRAT
 * 
 */
public class VueAttente extends JFrame {

	/**
	 * Conteneur de la page 
	 */
	private JPanel contentPane;
	
	/**
	 * Reference sur le gestionnaire de vue
	 */
	private Vue vue;
	
	/**
	 * Intancie un nouvel objet de classe
	 * @param vue Reference sur le gestionnaire de vue. 
	 */
	public VueAttente(Vue vue) {
		super();
		setTitle("En attente...");
		this.vue = vue;
		
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		setBounds(100, 100, 297, 153);
		contentPane = new JPanel();
		contentPane.setBorder(new EmptyBorder(5, 5, 5, 5));
		contentPane.setLayout(new BorderLayout(0, 0));
		setContentPane(contentPane);
		
		JLabel lblEnAttente = new JLabel("En attente");
		contentPane.add(lblEnAttente, BorderLayout.CENTER);
	}

}
