// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc., University of Heidelberg, and University of 
// of Connecticut School of Medicine. 
// All rights reserved. 

// Copyright (C) 2010 - 2016 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc., University of Heidelberg, and The University 
// of Manchester. 
// All rights reserved. 

// Copyright (C) 2008 - 2009 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc., EML Research, gGmbH, University of Heidelberg, 
// and The University of Manchester. 
// All rights reserved. 

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc. and EML Research, gGmbH. 
// All rights reserved. 





//  © 2005 by Pedro Mendes, Virginia Tech Intellectual
// , Inc. and EML Research, gGmbH.
//  rights reserved.

package org.COPASI.gui;

import javax.swing.BorderFactory;
import javax.swing.ImageIcon;
import javax.swing.JComboBox;
import javax.swing.JFileChooser;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.JButton;
import javax.swing.BoxLayout;
import javax.swing.JLabel;
import javax.swing.JCheckBox;
import javax.swing.Box;
import javax.swing.JSeparator;
import javax.swing.JTable;
import javax.swing.JFrame;
import javax.swing.ListSelectionModel;
import javax.swing.SwingConstants;
import javax.swing.JScrollPane;
import javax.swing.event.TableModelEvent;
import javax.swing.event.TableModelListener;
import javax.swing.table.DefaultTableModel;
import javax.swing.table.DefaultTableColumnModel;
import javax.swing.JOptionPane;
import java.awt.Color;
import java.awt.Container;
import java.awt.Window;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import java.util.Vector;
import java.util.Enumeration;

import org.COPASI.CRootContainer;
import org.COPASI.CDataModel;
import org.COPASI.CDataObject;
import org.COPASI.CCopasiTask;
import org.COPASI.CCopasiMethod;
import org.COPASI.CCopasiParameter;
import org.COPASI.CRegisteredCommonName;
import org.COPASI.CReport;
import org.COPASI.CReportDefinition;
import org.COPASI.COutputAssistant;
import org.COPASI.CCopasiMessage;
import org.COPASI.COPASIConstants;

/**
 * @author gauges
 * The class is the base class for all task widgets to come.
 * It consists of four elements that are put together with a horizontal box layout.
 * At the bottom there is a widget with some buttons to start and cancel the task as
 * well as buttons to call the output assistant once it is available.
 * Above the button widget there is a widget that allows the user to set method parameters.
 * This widget is hidden per default but can be displayed with a push button.
 * Next is a widget that is task specific and where the problem settings are handled.
 * And last but not least at the top there is a widget that displayes a title and has a 
 * few general task specific control elements.
 */
public class TaskWidget extends JPanel implements ActionListener, TableModelListener{
	
	
	/**
	 * 
	 */
	private static final long serialVersionUID = -389433829089422801L;

	public class MyTableModel extends DefaultTableModel {
		/**
		 * 
		 */
		private static final long serialVersionUID = -7232248508525153111L;

		public MyTableModel(int numRows,int numColumns)
		{
			super(numRows,numColumns);
		}
		
		public boolean isCellEditable(int row,int column)
		{
			return (column!=0);
		}
	}


	protected class TitleWidget extends JPanel
	{
		/**
		 * 
		 */
		private static final long serialVersionUID = 2367484356605694890L;
		protected JLabel mTitle;
		protected JCheckBox mUpdateModelBox;
		protected JCheckBox mExecutableBox;
		
