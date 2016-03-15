package Client.Vue;

import java.awt.BorderLayout;
import java.awt.Component;
import java.awt.EventQueue;

import javax.swing.DefaultListCellRenderer;
import javax.swing.DefaultListModel;
import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.ListCellRenderer;
import javax.swing.border.EmptyBorder;
import javax.swing.JList;
import javax.swing.border.LineBorder;

import java.awt.Color;

import javax.swing.AbstractListModel;
import javax.swing.JLabel;
import javax.swing.JButton;

import java.awt.event.ActionListener;
import java.awt.event.ActionEvent;
import java.awt.event.MouseListener;
import java.util.ArrayList;
import java.util.Enumeration;
import java.util.HashMap;
import java.util.Iterator;

import javax.swing.JTextField;

import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;

public class VuePagePrincipale extends JFrame {

	private JPanel contentPane;
	private Vue vue;
	
	private JList listChat;
	private DefaultListModel modelListChat;
	
	private JScrollPane jScrollPane;
	private JLabel lblChatDisponibles;
	private JButton btnNewButton;
	private JTextField tfAjouterChat;
	private JLabel lblAjouerUnChat;

	private JButton btnSeConnecter;
	/**
	 * Launch the application.
	 */

	/**
	 * Create the frame.
	 */
	public VuePagePrincipale(final Vue vue) {
		super();
		setTitle("Chat");
		this.vue = vue;
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		setBounds(100, 100, 430, 273);
		
		// ContentPane
		contentPane = new JPanel();
		contentPane.setBorder(new EmptyBorder(5, 5, 5, 5));
		setContentPane(contentPane);
		contentPane.setLayout(null);
		
		// Liste --
		modelListChat = new DefaultListModel();
		jScrollPane = new JScrollPane();
		jScrollPane.setLocation(10, 26);
		jScrollPane.setSize(237, 153);
		listChat = new JList(modelListChat);	
		// Pour afficher le rendering d'une ligneChat
		listChat.setCellRenderer(new LigneChatRender());
		listChat.setBounds(0, 0, 200, 200);
		jScrollPane.setViewportView(listChat);
		contentPane.add(jScrollPane);
		
		// Label chat disponibles --
		lblChatDisponibles = new JLabel("Chat Disponibles:");
		lblChatDisponibles.setBounds(10, 11, 108, 14);
		contentPane.add(lblChatDisponibles);
		
		// TextFiel "ajouter chat" --
		tfAjouterChat = new JTextField();
		tfAjouterChat.setBounds(10, 203, 177, 22);
		contentPane.add(tfAjouterChat);
		tfAjouterChat.setColumns(10);
		
		// Bouton "ajouter chat" --
		btnNewButton = new JButton("+");
		
		// Clic listener bouton 
		btnNewButton.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent arg0) {
				
				// Lorsque l'on clic sur le bouton d'ajout de chat,
				
				// On crée un evenement clic chat
				HashMap<String, Object> event = new HashMap<String, Object>();
				event.put("Event", "ClicAjouterChat");
				event.put("nomChat", tfAjouterChat.getText());
				vue.getControleur().considererEvent(event);
			}
		});
		btnNewButton.setBounds(196, 203, 51, 23);
		contentPane.add(btnNewButton);
		

		lblAjouerUnChat = new JLabel("Ajouer un chat");
		lblAjouerUnChat.setBounds(10, 190, 108, 14);
		contentPane.add(lblAjouerUnChat);
		
		btnSeConnecter = new JButton("Se connecter");
		btnSeConnecter.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent arg0) {
				ligneChat c = (ligneChat) modelListChat.getElementAt(listChat.getSelectedIndex());
				
				HashMap<String, Object> event = new HashMap<String, Object>();
				event.put("Event", "ClicConnecterChat");
				event.put("chatID", c.id);
				vue.getControleur().considererEvent(event);
			}
		});
		btnSeConnecter.setBounds(257, 24, 123, 23);
		contentPane.add(btnSeConnecter);
	
	}
	
	public void setListChats(HashMap<Integer,String> chats)
	{
		Iterator<Integer> i = chats.keySet().iterator();		
		
		while(i.hasNext())
		{
			int Current = i.next();
			modelListChat.addElement(new ligneChat(Current,chats.get(Current)) );
		}
	}


	public void addChat(int chatid, String nom) {
		modelListChat.addElement( new ligneChat(chatid, nom) );
	}
	
	public String getChatNameByID(int chatid)
	{
		// On récupère la liste des chat du model
		Enumeration<ligneChat> e = modelListChat.elements();
		
		// Si on trouve le chat voulu on le retourne
		while (e.hasMoreElements())
		{
			ligneChat cur = e.nextElement();
			
			if(cur.id == chatid)
				return cur.nom;
		}
		
		return null;
	}

}

// Design Patern Adapter
class ligneChat
{
	public int id;
	public String nom;
	
	public ligneChat(int id, String nom)
	{
		this.id = id;
		this.nom = nom;
	}
}

class LigneChatRender implements ListCellRenderer {
	 private DefaultListCellRenderer defaultRenderer = new DefaultListCellRenderer();
	 
    @Override
    public Component getListCellRendererComponent(JList list, Object value, int index, boolean isSelected, boolean cellHasFocus) {
        ligneChat chat = (ligneChat) value;
        
        JLabel renderer =  (JLabel) defaultRenderer.getListCellRendererComponent(list, chat.nom, index,
                isSelected, cellHasFocus);

        return renderer;
    }
}
