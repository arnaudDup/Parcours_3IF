package Client.Vue;

import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Font;

import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.border.EmptyBorder;

public class VueMessage extends JPanel {

	private String auteur;
	private String contenu;
	private String date;
	
	
	public VueMessage(String contenu, String auteur, String date, boolean source)
	{
		super();
		setBorder(new EmptyBorder(5, 5, 5, 5));
		setLayout(new BorderLayout(0, 0));
		
		JPanel panel = new JPanel();
		add(panel, BorderLayout.NORTH);
		
		JLabel lblNewLabel_1 = new JLabel(auteur + ":");	
		JLabel lblNewLabel = new JLabel(contenu);
		lblNewLabel.setFont(new Font("Tahoma", Font.ITALIC, 11));
		
		// Ici nous gérons les deux affichages différements.
		if (source)
		{
			this.setBackground(Color.CYAN);
			lblNewLabel_1.setForeground(Color.BLACK);
			lblNewLabel_1.setBackground(Color.DARK_GRAY);
			lblNewLabel.setForeground(Color.BLACK);
			add(lblNewLabel_1, BorderLayout.NORTH);
			add(lblNewLabel, BorderLayout.SOUTH);	
		}
		
		else 
		{
			lblNewLabel_1.setForeground(Color.BLACK);
			lblNewLabel_1.setBackground(Color.LIGHT_GRAY);
			lblNewLabel.setForeground(Color.BLACK);
			add(lblNewLabel_1, BorderLayout.NORTH);
			add(lblNewLabel, BorderLayout.CENTER);
		}
	}
}