		protected byte[] mCopasiIconData={
				 (byte)0x89,(byte)0x50,(byte)0x4e,(byte)0x47,(byte)0xd,(byte)0xa,(byte)0x1a,(byte)0xa,(byte)0x0,(byte)0x0,(byte)0x0,(byte)0xd,(byte)0x49,(byte)0x48,(byte)0x44,(byte)0x52,(byte)0x0,(byte)0x0,(byte)0x0,(byte)0x20
				,(byte)0x0,(byte)0x0,(byte)0x0,(byte)0x20,(byte)0x10,(byte)0x6,(byte)0x0,(byte)0x0,(byte)0x0,(byte)0x23,(byte)0xea,(byte)0xa6,(byte)0xb7,(byte)0x0,(byte)0x0,(byte)0x0,(byte)0x6,(byte)0x62,(byte)0x4b,(byte)0x47
				,(byte)0x44,(byte)0xff,(byte)0xff,(byte)0xff,(byte)0xff,(byte)0xff,(byte)0xff,(byte)0x9,(byte)0x58,(byte)0xf7,(byte)0xdc,(byte)0x0,(byte)0x0,(byte)0x0,(byte)0x9,(byte)0x70,(byte)0x48,(byte)0x59,(byte)0x73,(byte)0x0
				,(byte)0x0,(byte)0x0,(byte)0x48,(byte)0x0,(byte)0x0,(byte)0x0,(byte)0x48,(byte)0x0,(byte)0x46,(byte)0xc9,(byte)0x6b,(byte)0x3e,(byte)0x0,(byte)0x0,(byte)0xa,(byte)0xf2,(byte)0x49,(byte)0x44,(byte)0x41,(byte)0x54
				,(byte)0x68,(byte)0xde,(byte)0xed,(byte)0x98,(byte)0xd9,(byte)0x4f,(byte)0x9b,(byte)0xe9,(byte)0xf5,(byte)0xc7,(byte)0x3f,(byte)0xaf,(byte)0xb1,(byte)0x1,(byte)0xdb,(byte)0x80,(byte)0x8d,(byte)0x6d,(byte)0xb0,(byte)0x1d
				,(byte)0x9b,(byte)0x2d,(byte)0x80,(byte)0x3d,(byte)0x6,(byte)0x2,(byte)0x84,(byte)0x21,(byte)0xa4,(byte)0x93,(byte)0x7d,(byte)0x55,(byte)0x27,(byte)0x1d,(byte)0x4d,(byte)0xab,(byte)0x56,(byte)0xa9,(byte)0xd4,(byte)0x51
				,(byte)0xaf,(byte)0xab,(byte)0x4a,(byte)0x55,(byte)0x97,(byte)0x7f,(byte)0xa1,(byte)0xaa,(byte)0x7a,(byte)0xdf,(byte)0x8b,(byte)0x5e,(byte)0xb4,(byte)0x55,(byte)0x35,(byte)0x89,(byte)0x7a,(byte)0x31,(byte)0x55,(byte)0x47
				,(byte)0x9d,(byte)0xad,(byte)0x64,(byte)0x1a,(byte)0x29,(byte)0x34,(byte)0x1d,(byte)0x86,(byte)0x30,(byte)0x81,(byte)0x90,(byte)0xb2,(byte)0x99,(byte)0x24,(byte)0x10,(byte)0x1c,(byte)0x8c,(byte)0x17,(byte)0x86,(byte)0xc5
				,(byte)0xc6,(byte)0x60,(byte)0x36,(byte)0x6f,(byte)0x78,(byte)0x79,(byte)0x7e,(byte)0x17,(byte)0x8f,(byte)0xf8,(byte)0x25,(byte)0xd3,(byte)0xd1,(byte)0x4c,(byte)0xb3,(byte)0xcc,(byte)0x56,(byte)0x75,(byte)0xce,(byte)0x8d
				,(byte)0xfd,(byte)0xfa,(byte)0x7d,(byte)0xfd,(byte)0x3e,(byte)0xe7,(byte)0x7b,(byte)0xce,(byte)0xf7,(byte)0xac,(byte)0xf0,(byte)0xb5,(byte)0xfc,(byte)0x6f,(byte)0x8b,(byte)0xf2,(byte)0x65,(byte)0x2b,(byte)0xf0,(byte)0xef
				,(byte)0x12,(byte)0x8f,(byte)0xc7,(byte)0xe3,(byte)0x53,(byte)0x53,(byte)0x42,(byte)0x6c,(byte)0x6d,(byte)0x6d,(byte)0x6d,(byte)0xad,(byte)0xae,(byte)0xc2,(byte)0xf6,(byte)0xf6,(byte)0xf6,(byte)0x76,(byte)0x3c,(byte)0xe
				,(byte)0x85,(byte)0x42,(byte)0xa1,(byte)0x90,(byte)0xcf,(byte)0x3f,(byte)0x7c,(byte)0xae,(byte)0xb4,(byte)0xb4,(byte)0xb4,(byte)0xb4,(byte)0xac,(byte)0xc,(byte)0xaa,(byte)0xaa,(byte)0xaa,(byte)0xaa,(byte)0xea,(byte)0xeb
				,(byte)0xa1,(byte)0xb2,(byte)0xb2,(byte)0xb2,(byte)0xb2,(byte)0xb5,(byte)0x55,(byte)0x79,(byte)0x62,(byte)0x3c,(byte)0x5f,(byte)0xba,(byte)0x1,(byte)0x26,(byte)0x26,(byte)0x26,(byte)0x26,(byte)0x5e,(byte)0x7d,(byte)0x55
				,(byte)0x88,(byte)0x8d,(byte)0x8d,(byte)0x8d,(byte)0x8d,(byte)0x68,(byte)0x14,(byte)0x92,(byte)0xc9,(byte)0x64,(byte)0x52,(byte)0x8,(byte)0x78,(byte)0xf0,(byte)0xe0,(byte)0xc1,(byte)0x83,(byte)0xad,(byte)0x2d,(byte)0x58
				,(byte)0x58,(byte)0x58,(byte)0x58,(byte)0x48,(byte)0xa7,(byte)0xe5,(byte)0xb3,(byte)0xf9,(byte)0x3c,(byte)0x94,(byte)0x94,(byte)0x94,(byte)0x94,(byte)0x14,(byte)0xa,(byte)0x50,(byte)0x5d,(byte)0x5d,(byte)0x5d,(byte)0xad
				,(byte)0xd3,(byte)0xc1,(byte)0xa9,(byte)0x53,(byte)0xa7,(byte)0x4e,(byte)0x1d,(byte)0x38,(byte)0x0,(byte)0x8d,(byte)0x8d,(byte)0x8d,(byte)0x8d,(byte)0xdf,(byte)0xf8,(byte)0x6,(byte)0x94,(byte)0x97,(byte)0x97,(byte)0x97
				,(byte)0xbb,(byte)0x5c,(byte)0x8f,(byte)0x6f,(byte)0x8,(byte)0xf5,(byte)0x17,(byte)0xd,(byte)0x78,(byte)0x78,(byte)0x78,(byte)0x78,(byte)0xf8,(byte)0x77,(byte)0xbf,(byte)0x13,(byte)0x62,(byte)0x7a,(byte)0x7a,(byte)0x7a
				,(byte)0x3a,(byte)0x10,(byte)0x80,(byte)0xcb,(byte)0x97,(byte)0x2f,(byte)0x5f,(byte)0xf6,(byte)0x7a,(byte)0x25,(byte)0x60,(byte)0x95,(byte)0xa,(byte)0xb2,(byte)0xd9,(byte)0x6c,(byte)0x36,(byte)0x9f,(byte)0x87,(byte)0x5c
				,(byte)0x2e,(byte)0x97,(byte)0xcb,(byte)0xe7,(byte)0x41,(byte)0x8,(byte)0x21,(byte)0x84,(byte)0x80,(byte)0x9a,(byte)0x9a,(byte)0x9a,(byte)0x1a,(byte)0x21,(byte)0xc0,(byte)0x6e,(byte)0xb7,(byte)0xdb,(byte)0x55,(byte)0x2a
				,(byte)0x48,(byte)0xa5,(byte)0xd2,(byte)0xe9,(byte)0x4c,(byte)0x6,(byte)0xa2,(byte)0xd1,(byte)0xd5,(byte)0xd5,(byte)0xe5,(byte)0x65,(byte)0xb0,(byte)0xdb,(byte)0x1d,(byte)0x8e,(byte)0xf5,(byte)0xf5,(byte)0x27,(byte)0xd7
				,(byte)0xe7,(byte)0x73,(byte)0x67,(byte)0xc0,(byte)0xc4,(byte)0xc4,(byte)0xc4,(byte)0xc4,(byte)0x9f,(byte)0xfe,(byte)0x24,(byte)0x84,(byte)0xcf,(byte)0xe7,(byte)0xf3,(byte)0xcd,(byte)0xcd,(byte)0xc1,(byte)0xc8,(byte)0xc8
				,(byte)0xc8,(byte)0xc8,(byte)0xd6,(byte)0x16,(byte)0xf8,(byte)0x7c,(byte)0x3e,(byte)0x5f,(byte)0x2e,(byte)0x27,(byte)0x29,(byte)0xaf,(byte)0x28,(byte)0xd2,(byte)0xb3,(byte)0x45,(byte)0x45,(byte)0x50,(byte)0x5f,(byte)0x5f
				,(byte)0x5f,(byte)0x2f,(byte)0x84,(byte)0xf4,(byte)0x68,(byte)0x3e,(byte)0xf,(byte)0xc5,(byte)0xc5,(byte)0xc5,(byte)0xc5,(byte)0xc9,(byte)0xa4,(byte)0xbc,(byte)0xde,(byte)0xb7,(byte)0xf,(byte)0x6a,(byte)0x6b,(byte)0x6b
				,(byte)0x6b,(byte)0x5d,(byte)0x2e,(byte)0x19,(byte)0x2,(byte)0x5a,(byte)0x2d,(byte)0x68,(byte)0x34,(byte)0xc5,(byte)0xc5,(byte)0x1a,(byte)0xd,(byte)0xb8,(byte)0xdd,(byte)0x2e,(byte)0xd7,(byte)0x77,(byte)0xbf,(byte)0xfb
				,(byte)0x15,(byte)0x8,(byte)0x81,(byte)0x50,(byte)0x28,(byte)0x14,(byte)0xba,(byte)0x76,(byte)0x4d,(byte)0x8,(byte)0xbf,(byte)0xdf,(byte)0xef,(byte)0xf7,(byte)0xfb,(byte)0xa1,(byte)0xaf,(byte)0xaf,(byte)0xaf,(byte)0x2f
				,(byte)0x1c,(byte)0x86,(byte)0xdb,(byte)0xb7,(byte)0x6f,(byte)0xdf,(byte)0xce,(byte)0x64,(byte)0x60,(byte)0x63,(byte)0x63,(byte)0x63,(byte)0xa3,(byte)0x50,(byte)0x80,(byte)0xa6,(byte)0xa6,(byte)0xa6,(byte)0x26,(byte)0x21
				,(byte)0xe0,(byte)0xd0,(byte)0xa1,(byte)0x43,(byte)0x87,(byte)0x74,(byte)0x3a,(byte)0x68,(byte)0x6b,(byte)0x6b,(byte)0x6b,(byte)0xab,(byte)0xac,(byte)0x94,(byte)0x31,(byte)0x6d,(byte)0xb1,(byte)0xc8,(byte)0x98,(byte)0x6e
				,(byte)0x68,(byte)0x90,(byte)0xc0,(byte)0xcf,(byte)0x9c,(byte)0x79,(byte)0x72,(byte)0x60,(byte)0x5f,(byte)0x98,(byte)0x1,(byte)0xa2,(byte)0xd1,(byte)0x68,(byte)0x74,(byte)0x62,(byte)0x42,(byte)0x88,(byte)0x60,(byte)0x30
				,(byte)0x18,(byte)0x9c,(byte)0x9c,(byte)0x84,(byte)0xa9,(byte)0xa9,(byte)0xa9,(byte)0xa9,(byte)0x40,(byte)0x40,(byte)0x2,(byte)0xde,(byte)0xde,(byte)0x86,(byte)0xb1,(byte)0xb1,(byte)0xb1,(byte)0x31,(byte)0x21,(byte)0x40
				,(byte)0xa5,(byte)0x52,(byte)0xa9,(byte)0x14,(byte)0x5,(byte)0x3a,(byte)0x3b,(byte)0x3b,(byte)0x3b,(byte)0x4b,(byte)0x4a,(byte)0xe0,(byte)0xc2,(byte)0x85,(byte)0xb,(byte)0x17,(byte)0xec,(byte)0x76,(byte)0xe8,(byte)0xe8
				,(byte)0xe8,(byte)0xe8,(byte)0x70,(byte)0xbb,(byte)0xc1,(byte)0x62,(byte)0xb1,(byte)0x58,(byte)0x1c,(byte)0xe,(byte)0x30,(byte)0x18,(byte)0xc,(byte)0x86,(byte)0x3,(byte)0x7,(byte)0x3e,(byte)0x3f,(byte)0xc0,(byte)0x9f
				,(byte)0x99,(byte)0x1,(byte)0x16,(byte)0x17,(byte)0x17,(byte)0x17,(byte)0x87,(byte)0x87,(byte)0x85,(byte)0x18,(byte)0x1b,(byte)0x1b,(byte)0x1b,(byte)0x9b,(byte)0x9a,(byte)0x82,(byte)0x2b,(byte)0x57,(byte)0xae,(byte)0x5c
				,(byte)0x9,(byte)0x6,(byte)0x25,(byte)0xe5,(byte)0x33,(byte)0x19,(byte)0xc8,(byte)0x64,(byte)0x32,(byte)0x99,(byte)0x7c,(byte)0x1e,(byte)0x1a,(byte)0x1a,(byte)0x1a,(byte)0x1a,(byte)0x54,(byte)0x2a,(byte)0x38,(byte)0x7f
				,(byte)0xfe,(byte)0xfc,(byte)0xf9,(byte)0xb2,(byte)0x32,(byte)0xe8,(byte)0xe9,(byte)0xe9,(byte)0xe9,(byte)0xa9,(byte)0xaf,(byte)0x97,(byte)0xbf,(byte)0x77,(byte)0x74,(byte)0xc8,(byte)0x64,(byte)0xd6,(byte)0xdd,(byte)0xfd
				,(byte)0xc5,(byte)0x1,(byte)0x7e,(byte)0x66,(byte)0x3,(byte)0x4c,(byte)0x4e,(byte)0x7a,(byte)0xbd,(byte)0xaf,(byte)0xbd,(byte)0x26,(byte)0xc4,(byte)0xdc,(byte)0xdc,(byte)0x83,(byte)0x7,(byte)0x4b,(byte)0x4b,(byte)0xd0
				,(byte)0xdb,(byte)0xdb,(byte)0xdb,(byte)0x1b,(byte)0x8d,(byte)0xc2,(byte)0xe8,(byte)0xe8,(byte)0xe8,(byte)0xe8,(byte)0x5e,(byte)0x96,(byte)0x6,(byte)0x38,(byte)0x7c,(byte)0xf8,(byte)0xf0,(byte)0xe1,(byte)0x7c,(byte)0x1e
				,(byte)0x5e,(byte)0x78,(byte)0xe1,(byte)0x85,(byte)0x17,(byte)0xca,(byte)0xca,(byte)0x24,(byte)0xd5,(byte)0x3b,(byte)0x3b,(byte)0xa1,(byte)0xa5,(byte)0xa5,(byte)0xa5,(byte)0xe5,(byte)0xfb,(byte)0xdf,(byte)0xff,(byte)0xf2
				,(byte)0x0,(byte)0x3f,(byte)0xb5,(byte)0x1,(byte)0xde,(byte)0x7b,(byte)0xaf,(byte)0xbf,(byte)0xff,(byte)0xf2,(byte)0x65,(byte)0x21,(byte)0xfa,(byte)0xfa,(byte)0xfa,(byte)0xfa,(byte)0xfc,(byte)0x7e,(byte)0x99,(byte)0xcc
				,(byte)0x92,(byte)0x49,(byte)0x58,(byte)0x5b,(byte)0x8b,(byte)0xc5,(byte)0x84,(byte)0x80,(byte)0xfd,(byte)0xfb,(byte)0xf7,(byte)0xef,(byte)0x17,(byte)0x2,(byte)0x8e,(byte)0x1e,(byte)0x3d,(byte)0x7a,(byte)0xd4,(byte)0x68
				,(byte)0x84,(byte)0xee,(byte)0xee,(byte)0xee,(byte)0x6e,(byte)0xbb,(byte)0x1d,(byte)0x4e,(byte)0x9f,(byte)0x3e,(byte)0x7d,(byte)0xfa,(byte)0xc7,(byte)0x3f,(byte)0xfe,(byte)0xea,(byte)0x0,(byte)0x7e,(byte)0x62,(byte)0x3
				,(byte)0xf4,(byte)0xf7,(byte)0xf,(byte)0xc,(byte)0x5c,(byte)0xba,(byte)0x24,(byte)0xc4,(byte)0x7b,(byte)0xef,(byte)0xf5,(byte)0xf7,(byte)0x7,(byte)0x83,(byte)0x70,(byte)0xfd,(byte)0xfa,(byte)0xb5,(byte)0x6b,(byte)0x3b
				,(byte)0x3b,(byte)0xb2,(byte)0x4c,(byte)0x9,(byte)0x21,(byte)0x93,(byte)0x57,(byte)0x51,(byte)0x11,(byte)0x9c,(byte)0x3d,(byte)0x7b,(byte)0xf6,(byte)0x6c,(byte)0x65,(byte)0x25,(byte)0x74,(byte)0x75,(byte)0x75,(byte)0x75
				,(byte)0xb5,(byte)0xb4,(byte)0x48,(byte)0x4f,(byte)0x3f,(byte)0x4d,(byte)0x56,(byte)0xfe,(byte)0xca,(byte)0x18,(byte)0x60,(byte)0x60,(byte)0x40,(byte)0x2,(byte)0xbf,(byte)0x72,(byte)0xe5,(byte)0xca,(byte)0x15,(byte)0xbf
				,(byte)0x1f,(byte)0x86,(byte)0x86,(byte)0x86,(byte)0x86,(byte)0x52,(byte)0x29,(byte)0x30,(byte)0x9b,(byte)0xcd,(byte)0x66,(byte)0x90,(byte)0x31,(byte)0xad,(byte)0xd3,(byte)0xc9,(byte)0x24,(byte)0x56,(byte)0x5d,(byte)0xd
				,(byte)0x27,(byte)0x4f,(byte)0x9e,(byte)0x3c,(byte)0xf9,(byte)0xf3,(byte)0x9f,(byte)0x7f,(byte)0xfe,(byte)0x80,(byte)0x37,(byte)0x37,(byte)0x3f,(byte)0xfc,(byte)0xf0,(byte)0x9d,(byte)0x77,(byte)0x84,(byte)0xc8,(byte)0x64
				,(byte)0xb6,(byte)0xb7,(byte)0xd7,(byte)0xd6,(byte)0xa0,(byte)0x50,(byte)0xd8,(byte)0xdd,(byte)0x4d,(byte)0x26,(byte)0x1f,(byte)0xde,(byte)0x57,(byte)0xa9,(byte)0x8a,(byte)0x8b,(byte)0x75,(byte)0x3a,(byte)0x28,(byte)0x29
				,(byte)0x29,(byte)0x2f,(byte)0xaf,(byte)0xaa,(byte)0x2,(byte)0x83,(byte)0xc1,(byte)0xe9,(byte)0xfc,(byte)0xf6,(byte)0xb7,(byte)0x3f,(byte)0x59,(byte)0xaf,(byte)0x8f,(byte)0xdd,(byte)0xe8,(byte)0xef,(byte)0xef,(byte)0xef
				,(byte)0xbf,(byte)0x74,(byte)0x49,(byte)0x88,(byte)0xfe,(byte)0xfe,(byte)0x3d,(byte)0x8f,(byte)0x5f,(byte)0xbf,(byte)0xbe,(byte)0xb3,(byte)0x3,(byte)0x7a,(byte)0xbd,(byte)0x5e,(byte)0x5f,(byte)0x54,(byte)0x4,(byte)0x17
				,(byte)0x2f,(byte)0x5e,(byte)0xbc,(byte)0x58,(byte)0x55,(byte)0x5,(byte)0xc7,(byte)0x8e,(byte)0x1d,(byte)0x3b,(byte)0xd6,(byte)0xd4,(byte)0x4,(byte)0xad,(byte)0xad,(byte)0xad,(byte)0xad,(byte)0xdf,(byte)0xfb,(byte)0xde
				,(byte)0x67,(byte)0xf,(byte)0x7c,(byte)0x65,(byte)0xe5,(byte)0xce,(byte)0x9d,(byte)0x5f,(byte)0xfc,(byte)0x42,(byte)0x88,(byte)0x42,(byte)0xa1,(byte)0x50,(byte)0xa8,(byte)0xaa,(byte)0x82,(byte)0xed,(byte)0xed,(byte)0x95
				,(byte)0x95,(byte)0x70,(byte)0x18,(byte)0xd6,(byte)0xd7,(byte)0x43,(byte)0xa1,(byte)0x48,(byte)0x4,(byte)0x22,(byte)0x11,(byte)0x9f,(byte)0x6f,(byte)0x65,(byte)0x5,(byte)0x76,(byte)0x77,(byte)0x13,(byte)0x89,(byte)0xbd
				,(byte)0x4e,(byte)0x11,(byte)0xa0,(byte)0xb4,(byte)0x54,(byte)0xaf,(byte)0x2f,(byte)0x29,(byte)0x1,(byte)0x9b,(byte)0xcd,(byte)0xe3,(byte)0x71,(byte)0x3a,(byte)0xc1,(byte)0x6a,(byte)0x6d,(byte)0x6d,(byte)0xed,(byte)0xe8
				,(byte)0x80,(byte)0x8a,(byte)0xa,(byte)0x87,(byte)0xe3,(byte)0xd0,(byte)0x21,(byte)0xa8,(byte)0xac,(byte)0xac,(byte)0xa9,(byte)0xf9,(byte)0xd6,(byte)0xb7,(byte)0x1e,(byte)0xea,(byte)0xfb,(byte)0xff,(byte)0x5f,(byte)0x6e
				,(byte)0xdc,(byte)0xb8,(byte)0x71,(byte)0xe3,(byte)0xd2,(byte)0x25,(byte)0x21,(byte)0x7a,(byte)0x7b,(byte)0x7b,(byte)0x7b,(byte)0xfd,(byte)0x7e,(byte)0xb8,(byte)0x79,(byte)0xf3,(byte)0xe6,(byte)0xcd,(byte)0x74,(byte)0x5a
				,(byte)0x96,(byte)0x27,(byte)0x80,(byte)0x97,(byte)0x5e,(byte)0x7a,(byte)0xe9,(byte)0x25,(byte)0xab,(byte)0x55,(byte)0xc6,(byte)0xf4,(byte)0xc1,(byte)0x83,(byte)0xe0,(byte)0x76,(byte)0xbb,(byte)0xdd,(byte)0xe7,(byte)0xcf
				,(byte)0x3f,(byte)0x3b,(byte)0xf0,(byte)0x64,(byte)0x72,(byte)0x73,(byte)0xd3,(byte)0xeb,(byte)0x15,(byte)0x22,(byte)0x91,(byte)0x88,(byte)0x46,(byte)0xef,(byte)0xdd,(byte)0x83,(byte)0xd5,(byte)0xd5,(byte)0x99,(byte)0x99
				,(byte)0xbf,(byte)0xff,(byte)0x1d,(byte)0xd6,(byte)0xd6,(byte)0xfc,(byte)0xfe,(byte)0xd9,(byte)0x59,(byte)0x58,(byte)0x59,(byte)0x99,(byte)0x9b,(byte)0xdb,(byte)0xdd,(byte)0x85,(byte)0x70,(byte)0x78,(byte)0x66,(byte)0x26
				,(byte)0x93,(byte)0x81,(byte)0x95,(byte)0x95,(byte)0x48,(byte)0x44,(byte)0x51,(byte)0x20,(byte)0x12,(byte)0x89,(byte)0xc7,(byte)0x4b,(byte)0x4b,(byte)0x21,(byte)0x93,(byte)0xc9,(byte)0xe5,(byte)0x8a,(byte)0x8a,(byte)0x40
				,(byte)0xa5,(byte)0x82,(byte)0x42,(byte)0x1,(byte)0xc,(byte)0x6,(byte)0xb5,(byte)0x3a,(byte)0x91,(byte)0x80,(byte)0x9a,(byte)0x1a,(byte)0xab,(byte)0x35,(byte)0x9d,(byte)0x86,(byte)0xfd,(byte)0xfb,(byte)0xdb,(byte)0xda
				,(byte)0xb4,(byte)0x5a,(byte)0x68,(byte)0x6a,(byte)0x92,(byte)0xe,(byte)0xab,(byte)0xab,(byte)0x3b,(byte)0x75,(byte)0xea,(byte)0xc5,(byte)0x17,(byte)0xa1,(byte)0xba,(byte)0xda,(byte)0xed,(byte)0xfe,(byte)0xd9,(byte)0xcf
				,(byte)0x14,(byte)0x45,(byte)0xed,(byte)0xf3,(byte)0xf9,(byte)0x7c,(byte)0xef,(byte)0xbc,(byte)0x23,(byte)0x81,(byte)0x4f,(byte)0x4e,(byte)0xc2,(byte)0xe0,(byte)0xe0,(byte)0xe0,(byte)0x60,(byte)0x32,(byte)0x9,(byte)0x5a
				,(byte)0xad,(byte)0x56,(byte)0xfb,(byte)0x28,(byte)0xf0,(byte)0x13,(byte)0x27,(byte)0x4e,(byte)0x9c,(byte)0x78,(byte)0xee,(byte)0xb9,(byte)0xcf,(byte)0xe,(byte)0x78,(byte)0x2c,(byte)0xe6,(byte)0xf3,(byte)0xfd,(byte)0xf9
				,(byte)0xcf,(byte)0x42,(byte)0x2c,(byte)0x2c,(byte)0x8c,(byte)0x8e,(byte)0xbe,(byte)0xfe,(byte)0x3a,(byte)0x84,(byte)0x42,(byte)0x63,(byte)0x63,(byte)0x5e,(byte)0x2f,(byte)0xf8,(byte)0xfd,(byte)0xb7,(byte)0x6e,(byte)0x5
				,(byte)0x2,(byte)0xb0,(byte)0xb8,(byte)0xe8,(byte)0xf7,(byte)0xa7,(byte)0xd3,(byte)0xb0,(byte)0xb6,(byte)0x96,(byte)0x4c,(byte)0x6a,(byte)0xb5,(byte)0xb0,(byte)0xb6,(byte)0x96,(byte)0xcb,(byte)0x55,(byte)0x57,(byte)0x83
				,(byte)0xa2,(byte)0x18,(byte)0x8d,(byte)0x46,(byte)0x23,(byte)0x24,(byte)0x93,(byte)0x35,(byte)0x35,(byte)0x46,(byte)0x23,(byte)0xe4,(byte)0x72,(byte)0xa0,(byte)0x56,(byte)0x3f,(byte)0x34,(byte)0x80,(byte)0x10,(byte)0xb0
				,(byte)0xbd,(byte)0xd,(byte)0x45,(byte)0x45,(byte)0xd9,(byte)0xec,(byte)0xd2,(byte)0x12,(byte)0xa4,(byte)0x52,(byte)0x23,(byte)0x23,(byte)0xe1,(byte)0x30,(byte)0x24,(byte)0x12,(byte)0xb1,(byte)0x98,(byte)0xd7,(byte)0xb
				,(byte)0x65,(byte)0x65,(byte)0xe,(byte)0x87,(byte)0xd3,(byte)0x9,(byte)0x89,(byte)0xc4,(byte)0xfa,(byte)0xfa,(byte)0xf0,(byte)0xb0,(byte)0x10,(byte)0x6a,(byte)0x9f,(byte)0xcf,(byte)0xe7,(byte)0x1b,(byte)0x1a,(byte)0x7a
				,(byte)0x98,(byte)0xd5,(byte)0x73,(byte)0xb9,(byte)0x5c,(byte)0x4e,(byte)0x51,(byte)0xe0,(byte)0xcc,(byte)0x99,(byte)0x33,(byte)0x67,(byte)0x34,(byte)0x1a,(byte)0x38,(byte)0x72,(byte)0xe4,(byte)0xc8,(byte)0x91,(byte)0xbd
				,(byte)0xa4,(byte)0xf6,(byte)0x69,(byte)0xb1,(byte)0xf4,(byte)0x9f,(byte)0x24,(byte)0x1a,(byte)0x9d,(byte)0x99,(byte)0x79,(byte)0xf5,(byte)0x55,(byte)0x21,(byte)0xa2,(byte)0x51,(byte)0x9f,(byte)0xef,(byte)0xc6,(byte)0xd
				,(byte)0xf8,(byte)0xd7,(byte)0xbf,(byte)0x5e,(byte)0x7f,(byte)0xfd,(byte)0xf7,(byte)0xbf,(byte)0x87,(byte)0xf1,(byte)0xf1,(byte)0xf,(byte)0x3e,(byte)0x48,(byte)0xa5,(byte)0x60,(byte)0x6e,(byte)0x2e,(byte)0x10,(byte)0x28
				,(byte)0x2a,(byte)0x82,(byte)0x78,(byte)0x3c,(byte)0x93,(byte)0xb1,(byte)0x5a,(byte)0x41,(byte)0x51,(byte)0xcc,(byte)0xe6,(byte)0x8a,(byte)0xa,(byte)0xa8,(byte)0xad,(byte)0x3d,(byte)0x7c,(byte)0x58,(byte)0xaf,(byte)0x87
				,(byte)0xce,(byte)0xce,(byte)0xba,(byte)0x3a,(byte)0xa3,(byte)0x11,(byte)0xda,(byte)0xda,(byte)0xba,(byte)0xba,(byte)0x8c,(byte)0x46,(byte)0xd0,(byte)0x6a,(byte)0x75,(byte)0x3a,(byte)0x0,(byte)0x21,(byte)0x54,(byte)0x2a
				,(byte)0x21,(byte)0xe4,(byte)0x19,(byte)0x42,(byte)0x40,(byte)0x51,(byte)0x51,(byte)0xa1,(byte)0x60,(byte)0xb3,(byte)0x41,(byte)0x32,(byte)0xb9,(byte)0xb6,(byte)0xe6,(byte)0x74,(byte)0xc2,(byte)0xf8,(byte)0xf8,(byte)0x5b
				,(byte)0x6f,(byte)0xa9,(byte)0xd5,(byte)0xf0,(byte)0xe0,(byte)0xc1,(byte)0xf4,(byte)0xf4,(byte)0xe2,(byte)0x22,(byte)0x54,(byte)0x55,(byte)0xbd,(byte)0xff,(byte)0xfe,(byte)0xe4,(byte)0x24,(byte)0x18,(byte)0xc,(byte)0x35
				,(byte)0x35,(byte)0x43,(byte)0x43,(byte)0xa0,(byte)0x9e,(byte)0x9d,(byte)0x9d,(byte)0x9d,(byte)0xf5,(byte)0x7a,(byte)0x21,(byte)0x1c,(byte)0xe,(byte)0x87,(byte)0xeb,(byte)0xea,(byte)0xc0,(byte)0xe9,(byte)0x74,(byte)0x3a
				,(byte)0x8b,(byte)0x8b,(byte)0x65,(byte)0x6c,(byte)0x57,(byte)0x54,(byte)0x40,(byte)0x7b,(byte)0x7b,(byte)0x7b,(byte)0xfb,(byte)0xb3,(byte)0x0,(byte)0xf,(byte)0x6,(byte)0x7,(byte)0x6,(byte)0x7e,(byte)0xf5,(byte)0x2b
				,(byte)0x21,(byte)0xa6,(byte)0xa7,(byte)0xdf,(byte)0x7d,(byte)0xf7,(byte)0xed,(byte)0xb7,(byte)0x61,(byte)0x66,(byte)0x66,(byte)0x78,(byte)0x78,(byte)0x7e,(byte)0x1e,(byte)0x66,(byte)0x67,(byte)0x67,(byte)0x67,(byte)0x1
				,(byte)0xee,(byte)0xdf,(byte)0xdf,(byte)0xda,(byte)0xaa,(byte)0xad,(byte)0x85,(byte)0x5c,(byte)0xce,(byte)0x6c,(byte)0xae,(byte)0xaa,(byte)0x82,(byte)0xa6,(byte)0xa6,(byte)0x9e,(byte)0x9e,(byte)0xd2,(byte)0x52,(byte)0x68
				,(byte)0x6f,(byte)0xef,(byte)0xe9,(byte)0x31,(byte)0x18,(byte)0xa0,(byte)0xad,(byte)0xad,(byte)0xbd,(byte)0x5d,(byte)0xc6,(byte)0xb2,(byte)0xcd,(byte)0x56,(byte)0x5f,(byte)0xf,(byte)0x66,(byte)0xb3,(byte)0xc5,(byte)0xb2
				,(byte)0x6f,(byte)0x9f,(byte)0xc,(byte)0xcd,(byte)0x9e,(byte)0x9e,(byte)0x4f,(byte)0xd6,(byte)0x2b,(byte)0x18,(byte)0xf4,(byte)0xfb,(byte)0xaf,(byte)0x5d,(byte)0x13,(byte)0x22,(byte)0x10,(byte)0x8,(byte)0x4,(byte)0x36
				,(byte)0x37,(byte)0x61,(byte)0x7a,(byte)0xfa,(byte)0xde,(byte)0x3d,(byte)0x95,(byte)0xa,(byte)0xac,(byte)0xd6,(byte)0xc9,(byte)0xc9,(byte)0x85,(byte)0x5,(byte)0xa8,(byte)0xad,(byte)0xed,(byte)0xea,(byte)0x7a,(byte)0xfb
				,(byte)0x6d,(byte)0x50,(byte)0x27,(byte)0x93,(byte)0xc9,(byte)0x64,(byte)0x22,(byte)0xf1,(byte)0xb0,(byte)0xac,(byte)0x59,(byte)0xad,(byte)0x56,(byte)0x6b,(byte)0x51,(byte)0x11,(byte)0xd4,(byte)0xd5,(byte)0xd5,(byte)0xd5
				,(byte)0x35,(byte)0x34,(byte)0x3c,(byte)0x3d,(byte)0xc5,(byte)0xe7,(byte)0xe7,(byte)0xfb,(byte)0xfb,(byte)0x7f,(byte)0xf9,(byte)0x4b,(byte)0x21,(byte)0xee,(byte)0xdc,(byte)0xe9,(byte)0xed,(byte)0xed,(byte)0xeb,(byte)0x83
				,(byte)0xf1,(byte)0xf1,(byte)0x7f,(byte)0xfe,(byte)0x73,(byte)0x79,(byte)0x19,(byte)0xa6,(byte)0xa7,(byte)0xe3,(byte)0x71,(byte)0xab,(byte)0x15,(byte)0xd2,(byte)0x69,(byte)0xb3,(byte)0xd9,(byte)0x66,(byte)0x3,(byte)0xb7
				,(byte)0xfb,(byte)0xc5,(byte)0x17,(byte)0xab,(byte)0xaa,(byte)0x24,(byte)0x60,(byte)0x8b,(byte)0x5,(byte)0xda,(byte)0xda,(byte)0xe,(byte)0x1c,(byte)0xa8,(byte)0xab,(byte)0x83,(byte)0x7d,(byte)0xfb,(byte)0x1c,(byte)0xe
				,(byte)0x8f,(byte)0x47,(byte)0x4e,(byte)0x81,(byte)0xc7,(byte)0x8f,(byte)0x3f,(byte)0x8d,(byte)0x3,(byte)0x54,(byte)0x2a,(byte)0x9d,(byte)0xe,(byte)0xd2,(byte)0x69,(byte)0xd0,(byte)0x6a,(byte)0x61,(byte)0x63,(byte)0x23
				,(byte)0x97,(byte)0x2b,(byte)0x2f,(byte)0x87,(byte)0xad,(byte)0xad,(byte)0xf5,(byte)0xf5,(byte)0x5c,(byte)0x4e,(byte)0x32,(byte)0x24,(byte)0x14,(byte)0x2,(byte)0xf5,(byte)0xde,(byte)0xb8,(byte)0xa9,(byte)0x28,(byte)0x8a
				,(byte)0xa2,(byte)0x28,(byte)0xa0,(byte)0xd1,(byte)0x68,(byte)0x34,(byte)0x20,(byte)0xa7,(byte)0xb0,(byte)0xd2,(byte)0xd2,(byte)0x27,(byte)0x3f,(byte)0x36,(byte)0x1c,(byte)0x1e,(byte)0x1e,(byte)0xfe,(byte)0xf5,(byte)0xaf
				,(byte)0x85,(byte)0x98,(byte)0x99,(byte)0xb9,(byte)0x76,(byte)0x6d,(byte)0x60,(byte)0x0,(byte)0xc6,(byte)0xc6,(byte)0xfe,(byte)0xf1,(byte)0x8f,(byte)0xa5,(byte)0x25,(byte)0xf0,(byte)0xfb,(byte)0xb7,(byte)0xb6,(byte)0x2c
				,(byte)0x16,(byte)0xb0,(byte)0x58,(byte)0x7a,(byte)0x7a,(byte)0x1a,(byte)0x1a,(byte)0xa0,(byte)0xb5,(byte)0xf5,(byte)0xd8,(byte)0x31,(byte)0x9b,(byte)0xd,(byte)0x3a,(byte)0x3a,(byte)0x9e,(byte)0x7f,(byte)0x7e,(byte)0xff
				,(byte)0x7e,(byte)0xa8,(byte)0xad,(byte)0xad,(byte)0xab,(byte)0x6b,(byte)0x6a,(byte)0x92,(byte)0x80,(byte)0xbf,(byte)0xf9,(byte)0xcd,(byte)0xa7,(byte)0x67,(byte)0xdc,(byte)0xca,(byte)0xca,(byte)0xca,(byte)0xca,(byte)0xd8
				,(byte)0x98,(byte)0x10,(byte)0x77,(byte)0xef,(byte)0x4e,(byte)0x4e,(byte)0x8e,(byte)0x8e,(byte)0xc2,(byte)0xfc,(byte)0xbc,(byte)0xd7,(byte)0xbb,(byte)0xbd,(byte)0xd,(byte)0x5a,(byte)0x6d,(byte)0x36,(byte)0xbb,(byte)0xb3
				,(byte)0x3,(byte)0x46,(byte)0x63,(byte)0x7d,(byte)0xbd,(byte)0xc9,(byte)0x4,(byte)0x6,(byte)0x43,(byte)0x43,(byte)0xc3,(byte)0x73,(byte)0xcf,(byte)0x7d,(byte)0x86,(byte)0xfb,(byte)0x80,(byte)0x78,(byte)0x7c,(byte)0x61
				,(byte)0xe1,(byte)0xea,(byte)0x55,(byte)0x21,(byte)0xee,(byte)0xdf,(byte)0xff,(byte)0xdb,(byte)0xdf,(byte)0x7e,(byte)0xfb,(byte)0x5b,(byte)0xf0,(byte)0x7a,(byte)0xaf,(byte)0x5e,(byte)0x9d,(byte)0x9d,(byte)0x85,(byte)0xb9
				,(byte)0xb9,(byte)0xed,(byte)0xed,(byte)0x7d,(byte)0xfb,(byte)0xc0,(byte)0x6a,(byte)0x3d,(byte)0x7e,(byte)0xdc,(byte)0xe3,(byte)0x81,(byte)0xb,(byte)0x17,(byte)0x7e,(byte)0xf8,(byte)0xc3,(byte)0xc3,(byte)0x87,(byte)0xa1
				,(byte)0xb9,(byte)0xd9,(byte)0xe3,(byte)0x69,(byte)0x69,(byte)0x91,(byte)0x4c,(byte)0x3b,(byte)0x71,(byte)0xe2,(byte)0xd9,(byte)0x93,(byte)0x6a,(byte)0x24,(byte)0xb2,(byte)0xb8,(byte)0x38,(byte)0x38,(byte)0x28,(byte)0xc4
				,(byte)0xd8,(byte)0xd8,(byte)0xc8,(byte)0xc8,(byte)0xcd,(byte)0x9b,(byte)0x70,(byte)0xfd,(byte)0xfa,(byte)0x9b,(byte)0x6f,(byte)0x4e,(byte)0x4d,(byte)0x41,(byte)0x2c,(byte)0x36,(byte)0x3a,(byte)0xba,(byte)0xb4,(byte)0x4
				,(byte)0x76,(byte)0xbb,(byte)0xc9,(byte)0x94,(byte)0xcb,(byte)0x81,(byte)0xdd,(byte)0x7e,(byte)0xe4,(byte)0x48,(byte)0x77,(byte)0x37,(byte)0x18,(byte)0x8d,(byte)0x2e,(byte)0xd7,(byte)0xb9,(byte)0x73,(byte)0xa0,(byte)0xde
				,(byte)0xf3,(byte)0xfc,(byte)0x1e,(byte)0x13,(byte)0xb2,(byte)0xd9,(byte)0x6c,(byte)0x16,(byte)0x60,(byte)0x77,(byte)0x77,(byte)0x77,(byte)0xf7,(byte)0xd1,(byte)0xfa,(byte)0xfa,(byte)0x9f,(byte)0x24,(byte)0x91,(byte)0x88
				,(byte)0x46,(byte)0xc7,(byte)0xc7,(byte)0x21,(byte)0x18,(byte)0xbc,(byte)0x7d,(byte)0x3b,(byte)0x18,(byte)0x84,(byte)0xf,(byte)0x3f,(byte)0x5c,(byte)0x5a,(byte)0x52,(byte)0xa9,(byte)0x40,(byte)0xab,(byte)0x6d,(byte)0x6d
				,(byte)0xb5,(byte)0xd9,(byte)0xe0,(byte)0xd8,(byte)0xb1,(byte)0x97,(byte)0x5f,(byte)0x76,(byte)0xb9,(byte)0xa0,(byte)0xad,(byte)0xad,(byte)0xb3,(byte)0xb3,(byte)0xab,(byte)0xb,(byte)0x6c,(byte)0x36,(byte)0x9b,(byte)0xed
				,(byte)0xd3,(byte)0x62,(byte)0xf8,(byte)0x71,(byte)0x65,(byte)0x69,(byte)0xc9,(byte)0xeb,(byte)0xfd,(byte)0xcd,(byte)0x6f,(byte)0x84,(byte)0x8,(byte)0x4,(byte)0x6e,(byte)0xdd,(byte)0x7a,(byte)0xf3,(byte)0x4d,(byte)0xf8
				,(byte)0xe0,(byte)0x83,(byte)0xb7,(byte)0xde,(byte)0x5a,(byte)0x5e,(byte)0x86,(byte)0x50,(byte)0xe8,(byte)0xd6,(byte)0xad,(byte)0x58,(byte)0xc,(byte)0x2c,(byte)0x96,(byte)0x8a,(byte)0x8a,(byte)0x6c,(byte)0x16,(byte)0x5a
				,(byte)0x5b,(byte)0xcf,(byte)0x9e,(byte)0xad,(byte)0xab,(byte)0x83,(byte)0xc6,(byte)0xc6,(byte)0x9e,(byte)0x9e,(byte)0x83,(byte)0x7,(byte)0xc1,(byte)0xe9,(byte)0x74,(byte)0xb9,(byte)0x5e,(byte)0x79,(byte)0x45,(byte)0x51
				,(byte)0xd4,(byte)0x3a,(byte)0x9d,(byte)0x4e,(byte)0xa7,(byte)0xd7,(byte)0x83,(byte)0x5a,(byte)0xad,(byte)0x56,(byte)0xcb,(byte)0xfa,(byte)0x1a,(byte)0x89,(byte)0xe4,(byte)0xf3,(byte)0x72,(byte)0xae,(byte)0xf,(byte)0x4
				,(byte)0x1e,(byte)0x5f,(byte)0x91,(byte)0x54,(byte)0x6a,(byte)0x63,(byte)0x23,(byte)0x10,(byte)0x80,(byte)0x48,(byte)0x24,(byte)0x14,(byte)0x4a,(byte)0xa7,(byte)0x61,(byte)0x65,(byte)0x25,(byte)0x93,(byte)0x31,(byte)0x99
				,(byte)0xc0,(byte)0x62,(byte)0xa9,(byte)0xac,(byte)0x2c,(byte)0x2b,(byte)0x93,(byte)0x49,(byte)0x4b,(byte)0xad,(byte)0x7e,(byte)0x7a,(byte)0xe0,(byte)0x89,(byte)0x44,(byte)0x2c,(byte)0x36,(byte)0x30,(byte)0x20,(byte)0x44
				,(byte)0x22,(byte)0x11,(byte)0x8b,(byte)0xcd,(byte)0xcf,(byte)0xc3,(byte)0xc6,(byte)0x46,(byte)0x38,(byte)0x7c,(byte)0xe7,(byte)0xe,(byte)0x78,(byte)0xbd,(byte)0xaf,(byte)0xbd,(byte)0xf6,(byte)0xd7,(byte)0xbf,(byte)0xc2
				,(byte)0xfd,(byte)0xfb,(byte)0x43,(byte)0x43,(byte)0xcb,(byte)0xcb,(byte)0xb0,(byte)0xbc,(byte)0x1c,(byte)0x8,(byte)0x94,(byte)0x97,(byte)0x83,(byte)0xd1,(byte)0x68,(byte)0x36,(byte)0x9b,(byte)0x4c,(byte)0x70,(byte)0xf0
				,(byte)0xe0,(byte)0x77,(byte)0xbe,(byte)0xe3,(byte)0xf1,(byte)0x40,(byte)0x57,(byte)0xd7,(byte)0x99,(byte)0x33,(byte)0xed,(byte)0xed,(byte)0xd0,(byte)0xdd,(byte)0x7d,(byte)0xe2,(byte)0xc4,(byte)0x4f,(byte)0x7f,(byte)0xfa
				,(byte)0xf0,(byte)0x7c,(byte)0xb5,(byte)0xdb,(byte)0xed,(byte)0x76,(byte)0x77,(byte)0x74,(byte)0xc8,(byte)0x4d,(byte)0x4b,(byte)0x32,(byte)0x9,(byte)0xf3,(byte)0xf3,(byte)0xf3,(byte)0xf3,(byte)0x8a,(byte)0x2,(byte)0x77
				,(byte)0xef,(byte)0xde,(byte)0xbd,(byte)0xbb,(byte)0xb1,(byte)0x21,(byte)0xa7,(byte)0xbc,(byte)0xbf,(byte)0xfc,(byte)0x45,(byte)0x88,(byte)0xee,(byte)0xee,(byte)0xee,(byte)0xee,(byte)0x1f,(byte)0xfc,(byte)0xe0,(byte)0x53
				,(byte)0x5a,(byte)0x4a,(byte)0x45,(byte)0x88,(byte)0x42,(byte)0x1,(byte)0xf4,(byte)0xfa,(byte)0x8a,(byte)0xa,(byte)0x45,(byte)0x1,(byte)0xb3,(byte)0x59,(byte)0xaf,(byte)0xdf,(byte)0xd9,(byte)0x81,(byte)0x7c,(byte)0x3e
				,(byte)0x1a,(byte)0x8d,(byte)0x44,(byte)0x60,(byte)0x65,(byte)0x65,(byte)0x72,(byte)0x72,(byte)0x64,(byte)0x4,(byte)0xee,(byte)0xdd,(byte)0x7b,(byte)0xf7,(byte)0xdd,(byte)0x57,(byte)0x5e,(byte)0x11,(byte)0x42,(byte)0xa3
				,(byte)0xd1,(byte)0x68,(byte)0x1e,(byte)0xc7,(byte)0xc,(byte)0x42,(byte)0x14,(byte)0xa,(byte)0x8a,(byte)0x2,(byte)0x7e,(byte)0xff,(byte)0xfb,(byte)0xef,(byte)0xff,(byte)0xf1,(byte)0x8f,(byte)0x10,(byte)0xe,(byte)0x8f
				,(byte)0x8f,(byte)0x7,(byte)0x83,(byte)0x10,(byte)0x89,(byte)0xcc,(byte)0xcf,(byte)0xaf,(byte)0xaf,(byte)0xcb,(byte)0x18,(byte)0x4f,(byte)0x26,(byte)0x21,(byte)0x16,(byte)0x5b,(byte)0x5f,(byte)0x57,(byte)0xab,(byte)0x21
				,(byte)0x9b,(byte)0xb5,(byte)0xd9,(byte)0xec,(byte)0x76,(byte)0x68,(byte)0x6d,(byte)0x3d,(byte)0x77,(byte)0xae,(byte)0xa1,(byte)0x1,(byte)0xda,(byte)0xdb,(byte)0x25,(byte)0xf0,(byte)0x9e,(byte)0x9e,(byte)0xd3,(byte)0xa7
				,(byte)0x7f,(byte)0xf2,(byte)0x93,(byte)0x8f,(byte)0x9f,(byte)0xa8,(byte)0xfc,(byte)0x7b,(byte)0x23,(byte)0xf4,(byte)0xc6,(byte)0x1b,(byte)0x6f,(byte)0xbc,(byte)0xb1,(byte)0xb9,(byte)0x29,(byte)0x93,(byte)0x60,(byte)0x36
				,(byte)0xb,(byte)0xe7,(byte)0xce,(byte)0x9d,(byte)0x3b,(byte)0xa7,(byte)0x56,(byte)0xcb,(byte)0x9e,(byte)0xdf,(byte)0x6c,(byte)0x86,(byte)0xe6,(byte)0xe6,(byte)0xe6,(byte)0x66,(byte)0x8f,(byte)0x47,(byte)0xf6,(byte)0x5
				,(byte)0x17,(byte)0x2f,(byte)0x7e,(byte)0xfc,(byte)0x85,(byte)0x43,(byte)0x43,(byte)0x7f,(byte)0xf8,(byte)0xc3,(byte)0xf3,(byte)0xcf,(byte)0xb,(byte)0x11,(byte)0xe,(byte)0xdf,(byte)0xbd,(byte)0x1b,(byte)0xe,(byte)0x43
				,(byte)0x2c,(byte)0xb6,(byte)0xb4,(byte)0x24,(byte)0xeb,(byte)0x73,(byte)0x2a,(byte)0x5,(byte)0xa0,(byte)0xd1,(byte)0xe4,(byte)0x72,(byte)0x0,(byte)0xb9,(byte)0xdc,(byte)0xce,(byte)0x8e,(byte)0xa2,(byte)0xc0,(byte)0x47
				,(byte)0x77,(byte)0xbd,(byte)0x8f,(byte)0x2,(byte)0x97,(byte)0x9f,(byte)0x99,(byte)0x8c,(byte)0x10,(byte)0x1a,(byte)0xd,(byte)0xc4,(byte)0xe3,(byte)0xe9,(byte)0xb4,(byte)0x4e,(byte)0x7,(byte)0xe1,(byte)0xf0,(byte)0xda
				,(byte)0x5a,(byte)0x79,(byte)0x39,(byte)0x6c,(byte)0x6f,(byte)0x17,(byte)0xa,(byte)0x5a,(byte)0x2d,(byte)0xe4,(byte)0x72,(byte)0x95,(byte)0x95,(byte)0x26,(byte)0x13,(byte)0x38,(byte)0x1c,(byte)0x6e,(byte)0x77,(byte)0x59
				,(byte)0x19,(byte)0xb4,(byte)0xb7,(byte)0x1f,(byte)0x39,(byte)0x52,(byte)0x5b,(byte)0x2b,(byte)0xab,(byte)0x4a,(byte)0x73,(byte)0x33,(byte)0x1c,(byte)0x3d,(byte)0x7a,(byte)0xf2,(byte)0xe4,(byte)0x8f,(byte)0x7e,(byte)0xf4
				,(byte)0x18,(byte)0xb3,(byte)0xc0,(byte)0xe0,(byte)0xe0,(byte)0xe0,(byte)0xe0,(byte)0xa5,(byte)0x4b,(byte)0x42,(byte)0x5c,(byte)0xbd,(byte)0x7a,(byte)0xf5,(byte)0xea,(byte)0xdc,(byte)0x1c,(byte)0x8c,(byte)0x8f,(byte)0x8f
				,(byte)0x8f,(byte)0x27,(byte)0x93,(byte)0x90,(byte)0x4a,(byte)0xa5,(byte)0x52,(byte)0xd9,(byte)0x2c,(byte)0x38,(byte)0x1c,(byte)0xe,(byte)0x7,(byte)0x48,(byte)0x43,(byte)0x68,(byte)0xb5,(byte)0x72,(byte)0x55,(byte)0xa5
				,(byte)0x52,(byte)0xc9,(byte)0x2d,(byte)0xac,(byte)0x5a,(byte)0x2d,(byte)0x19,(byte)0x20,(byte)0x87,(byte)0x92,(byte)0x74,(byte)0x7a,(byte)0x76,(byte)0x16,(byte)0x52,(byte)0xa9,(byte)0x78,(byte)0x7c,(byte)0x6e,(byte)0x4e
				,(byte)0xe,(byte)0x2f,(byte)0xe9,(byte)0x34,(byte)0xc4,(byte)0xe3,(byte)0x7e,(byte)0xbf,(byte)0x10,(byte)0xb0,(byte)0xbe,(byte)0x3e,(byte)0x3b,(byte)0x2b,(byte)0x4,(byte)0xac,(byte)0xae,(byte)0xde,(byte)0xbf,(byte)0xf
				,(byte)0xb2,(byte)0x97,(byte)0xff,(byte)0x28,(byte)0x93,(byte)0x14,(byte)0x45,(byte)0x8,(byte)0x10,(byte)0x42,(byte)0x51,(byte)0x54,(byte)0x2a,(byte)0x48,(byte)0x24,(byte)0x8a,(byte)0x8b,(byte)0xd,(byte)0x6,(byte)0x58
				,(byte)0x5b,(byte)0x2b,(byte)0x29,(byte)0xb1,(byte)0xdb,(byte)0x21,(byte)0x95,(byte)0x32,(byte)0x18,(byte)0xac,(byte)0x56,(byte)0xb0,(byte)0xdb,(byte)0x1b,(byte)0x1b,(byte)0x4b,(byte)0x4b,(byte)0xe1,(byte)0xd0,(byte)0xa1
				,(byte)0xe3,(byte)0xc7,(byte)0xb5,(byte)0x5a,(byte)0x68,(byte)0x69,(byte)0x69,(byte)0x6f,(byte)0x37,(byte)0x9b,(byte)0xa1,(byte)0xb1,(byte)0xd1,(byte)0xe5,(byte)0xea,(byte)0xe8,(byte)0x0,(byte)0x8f,(byte)0xc7,(byte)0xe3
				,(byte)0x79,(byte)0x9c,(byte)0x19,(byte)0xe5,(byte)0x63,(byte)0xf,(byte)0x78,(byte)0xbd,(byte)0x72,(byte)0xe1,(byte)0x11,(byte)0xe,(byte)0x87,(byte)0xc3,(byte)0xe1,(byte)0xb0,(byte)0x34,(byte)0x4c,(byte)0x28,(byte)0x24
				,(byte)0x7f,(byte)0xcf,(byte)0xe5,(byte)0x64,(byte)0x99,(byte)0xd1,(byte)0xeb,(byte)0xe5,(byte)0xe2,(byte)0x43,(byte)0xa5,(byte)0x92,(byte)0x4c,(byte)0x91,(byte)0x8a,(byte)0x4b,(byte)0xaf,(byte)0x9,(byte)0x21,(byte)0x44
				,(byte)0x2a,(byte)0x25,(byte)0xf7,(byte)0xf8,(byte)0x99,(byte)0xc,(byte)0xe4,(byte)0xf3,(byte)0xbb,(byte)0xbb,(byte)0x85,(byte)0x2,(byte)0xe4,(byte)0x72,(byte)0x92,(byte)0x1,(byte)0xe9,(byte)0xf4,(byte)0xe6,(byte)0x26
				,(byte)0x40,(byte)0x2a,(byte)0x25,(byte)0x77,(byte)0xb8,(byte)0x85,(byte)0x82,(byte)0x64,(byte)0xc4,(byte)0x1e,(byte)0x70,(byte)0xbd,(byte)0x5e,(byte)0xa7,(byte)0xcb,(byte)0xe5,(byte)0xa0,(byte)0xb2,(byte)0xd2,(byte)0x64
				,(byte)0xca,(byte)0xe7,(byte)0xa1,(byte)0xba,(byte)0xda,(byte)0xe9,(byte)0xd4,(byte)0x68,(byte)0xc0,(byte)0xe1,(byte)0x70,(byte)0xb9,(byte)0xf4,(byte)0x7a,(byte)0xa8,(byte)0xaf,(byte)0x77,(byte)0xb9,(byte)0x2a,(byte)0x2a
				,(byte)0xc0,(byte)0xe3,(byte)0x69,(byte)0x6d,(byte)0x35,(byte)0x99,(byte)0xa0,(byte)0xb1,(byte)0xb1,(byte)0xa9,(byte)0xa9,(byte)0xad,(byte)0xd,(byte)0x5c,(byte)0x2e,(byte)0xb7,(byte)0xfb,(byte)0x69,(byte)0x1a,(byte)0xb6
				,(byte)0x4f,(byte)0xfc,(byte)0xc3,(byte)0xea,(byte)0xea,(byte)0xea,(byte)0xea,(byte)0xc0,(byte)0x80,(byte)0x10,(byte)0xa1,(byte)0x50,(byte)0x28,(byte)0xd4,(byte)0xdf,(byte)0x2f,(byte)0x73,(byte)0x41,(byte)0x34,(byte)0x2a
				,(byte)0x97,(byte)0x9c,(byte)0x1a,(byte)0x8d,(byte)0xbc,(byte)0xaf,(byte)0x52,(byte)0x49,(byte)0xc0,(byte)0x7b,(byte)0x0,(byte)0xf6,(byte)0x8e,(byte)0xdf,(byte)0x33,(byte)0xc4,(byte)0x47,(byte)0x29,(byte)0xfd,(byte)0x68
				,(byte)0xc3,(byte)0x2a,(byte)0x63,(byte)0xfb,(byte)0xd1,(byte)0x6b,(byte)0x8d,(byte)0xa6,(byte)0xb8,(byte)0x58,(byte)0x8,(byte)0x59,(byte)0x16,(byte)0xf3,(byte)0x79,(byte)0x19,(byte)0x62,(byte)0x42,(byte)0x80,(byte)0xd3
				,(byte)0xe9,(byte)0x70,(byte)0x94,(byte)0x94,(byte)0x40,(byte)0x73,(byte)0xb3,(byte)0xdb,(byte)0xbd,(byte)0xb7,(byte)0x3b,(byte)0xb4,(byte)0xdb,(byte)0x25,(byte)0xf0,(byte)0x97,(byte)0x5f,(byte)0x7e,(byte)0xf6,(byte)0x2a
				,(byte)0xf2,(byte)0xd8,(byte)0x2f,(byte)0x8,(byte)0x85,(byte)0x42,(byte)0xa1,(byte)0xde,(byte)0x5e,(byte)0x21,(byte)0x16,(byte)0x16,(byte)0x16,(byte)0x16,(byte)0x7c,(byte)0x3e,(byte)0x48,(byte)0x24,(byte)0x12,(byte)0x9
				,(byte)0xe9,(byte)0x4b,(byte)0x39,(byte)0x84,(byte)0x3c,(byte)0xab,(byte)0xa8,(byte)0x54,(byte)0x2a,(byte)0x95,(byte)0x5a,(byte)0x2d,(byte)0xb7,(byte)0xc1,(byte)0x4e,(byte)0x27,(byte)0x98,(byte)0x4c,(byte)0x26,(byte)0x53
				,(byte)0x73,(byte)0xb3,(byte)0xdc,(byte)0x34,(byte)0x9d,(byte)0x3a,(byte)0xf5,(byte)0xd5,(byte)0x5f,(byte)0xac,(byte)0x7c,(byte)0x2d,(byte)0x5f,(byte)0xcb,(byte)0x7f,(byte)0xa9,(byte)0xfc,(byte)0x1f,(byte)0xce,(byte)0x60
				,(byte)0x6c,(byte)0x4d,(byte)0x5d,(byte)0x76,(byte)0xd3,(byte)0x39,(byte)0x0,(byte)0x0,(byte)0x0,(byte)0x0,(byte)0x49,(byte)0x45,(byte)0x4e,(byte)0x44,(byte)0xae,(byte)0x42,(byte)0x60,(byte)0x82

		};
		
