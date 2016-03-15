package Client.Vue;

import java.awt.BorderLayout;
import java.awt.EventQueue;

import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.border.EmptyBorder;
import javax.swing.JLabel;
import javax.swing.JTextField;
import javax.swing.JButton;

import Client.ControleurReseau.Controleur;
import Common.Message;

import java.awt.event.ActionListener;
import java.awt.event.ActionEvent;

public class VueMessagePrive extends JFrame {

	private JPanel contentPane;
	private JTextField textField;
	private Controleur c;
	private Message m;
	private int userID;
	private JLabel lblPasDeMessage;
	
	private VueMessagePrive(int userIdDest, String nom, final Controleur c) {
		this.c = c;
		this.userID = userIdDest;
		
		// On ajoute la vue a la liste de vue du controleur
		
		this.setTitle("Message privé : "+nom);
		setBounds(100, 100, 413, 133);
		contentPane = new JPanel();
		contentPane.setBorder(new EmptyBorder(5, 5, 5, 5));
		contentPane.setLayout(new BorderLayout(0, 0));
		setContentPane(contentPane);
		
		JPanel panel = new JPanel();
		contentPane.add(panel, BorderLayout.SOUTH);
		panel.setLayout(new BorderLayout(0, 0));
		
		textField = new JTextField();
		panel.add(textField);
		textField.setColumns(10);
		
		JButton btnNewButton = new JButton("Envoyer");
		
		final VueMessagePrive hamecon = this;
		
		btnNewButton.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				String text = textField.getText();
				c.getControleurReseau().envoyerMessagePrive(userID, text);
				hamecon.setVisible(false);
				
			}
			
		});
		
		panel.add(btnNewButton, BorderLayout.EAST);
		lblPasDeMessage = new JLabel("Pas de message");
		contentPane.add(lblPasDeMessage, BorderLayout.CENTER);
		this.setVisible(true);
	}

	public static VueMessagePrive getInstance(int UserIdDest, String nom, Controleur c)
	{		
		VueMessagePrive vue = new VueMessagePrive(UserIdDest, nom, c);	
		c.addVueMessagePrive(vue,UserIdDest);
		return vue;
	}
		

	public void setMessage(Message msg) {
		lblPasDeMessage.setText(msg.getContenu());
	}

}
