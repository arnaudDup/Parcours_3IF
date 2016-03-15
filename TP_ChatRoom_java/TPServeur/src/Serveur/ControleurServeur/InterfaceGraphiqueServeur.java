package Serveur.ControleurServeur;

import java.awt.BorderLayout;
import java.awt.EventQueue;

import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.border.EmptyBorder;
import javax.swing.SpringLayout;

import java.awt.CardLayout;
import java.awt.GridBagLayout;

import javax.swing.JTextPane;

import java.awt.GridBagConstraints;

import javax.swing.BoxLayout;
import javax.swing.DefaultListModel;
import javax.swing.JLabel;
import javax.swing.JButton;
import javax.swing.JList;
import javax.swing.JScrollPane;

import Common.Message;

import java.awt.event.ActionListener;
import java.awt.event.ActionEvent;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;
import java.io.IOException;
import java.util.HashMap;

/**
 * Interface graphique permettant d'obtenir une vision globale des differentes connexions des utilisateurs aux differentes chat.
 * 
 * @author Antoine BRETON et Arnaud DUPEYRAT
 *
 */
public class InterfaceGraphiqueServeur extends JFrame {

	/**
	 * Conteneur de la Frame 
	 */
	private JPanel contentPane;	
	
	/**
	 * Liste contenant les differentes connexions au serveur
	 */
	private JList listLog;
	
	/**
	 * Model de liste des log.
	 */
	private DefaultListModel modelLog;
	
	/**
	 * Permettant de faire le lien entre le model et la vue
	 */
	private ControleurSe controleur;
	
	/**
	 * Instancie un nouvel objet de classe.
	 * @param controleur Lien entre le model et les vues 
	 */
	public InterfaceGraphiqueServeur(final ControleurSe controleur) {
		this.controleur = controleur;
		setTitle("Serveur Chat");
		setVisible(true);
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		setBounds(100, 100, 710, 531);
		contentPane = new JPanel();
		contentPane.setBorder(new EmptyBorder(5, 5, 5, 5));
		setContentPane(contentPane);
		contentPane.setLayout(new BorderLayout(0, 0));
		
		// Liste
		modelLog = new DefaultListModel();		
		JScrollPane jscrollPane = new JScrollPane();
		listLog = new JList(modelLog);	
		jscrollPane.setViewportView(listLog);

		contentPane.add(jscrollPane, BorderLayout.CENTER);
		
		// On ecrit le callBack de fermeture de la frame
		this.addWindowListener(new WindowAdapter(){
			// Quand on ferme la frame, on se deconnecte du chat
            public void windowClosing(WindowEvent e){
				try {
					controleur.getModele().SerialiserChats(controleur.getNomFichier());
				} catch (IOException e1) {
					// TODO Auto-generated catch block
					System.out.println("Impossible de serialiser le serveur");
					e1.printStackTrace();
				}
				
				System.exit(0);	
            }
        });
		
		
		JButton ClickButtonDeconnecterServeur = new JButton("Deconnecter Serveur");
		ClickButtonDeconnecterServeur.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				try {
					controleur.getModele().SerialiserChats(controleur.getNomFichier());
					System.out.println("Chats sérialisés");
				} catch (IOException e1) {
					// TODO Auto-generated catch block
					System.out.println("Impossible de serialiser le serveur");
					e1.printStackTrace();
				}
				
				System.exit(0);
			}
		});
		contentPane.add(ClickButtonDeconnecterServeur, BorderLayout.SOUTH);
		
		
	}
	
	
	/**
	 * Methode permettant d'ajouter un message a notre liste de log. 
	 * @param contenu Contenu de la connexion.
	 */
	public void AddMessageLog(String contenu)
	{
		modelLog.addElement(contenu);
		repaint();
	}
}