		public TitleWidget(String title)
		{
			super();
			this.setLayout(new BoxLayout(this,BoxLayout.X_AXIS));
			this.setBorder(BorderFactory.createEmptyBorder(5,5,5,5));
			this.mTitle=new JLabel(title);
			this.mTitle.setIcon(new ImageIcon(this.mCopasiIconData));
			this.mTitle.setFont(this.mTitle.getFont().deriveFont(20.0f));
			this.mTitle.setMinimumSize(this.mTitle.getPreferredSize());
			this.add(this.mTitle);
			this.add(Box.createHorizontalGlue());
			this.mUpdateModelBox=new JCheckBox("Update model");
			this.mUpdateModelBox.setVisible(false);
			this.add(this.mUpdateModelBox);
			this.mExecutableBox=new JCheckBox("executable");
			this.mExecutableBox.setVisible(false);
			this.add(this.mExecutableBox);
		}
		
	}
	
	
	protected class ProblemWidget extends JPanel 
	{
		/**
		 * 
		 */
		private static final long serialVersionUID = 584567740770423473L;

		public ProblemWidget()
		{
			super();
			this.setLayout(new BoxLayout(this,BoxLayout.Y_AXIS));
			this.setBorder(BorderFactory.createEmptyBorder(5,5,5,5));
		}
	}

