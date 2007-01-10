//  © 2005 by Pedro Mendes, Virginia Tech Intellectual
// , Inc. and EML Research, gGmbH.
//  rights reserved.

package org.COPASI.gui;

import javax.swing.InputVerifier;
import javax.swing.JComponent;
import javax.swing.JTextField;

public class FloatVerifier extends InputVerifier {

	public boolean verify(JComponent arg0) {
		JTextField tf=(JTextField)arg0;
		String t=tf.getText();
		return t.matches("-?\\d+(\\.\\d+)?([eE]-?\\d+)?");
    }

}
