package Client.Vue;

import java.awt.BorderLayout;
import java.awt.Component;
import java.awt.EventQueue;
import java.awt.TextArea;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;
import java.util.Enumeration;
import java.util.HashMap;
import java.util.Iterator;
import java.util.LinkedList;

import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.border.EmptyBorder;
import javax.swing.DefaultListCellRenderer;
import javax.swing.DefaultListModel;
import javax.swing.JList;
import javax.swing.JTabbedPane;
import javax.swing.JScrollPane;
import javax.swing.JTextField;
import javax.swing.JTextArea;
import javax.swing.JButton;
import javax.swing.ListCellRenderer;
import javax.swing.JLabel;

import java.awt.FlowLayout;

import javax.swing.SwingConstants;

import Common.Message;

/**
 *	Interface graphique representant la choix du chat.
 * 
 *  <p> La vue dispose de plusieurs disponibilités:
 *  - La liste des differents chats presents sur la serveur.
 *  - La possibilite de se connecter a l'un de ses chat. 
 *  - La possibilite d'ajouter un nouveau chat.<p>
 *  
 * @author Antoine BRETON et Arnaud DUPEYRAT
 * 
 */
public class VueChat extends JFrame {

	/**
	 * Conteneur de la page.
	 */
	
	private JPanel contentPane;
	
	/**
	 * Gestionnaire de la vue.
	 */
	private Vue vue;
	
	/**
	 * Liste des messages contenues dans le chat. 
	 */
	private LinkedList<Message> messages;
	
	/**
	 * Identifiant unique d'un chat.  
	 */
	private int id;
	
	/**
	 * Nom du chat.
	 */
	private String nom;
	
	/**
	 * Permettant l'envoi d'un message.
	 */
	private JTextArea textArea;
	
	/**
	 * Permettant d'afficher le nombre d'utilisateurs connectés. 
	 */
	private JLabel nbUtilisateurConnectee;
	private JList listChat;
	
	/**
	 * Composant MVC de la Jlist, pour les chats.
	 */
	private DefaultListModel modelListChat;
	
	/**
	 * Composant MVC de la JList, pour les utilisateurs.
	 */
	private DefaultListModel modelListUsers;
	
	/**
	 * Vue des listes utilisateurs.
	 */
	private VueListeUtilisateurs vueListeUsers;
	