	protected class MethodParameterWidget extends JPanel implements ActionListener
	{
		/**
		 * 
		 */
		private static final long serialVersionUID = -4504322965717259865L;
		protected JPanel mControlPanel;
		protected JButton mControlButton;
		protected JPanel mParameterPanel;
		protected JTable mParameterTable;
		protected JComboBox mMethodDropdown;
		private JPanel mDropdownPanel;
		
		public MethodParameterWidget()
		{
			super();
			this.setLayout(new BoxLayout(this,BoxLayout.Y_AXIS));
			this.setBorder(BorderFactory.createEmptyBorder(5,5,5,5));
			this.mControlButton=new JButton("Show Method Parameters...");
			this.mControlButton.setEnabled(false);
			this.mControlButton.addActionListener(this);
			this.mControlButton.setEnabled(false);
			this.mControlPanel=new JPanel();
			this.mControlPanel.setLayout(new BoxLayout(this.mControlPanel,BoxLayout.X_AXIS));
			this.mControlPanel.add(this.mControlButton);
			this.add(this.mControlPanel);
			this.mDropdownPanel=new JPanel();
			this.mDropdownPanel.setLayout(new BoxLayout(this.mDropdownPanel,BoxLayout.X_AXIS));
			this.mDropdownPanel.add(new JLabel("Method: "));
			this.mMethodDropdown=new JComboBox();
			this.mMethodDropdown.setEditable(false);
			this.mDropdownPanel.add(this.mMethodDropdown);
			this.mDropdownPanel.setVisible(false);
			this.add(this.mDropdownPanel);
			this.mParameterPanel=new JPanel();
			this.mParameterPanel.setLayout(new BoxLayout(this.mParameterPanel,BoxLayout.X_AXIS));
			this.add(this.mParameterPanel);
			this.mParameterPanel.add(new JLabel("Method parameters:"));
			this.mParameterTable=new JTable();
			this.mParameterTable.setShowGrid(true);
			this.mParameterTable.setGridColor(Color.BLACK);
			this.mParameterTable.setModel(new MyTableModel(0,2));
			this.mParameterTable.setSelectionMode(ListSelectionModel.SINGLE_SELECTION);
			((DefaultTableColumnModel)this.mParameterTable.getColumnModel()).getColumn(0).setHeaderValue("Parameter Name");
			((DefaultTableColumnModel)this.mParameterTable.getColumnModel()).getColumn(1).setHeaderValue("Parameter Value");
			JScrollPane sv=new JScrollPane(this.mParameterTable);
			this.mParameterPanel.add(sv);
			this.mParameterPanel.setVisible(false);
		}
		
