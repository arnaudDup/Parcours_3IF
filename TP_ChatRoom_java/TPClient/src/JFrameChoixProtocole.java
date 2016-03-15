import java.awt.BorderLayout;
import java.awt.EventQueue;

import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.border.EmptyBorder;
import javax.swing.JButton;

import java.awt.FlowLayout;
import java.awt.event.ActionListener;
import java.awt.event.ActionEvent;

import javax.swing.JTextField;
import javax.swing.JLabel;

import Client.ControleurReseau.Controleur;


public class JFrameChoixProtocole extends JFrame {

	private JPanel contentPane;


	/**
	 * Create the frame.
	 */
	public JFrameChoixProtocole() {
		setResizable(false);
		
		setBounds(100, 100, 441, 195);
		contentPane = new JPanel();
		contentPane.setBorder(new EmptyBorder(5, 5, 5, 5));
		setContentPane(contentPane);
		contentPane.setLayout(null);
		
		final JFrame tmp = this;
		JButton RMIButton = new JButton("Start RMI");
		RMIButton.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				Controleur controleur = new Controleur(true);
				controleur.getVue().afficherPage("Accueil");
				tmp.setVisible(false);
			}
		});
		RMIButton.setBounds(41, 10, 150, 125);
		contentPane.add(RMIButton);
		
		JButton SocketButton = new JButton("Start Sockets");
		SocketButton.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent arg0) {
				Controleur controleur = new Controleur(false);
				controleur.getVue().afficherPage("Accueil");
				tmp.setVisible(false);
			}
		});
		SocketButton.setBounds(237, 10, 150, 125);
		contentPane.add(SocketButton);
		
	}
}