	/**
	 * Instancie un nouvel objet de classe.
	 * @param vue	Gestionnaire de vue.
	 * @param id	Identifiant unique du chat.
	 * @param nom	Nom du chat.
	 */
	public VueChat(final Vue vue, final int id, String nom) {
		this.id = id;
		this.vue = vue;
		this.nom = nom;
		
		
		//On initilise le modeleLIstUsers
		modelListUsers = new DefaultListModel();
		
		// On instancie la vue de la liste utilisateur
		
		vueListeUsers = new VueListeUtilisateurs(this, modelListUsers);
		
		this.setTitle(nom+" - "+id);

		// On ï¿½crit le callBack de fermeture de la frame
		this.addWindowListener(new WindowAdapter(){
			// Quand on ferme la frame, on se deconnecte du chat
            public void windowClosing(WindowEvent e){
            	HashMap<String, Object> event = new HashMap<String, Object>();
				event.put("Event", "ClicDeconnexionChat");
				event.put ("chatID", id);
				vue.getControleur().considererEvent(event);
            }
        });
		
		setBounds(100, 100, 450, 385);
		contentPane = new JPanel();
		contentPane.setBorder(new EmptyBorder(5, 5, 5, 5));
		contentPane.setLayout(new BorderLayout(0, 0));
		setContentPane(contentPane);
		
		JPanel panel_1 = new JPanel();
		contentPane.add(panel_1, BorderLayout.NORTH);
		panel_1.setLayout(new BorderLayout(0, 0));
		
		// Bouton deconnecter
		JButton btnNewButton_1 = new JButton("Deconnecter");
		btnNewButton_1.setHorizontalAlignment(SwingConstants.LEFT);
		panel_1.add(btnNewButton_1, BorderLayout.WEST);
		
		// clic sur bouton deconnecter
		btnNewButton_1.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent arg0) {
				
				HashMap<String, Object> event = new HashMap<String, Object>();
				event.put("Event", "ClicDeconnexionChat");
				event.put ("chatID", id);
				vue.getControleur().considererEvent(event);
			}
		});
		
		JPanel panel_2 = new JPanel();
		FlowLayout flowLayout = (FlowLayout) panel_2.getLayout();
		flowLayout.setAlignment(FlowLayout.LEFT);
		panel_1.add(panel_2, BorderLayout.EAST);
		
		JLabel lblNewLabel = new JLabel("Utilisateur Connect\u00E9s :");
		panel_2.add(lblNewLabel);
		
		nbUtilisateurConnectee = new JLabel("-");
		panel_2.add(nbUtilisateurConnectee);
		
		JButton btnNewButton_2 = new JButton("voir");
		btnNewButton_2.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent arg0) {

				vueListeUsers.setVisible(true);
			}
		});
		panel_2.add(btnNewButton_2);
		
		
		// Liste
		modelListChat = new DefaultListModel();
		JScrollPane jscrollPane = new JScrollPane();
		jscrollPane.setLocation(10, 26);
		jscrollPane.setSize(237, 153);
		listChat = new JList(modelListChat);	
		
		// Pour afficher le rendering d'une ligneChat
		listChat.setCellRenderer(new LigneMessageRendered());

		
		listChat.setBounds(0, 0, 200, 200);
		jscrollPane.setViewportView(listChat);

		contentPane.add(jscrollPane, BorderLayout.CENTER);
		
		JPanel panel = new JPanel();
		contentPane.add(panel, BorderLayout.SOUTH);
		panel.setLayout(new BorderLayout(0, 0));
		
		textArea = new JTextArea();
		panel.add(textArea);
		textArea.setText("Ecrivez votre message");
		
		
		// Bouton envoyer
		JButton btnNewButton = new JButton("Envoyer");
		panel.add(btnNewButton, BorderLayout.EAST);
		
		// clic sur bouton envoyer
		btnNewButton.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent arg0) {
				
				HashMap<String, Object> event = new HashMap<String, Object>();
				event.put("Event", "ClicEnvoyerChat");
				event.put("message",textArea.getText());
				event.put ("chatID", id);
				vue.getControleur().considererEvent(event);
			}
		});
	}
	
	/**
	 * Methode permettant la mise a jour de la liste des messages, contenu dans le chat .
	 * @param linkedList Liste des differents messages.
	 */
	public void setListeMessages(LinkedList<Message> linkedList)
	{
		messages = linkedList;
		majListChats();
	}
	
	/**
	 * Methode permettant de rendre nulle le texte d'envoi du message. 
	 */
	public void remiseAZero()
	{
		this.textArea.setText("");
	}
	
	/**
	 * Methode permettant de mettre en premier plan l'espace d'envoi de message.  
	 */
	public void setFocusJText()
	{
		this.textArea.requestFocusInWindow();
	}
	
	/**
	 * Methode permettant la remise a zero de la liste des messages.  
	 */
	public void remiseAZeroJlist()
	{
		for(int i =0;i<messages.size();i++)
		{
			modelListChat.removeAllElements();
		}
	}
	
	
	/**
	 *  Methode permettant de faire le lien entre le model et la vue. 
	 *  La methode affiche les differents messages dans la vue. 
	 */
	public void majListChats()
	{	
			for(int i =0;i<messages.size();i++)
			{
				modelListChat.addElement(messages.get(i));
			}
	}
	
	/**
	 * Ajoute un message a la vue.
	 * @param m Message a afficher.
	 */
	public void AddMessage(Message m)
	{
		messages.add(m);
		modelListChat.addElement(m);
	}
	
	/**
	 * Mise a jour des utilisateurs connectes 
	 * @param nb Nombre d'utilisateurs connectees
	 */
	public void setNbUtilisateurConnecte(int nb)
	{
		nbUtilisateurConnectee.setText(""+nb);
	}
	
	/**
	 * Methode permettant la mise a jour de la liste des utilisateurs connectes au chat
	 * @param userID Identifiant de l'utilisateur
	 * @param nom Nom de l'utilisateur
	 */
	public void addUserVueUser(int userID, String nom)
	{
		modelListUsers.addElement(new LigneUser(userID, nom));
	}
	
	/**
	 * Methode permettant d'enlever un utilisateur a la liste d'utilisateur connecte 
	 * Methode permettant de gere la deconnection des utilisateurs. 
	 * @param userID Identifiant unique de l'utilisateur.
	 */
	public void removeUser(int userID)
	{
		Enumeration<LigneUser> e = modelListUsers.elements();
		
		while(e.hasMoreElements())
		{
			LigneUser cur = e.nextElement();
				
			if(cur.id==userID)
			{
				modelListUsers.removeElement(cur);
			}
		}
	}
	
	/**
	 * Methode permettant de charger entierement la liste des utilisateurs connectes.
	 * De plus la methode permet de gere l'affichage de la liste. 
	 * @param users Permettant de relier l'ensemble des utilisateurs connecte au serveur.
	 */
	public void majListUsers(HashMap<Integer,String> users)
	{	
			Iterator<Integer> i = users.keySet().iterator();
			
			while(i.hasNext())
			{
				int cur = i.next();
				System.out.println("id:"+cur);
				modelListUsers.addElement(new LigneUser(cur, users.get(cur)));
			}
	}
	
	/**
	 * Methode permettant de recuperer le gestionnaire de vue
	 * @return Gestionnaire de vue. 
	 */
	public Vue getVue()
	{
		return this.vue;
	}
	
}


/**
 * Classe gerant le rendering d'un message a afficher dans notre Jlist des messages
 * 
 * @author Antoine BRETON et Arnaud DUPEYRAT
 *
 */
class LigneMessageRendered implements ListCellRenderer {
	 private DefaultListCellRenderer defaultRenderer = new DefaultListCellRenderer();
	 
   @Override
   public Component getListCellRendererComponent(JList list, Object value, int index, boolean isSelected, boolean cellHasFocus) {
       Message m = (Message) value;
       
       return new VueMessage(m.getContenu(),m.getAuteur(), null, m.getSource());
   }
}