		public void actionPerformed(ActionEvent e)
		{
			this.mParameterPanel.setVisible(!this.mParameterPanel.isVisible());
			this.mDropdownPanel.setVisible(!this.mDropdownPanel.isVisible());
			this.mControlButton.setText((!this.mParameterPanel.isVisible())?"Show Method Parameters...":"Hide Method Parameters...");
			Container cont=this.getParent();
			while(cont.getParent()!=null)
			{
				cont=cont.getParent();
			}
			if(cont instanceof Window)
			{
			  ((Window)cont).pack();
			}
		}
		
		public void fillTable(CCopasiMethod method)
		{
			((DefaultTableModel)this.mParameterTable.getModel()).setRowCount((int)(method.size())+1);
			for(int i=0;i<method.size();i++)
			{
				CCopasiParameter p=method.getParameter(i);
			  if(p!=null)
        {
				  String parameterName=p.getObjectName();
				  this.mParameterTable.setValueAt(parameterName,i,0);
				  switch(p.getType())
				  {
				    case CCopasiParameter.Type_BOOL:
					    Boolean b=new Boolean(p.getBoolValue());
					    this.mParameterTable.setValueAt(b,i,1);
					    break;
				    case CCopasiParameter.Type_CN:
					    String cn=new String(p.getCNValue().getString());
					    this.mParameterTable.setValueAt(cn,i,1);
				  	  break;
				    case CCopasiParameter.Type_KEY:
			  		  String key=new String(p.getCNValue().getString());
		  			  this.mParameterTable.setValueAt(key,i,1);
	  				  break;
	  			  case CCopasiParameter.Type_STRING:
  					  String s=new String(p.getStringValue());
  					  this.mParameterTable.setValueAt(s,i,1);
  					  break;
  				  case CCopasiParameter.Type_FILE:
  					  String f=new String(p.getFileValue());
  					  this.mParameterTable.setValueAt(f,i,1);
  					  break;
  				  case CCopasiParameter.Type_DOUBLE:
  					  Double d=new Double(p.getDblValue());
  					  this.mParameterTable.setValueAt(d,i,1);
  					  break;
  				  case CCopasiParameter.Type_UDOUBLE:
  					  Double ud=new Double(p.getUDblValue());
  					  this.mParameterTable.setValueAt(ud,i,1);
  					  break;
  				  case CCopasiParameter.Type_INT:
  					  Long in=new Long(p.getIntValue());
  					  this.mParameterTable.setValueAt(in,i,1);
  					  break;
  				  case CCopasiParameter.Type_UINT:
  					  Long uin=new Long(p.getUIntValue());
  					  this.mParameterTable.setValueAt(uin,i,1);
  					  break;
  				  default:
  					  break;
	  			}
        }
			}
			if(method.size()==0)
			{
				this.mControlButton.setEnabled(false);
				this.mParameterPanel.setVisible(false);
			}
			else
			{
				this.mControlButton.setEnabled(true);
			}
		}

