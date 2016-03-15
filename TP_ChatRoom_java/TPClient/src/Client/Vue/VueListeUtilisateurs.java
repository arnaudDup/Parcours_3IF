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

public class VueListeUtilisateurs extends JFrame {

	private JPanel contentPane;
	private Vue vue;
	private JList listUsers;
	private JScrollPane jScrollPane;
	private JLabel lblChatDisponibles;

	private JButton btnSeConnecter;
	/**
	 * Launch the application.
	 */
	private VueChat vueChat;

	
	public VueListeUtilisateurs(final VueChat vueChat, DefaultListModel modelListUsers) {
		super();
		
		listUsers = new JList(modelListUsers);			
		this.vueChat = vueChat;
		setTitle("Chat");

		setBounds(100, 100, 430, 273);
		
		// ContentPane
		contentPane = new JPanel();
		contentPane.setBorder(new EmptyBorder(5, 5, 5, 5));
		setContentPane(contentPane);
		contentPane.setLayout(null);
		
		// Liste --
		
		jScrollPane = new JScrollPane();
		jScrollPane.setLocation(10, 26);
		jScrollPane.setSize(237, 153);
		
		// Pour afficher le rendering d'une ligneChat
		listUsers.setCellRenderer(new LigneUserRender());
		listUsers.setBounds(0, 0, 200, 200);
		jScrollPane.setViewportView(listUsers);
		contentPane.add(jScrollPane);
		
		// Label chat disponibles --
		lblChatDisponibles = new JLabel("Liste utilisateurs:");
		lblChatDisponibles.setBounds(10, 11, 108, 14);
		contentPane.add(lblChatDisponibles);
		
		btnSeConnecter = new JButton("Message Priv\u00E9");
		btnSeConnecter.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent arg0) {
	
				int indiceSelectedLigne = listUsers.getSelectedIndex();
				System.out.println(indiceSelectedLigne);
				
				// On teste le cas ou on a rien selectionner
				if(indiceSelectedLigne<0)
					return;
				
				int id = ((LigneUser)listUsers.getModel().getElementAt(indiceSelectedLigne)).id;
				String nom = ((LigneUser)listUsers.getModel().getElementAt(indiceSelectedLigne)).nom;
				System.out.println("idLigne"+id);
				VueMessagePrive.getInstance(id, nom, vueChat.getVue().getControleur());
			}
		});

		btnSeConnecter.setBounds(257, 24, 123, 23);
		contentPane.add(btnSeConnecter);
	
	}

}

// Design Patern Adapter
class LigneUser
{
	public int id;
	public String nom;
	
	public LigneUser(int id, String nom)
	{
		this.id = id;
		this.nom = nom;
	}
}

class LigneUserRender implements ListCellRenderer {
	 private DefaultListCellRenderer defaultRenderer = new DefaultListCellRenderer();
	 
    @Override
    public Component getListCellRendererComponent(JList list, Object value, int index, boolean isSelected, boolean cellHasFocus) {
        LigneUser user = (LigneUser) value;
        
        JLabel renderer =  (JLabel) defaultRenderer.getListCellRendererComponent(list, user.nom, index,
                isSelected, cellHasFocus);

        return renderer;
    }
}
