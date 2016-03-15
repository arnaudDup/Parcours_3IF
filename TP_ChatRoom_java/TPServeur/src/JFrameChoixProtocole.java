import java.awt.BorderLayout;
import java.awt.EventQueue;

import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.border.EmptyBorder;

import Serveur.ControleurServeur.ControleurSe;
import javax.swing.JButton;
import java.awt.FlowLayout;
import java.awt.event.ActionListener;
import java.awt.event.ActionEvent;
import javax.swing.JTextField;
import javax.swing.JLabel;

/**
 * Interface graphique, permettant de genere le choix entre les differents protocole de communication. 
 * 
 * @author Antoine BRETON et Arnaud DUPEYRAT
 * 
 */
public class JFrameChoixProtocole extends JFrame {

	private JPanel contentPane;
	private JTextField FileLogTF;


	/**
	 * Instancie un nouvel objet de classe 
	 */
	public JFrameChoixProtocole() {
		setResizable(false);
		
		setBounds(100, 100, 441, 271);
		contentPane = new JPanel();
		contentPane.setBorder(new EmptyBorder(5, 5, 5, 5));
		setContentPane(contentPane);
		contentPane.setLayout(null);
		final JFrame tmp = this;
		JButton RMIButton = new JButton("Start RMI");
		RMIButton.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				ControleurSe controleur = new ControleurSe(true,  FileLogTF.getText());
				tmp.setVisible(false);
			}
		});
		RMIButton.setBounds(41, 10, 150, 125);
		contentPane.add(RMIButton);
		
		JButton SocketButton = new JButton("Start Sockets");
		SocketButton.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent arg0) {
				ControleurSe controleur = new ControleurSe(false,  FileLogTF.getText());
				tmp.setVisible(false);
			}
		});
		SocketButton.setBounds(237, 10, 150, 125);
		contentPane.add(SocketButton);
		
		FileLogTF = new JTextField();
		FileLogTF.setBounds(173, 182, 86, 20);
		contentPane.add(FileLogTF);
		FileLogTF.setColumns(10);
		
		JLabel lblFichierDhistorique = new JLabel("Fichier d'historique");
		lblFichierDhistorique.setBounds(41, 185, 124, 14);
		contentPane.add(lblFichierDhistorique);
		
	}
}