		public void fillMethodDropdown(CCopasiTask task) {
			//System.out.println(task.getClass().getName());			
			//System.out.println("Filling method combobox.");
			//System.out.println("Num valid methods: "+new Long(task.getValidMethods().size()).toString());
			this.mMethodDropdown.removeAllItems();
			for(int i=0;i<task.getValidMethods().size();i++)
			{
				//System.out.println(task.getValidMethods().get(i));
				String name=CCopasiMethod.getSubTypeName(task.getValidMethods().get(i));
				this.mMethodDropdown.addItem(name);
			}
			
		}
	}

	protected class ButtonWidget extends JPanel
	{
		/**
		 * 
		 */
		private static final long serialVersionUID = 6102573907884431189L;
		protected JButton mRunButton;
		protected JButton mRevertButton;
		protected JButton mReportButton;
		protected JButton mOutputAssistantButton;
		
		public ButtonWidget()
		{
			super();
			this.setLayout(new BoxLayout(this,BoxLayout.X_AXIS));
			this.setBorder(BorderFactory.createEmptyBorder(5,5,5,5));
			this.mRunButton=new JButton("Run");
			this.mRunButton.setEnabled(false);
			this.add(this.mRunButton);
			this.mRevertButton=new JButton("Revert");
			this.mRevertButton.setVisible(false);
			this.mRevertButton.setEnabled(false);
			this.add(this.mRevertButton);
			this.mReportButton=new JButton("Create Default Report");
			this.mReportButton.setVisible(true);
			this.mReportButton.setEnabled(false);
			this.add(this.mReportButton);
			this.mOutputAssistantButton=new JButton("Output Assistant");
			this.mOutputAssistantButton.setVisible(false);
			this.mOutputAssistantButton.setEnabled(false);
			this.add(this.mOutputAssistantButton);
		}
	}
	
	
	
