package org.COPASI.gui;

import javax.swing.InputVerifier;
import javax.swing.JComponent;
import javax.swing.JTextField;

public class IntegerVerifier extends InputVerifier {

	public boolean verify(JComponent arg0) {
		// TODO Auto-generated method stub
		JTextField tf=(JTextField)arg0;
		String t=tf.getText();
		return t.matches("-?\\d+");
    }

}