	protected String mTitle;

	protected TitleWidget   mTitleWidget;
	protected ProblemWidget mProblemWidget;
	protected MethodParameterWidget  mMethodWidget;
	protected ButtonWidget  mButtonWidget;
	protected CCopasiTask mTask;
	protected CDataModel mDataModel;
	protected boolean mDefaultReportCreated;
        protected boolean mOverwrite;
        protected Vector<TaskRunEventListener> mListeners;
	
	public TaskWidget(String title,boolean enableReportButton)
	{
		super();
                this.mDataModel=CRootContainer.addDatamodel();
		this.mTask=null;
                this.mOverwrite=false;
		this.setLayout(new BoxLayout(this,BoxLayout.Y_AXIS));
		this.mTitle=title;
		this.mTitleWidget=new TitleWidget(this.mTitle);
		this.add(this.mTitleWidget);
		this.add(new JSeparator(SwingConstants.HORIZONTAL));
		this.mProblemWidget=new ProblemWidget();
		this.add(this.mProblemWidget);
		this.add(new JSeparator());
		this.mMethodWidget=new MethodParameterWidget();
		this.add(this.mMethodWidget);
		this.add(new JSeparator(SwingConstants.HORIZONTAL));
		this.mButtonWidget=new ButtonWidget();
		this.add(this.mButtonWidget);
		this.mButtonWidget.mRunButton.addActionListener(this);
		this.mButtonWidget.mReportButton.addActionListener(this);
		this.mMethodWidget.mMethodDropdown.addActionListener(this);
		this.mMethodWidget.mParameterTable.getModel().addTableModelListener(this);
		this.enableDefaultReportButton(enableReportButton);
        }
	
	
	/**
	 * Sets the task associated with the dialog.
	 * This method is called by derived classes. E.g. TrajectoryTaskWidget calls this method with the trajectory task.
	 * @param task
	 */
	protected void setTask(CCopasiTask task)
	{
		if(task!=this.mTask)
		{
		  this.mTask=task;
		  this.mDefaultReportCreated=false;
		  this.mMethodWidget.fillMethodDropdown(this.mTask);
		  if(this.mTask!=null)
	    {
			  this.mButtonWidget.mReportButton.setEnabled(true);
			  this.mButtonWidget.mRunButton.setEnabled(true);
		  }
		}
	}
	
	/**
	 * Handles button events from the ButtonWidget.
	 */
	public void actionPerformed(ActionEvent e)
	{
            if(e.getSource()==this.mButtonWidget.mRunButton)
            {
                //System.out.println("Saving results to \""+this.mTask.getReport().getTarget()+"\".");
                try
                {
                    this.mTask.process(true);	
                    TaskRunEvent event=new TaskRunEvent(this.mTask);
                    this.processTaskRunEvent(event);
                }
                catch(java.lang.Exception ex)
                {
                    // show an error dialog.
                    String message=ex.getMessage();
                    JOptionPane.showMessageDialog(null, message , "Error", JOptionPane.ERROR_MESSAGE);
                }
            }
            else if(e.getSource()==this.mMethodWidget.mMethodDropdown)
            {
                String s=(String)((JComboBox)e.getSource()).getSelectedItem();
                if(s == null){
                    return;
                }
                int type=CCopasiMethod.TypeNameToEnum(s);
                this.mMethodWidget.mParameterTable.getModel().removeTableModelListener(this);
                this.mMethodWidget.mMethodDropdown.removeActionListener(this);
                this.mTask.setMethodType(type);
                this.mMethodWidget.fillTable(this.mTask.getMethod());
                this.mMethodWidget.mParameterTable.getModel().addTableModelListener(this);
                this.mMethodWidget.mMethodDropdown.addActionListener(this);
            }
            else if(e.getSource()==this.mButtonWidget.mReportButton)
            {
                this.createDefaultReportDefinition();
                if(this.mTask.getReport().getTarget().equals(""))
                {
                    // ask for a filename
                    JFileChooser chooser=new JFileChooser();
                    int returnVal = chooser.showSaveDialog(this);
                    if(returnVal == JFileChooser.APPROVE_OPTION) 
                    {
                        String fileName=chooser.getSelectedFile().getAbsolutePath();
                        if(!fileName.equals(""))
                        {
                            this.mTask.getReport().setTarget(fileName);
                        }
                    }
                }
                this.mButtonWidget.mReportButton.setEnabled(false);
            }

        }

	/**
	 * Handles events that come from changes in the method parameter table.
	 */
	public void tableChanged(TableModelEvent e) {
		this.mMethodWidget.mParameterTable.getModel().removeTableModelListener(this);
		// find out what type the parameter has
		// check if the value is valid for that type of parameter
		// set the value of the parameter if it is valid
		CCopasiParameter p=this.mTask.getMethod().getParameter(e.getFirstRow());
		if(p!=null)
    {
      String value=this.mMethodWidget.mParameterTable.getValueAt(e.getFirstRow(),e.getColumn()).toString();
		  int row=e.getFirstRow();
		  int column=e.getColumn();
		
      switch(p.getType())
	  	{
		    case CCopasiParameter.Type_BOOL:
		  	  String s=value.toLowerCase();
		  	  if(s.equals("true") || s.equals("yes") || s.equals("1"))
	  		  {
  				  p.setBoolValue(true);
  			  }
  			  else if(s.equals("false") || s.equals("no") || s.equals("0"))
  			  {
  				  p.setBoolValue(false);
  			  }
  			  else
  			  {
  				  this.mMethodWidget.mParameterTable.setValueAt(new Boolean(p.getBoolValue()).toString(),row,column);
  			  }
  			  break;
  		  case CCopasiParameter.Type_CN:
  			  CRegisteredCommonName on=new CRegisteredCommonName(value);
  			  p.setCNValue(on);
  			  break;
  		  case CCopasiParameter.Type_KEY:
  			  p.setKeyValue(value);
  			  break;
   		  case CCopasiParameter.Type_STRING:
	  		  p.setStringValue(value);
  			  break;
  		  case CCopasiParameter.Type_FILE:
  			  p.setFileValue(value);
  			  break;
  		  case CCopasiParameter.Type_DOUBLE:
  			  try
  			  {
  			    Double d=new Double(value);
  			    p.setDblValue(d.doubleValue());
  			  }
  			  catch(NumberFormatException e1)
  			  {
    				this.mMethodWidget.mParameterTable.setValueAt(p.getDblValue(), row, column);  
  			  }
	  		  break;
	  	  case CCopasiParameter.Type_UDOUBLE:
	  		  try
	  		  {
	  		    Double d=new Double(value);
	  		    if(d.doubleValue()>0.0)
	  		    {
	  			    p.setUDblValue(d.doubleValue());			    	
	  		    }
	  		    else
	  		    {
	    				this.mMethodWidget.mParameterTable.setValueAt(p.getUDblValue(), row, column); 			    	
	  		    }
	  		  }
	  		  catch(NumberFormatException e2)
	  		  {
	    			this.mMethodWidget.mParameterTable.setValueAt(p.getDblValue(), row, column); 
	  		  }
			    break;
	  	  case CCopasiParameter.Type_INT:
	  		  try
	  		  {
	  		    Integer i=new Integer(value);
	  		    p.setIntValue(i.intValue());
	  		  }
	  		  catch(NumberFormatException e3)
	  		  {
	    			this.mMethodWidget.mParameterTable.setValueAt(p.getIntValue(), row, column);  
	  		  }
	  		  break;
		    case CCopasiParameter.Type_UINT:
		  	  try
		  	  {
		 		    Integer ui=new Integer(value);
				    if(ui.intValue()>0)
				    {
					    p.setUDblValue(ui.intValue());			    	
				    }
				    else
				    {
						this.mMethodWidget.mParameterTable.setValueAt(p.getUIntValue(), row, column);  			    	
				    }
		  	  }
			    catch(NumberFormatException e4)
			    {
				    this.mMethodWidget.mParameterTable.setValueAt(p.getUIntValue(), row, column);  
			    }
			    break;
		    default:
			    break;
		  }		
	  }
		this.mMethodWidget.mParameterTable.getModel().addTableModelListener(this);
}
	
	/**
	 * This can be called to enable or disable the button that lets the user create the default report.
	 * If the calling program already set a report on the task that is associated with the dialog, then this button should probably be disabled.
	 * Clicking the button creates a report that is suitable for the task, e.g. for the trajectory task clicking the button would create
	 * a report that includes the time, all metabolites and all global parameters.
	 * @param enable
	 */
	public void enableDefaultReportButton(boolean enable)
	{
		this.mButtonWidget.mReportButton.setEnabled(enable);
	}
	
	/**
	 * This method is a convenient way to load an SBML model to use with the associated task.
	 * @param fileName
	 * @return
	 */
	public boolean loadModel(String fileName)
	{
           CCopasiMessage.clearDeque();
           try
           {
             mDataModel.importSBML(fileName);
           }
           catch(java.lang.Exception e)
           {
             // show an error dialog
             if(mDataModel.getModel()==null)
             {
                 this.resetTask();
                 this.mButtonWidget.mReportButton.setEnabled(false);
                 this.mButtonWidget.mRunButton.setEnabled(false);
             }
             return false;
           }
           // check if the file could not be read at all
           if(CCopasiMessage.getHighestSeverity()==CCopasiMessage.ERROR || CCopasiMessage.getHighestSeverity()==CCopasiMessage.EXCEPTION)
           {
              return false;
           }
           // the model has been loaded
           this.resetTask();
           this.mButtonWidget.mReportButton.setEnabled(true);
           this.mButtonWidget.mRunButton.setEnabled(true);
	   return true;
	}

	/**
	 * This method does nothing.
	 * Derived classes should implement it to set the task to the correct task for the dialog.
	 */
	protected void resetTask()
	{
          this.mDefaultReportCreated=false;
          this.mButtonWidget.mReportButton.setEnabled(false);
	}
	
	
	/**
	 * This is a convenience method to find out what target file has been set for the report that
	 * is to be written when the task is excecuted.
	 * @return
	 */
	public String getTarget()
	{
		
		String target=null;
		if(this.mTask!=null)
		{
		  CReport report=this.mTask.getReport();
		  if(report!=null)
		  {
			target=report.getTarget();
		  }
		}
		return target;
	}
	
	/**
	 * This method sets the filename for the report.
	 * @param target
	 */
	public void setTarget(String target)
	{
		if(this.mTask!=null)
		{
		  CReport report=this.mTask.getReport();
		  if(report!=null)
		  {
			  report.setTarget(target);
                          report.setAppend(!this.mOverwrite);
		  }
		}
	}
	
	/**
	 * This method creats a report that is suitable for the task associated with the widget and activates it.
	 */
	public void createDefaultReportDefinition()
	{
		if(!this.mDefaultReportCreated && this.mTask!=null)
		{
                  //System.out.println("Creating default report.");;
		  int index=COutputAssistant.getDefaultReportIndex(this.mTask.getProblem());
		  CDataObject def=COutputAssistant.createDefaultOutput(index, this.mTask,mDataModel, true);
		  if (def instanceof CReportDefinition) 
		  {
			 this.mTask.getReport().setReportDefinition((CReportDefinition)def);
		  }
		  this.mDefaultReportCreated=true;
		}
	}

        /**
         * Returns true if the target for the report associated with the task
         * is to be overwritten when the report is created.
         */
        public boolean getOverwriteTarget()
        {
            return this.mOverwrite;
        }
	
        /**
         * Sets if the target for the report associated with the task
         * is to be overwritten when the report is created.
         * If true, the file associated with the report is overwritten,
         *  otherwise the output is appended to the end of the file.
         * The default behavior is to append the data to the end.
         */
        public void setOverwriteTarget(boolean overwrite)
        {
            this.mOverwrite=overwrite;
        }

        /**
         * Returns a string that contains all COPASI error messages from
         * the error message deque.
         */
        public String getErrorMessages(boolean cronological)
        {
            return CCopasiMessage.getAllMessageText(cronological);
        }



        /**
         * If there are error messages in the deque, this method will display
         * them in a dialog.
         */
        public void displayErrorMessages(boolean cronological)
        {
           if(CCopasiMessage.peekFirstMessage().getNumber()!=COPASIConstants.MCCopasiMessage + 1 )
           {
             if(CCopasiMessage.getHighestSeverity()==CCopasiMessage.ERROR || CCopasiMessage.getHighestSeverity()==CCopasiMessage.EXCEPTION)
             {
                JOptionPane.showMessageDialog(null, this.getErrorMessages(cronological),"ERROR", JOptionPane.ERROR_MESSAGE);
             }
             else
             {
              JOptionPane.showMessageDialog(null, this.getErrorMessages(cronological),"WARNING", JOptionPane.WARNING_MESSAGE);
             }
           }
        }

        /**
         * Adds a TaskRunEventListener to the registration list.
         */
        public void addTaskRunEventListener(TaskRunEventListener listener)
        {
            if(mListeners==null)
            {
                mListeners=new Vector<TaskRunEventListener>();
            }
            mListeners.addElement(listener);
        }

        /**
         * Removes a registered TaskRunEventListener from the registration
         * list.
         */
        public void removeTaskRunEventListener(TaskRunEventListener listener)
        {
            if(mListeners!=null)
            {
                mListeners.removeElement(listener);
            }
        }

        /**
         * This method informs all registered TaskRunEventListeners about a
         * TaskRunEvent that has occured.
         */
        protected void processTaskRunEvent(TaskRunEvent event)
        {
            Enumeration enu;
            TaskRunEventListener listener;
            enu=mListeners.elements();
            while(enu.hasMoreElements())
            {
              listener=(TaskRunEventListener)enu.nextElement();
              listener.taskRun(event);
            }
        }


	public static void main(String[] args)
	{	
        javax.swing.SwingUtilities.invokeLater
        (
          new Runnable() 
          {
            public void run() 
            {
            	JFrame mainDialog=new JFrame();
            	mainDialog.setTitle("Task Dialog");
        		mainDialog.getContentPane().add(new TaskWidget("Test",true));
        		mainDialog.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        		mainDialog.pack();
        		mainDialog.setVisible(true);
            }
          }
        );
    }



}
