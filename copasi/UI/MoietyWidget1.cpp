/*******************************************************************
**  $ CopasiUI/MoietyWidget1.cpp                 
**  $ Author  : Mudita Singhal
**
** This file is used to create the GUI FrontPage for the  information 
** obtained from the data model about the Moiety----It is Basically 
** the Second level of Moieties.
********************************************************************/
#include "MoietyWidget1.h"
#include <qlabel.h>
#include <qlineedit.h>
#include <qpushbutton.h>
#include <qlayout.h>
#include <qtoolbar.h>
#include <qwidget.h>
#include <qframe.h>
#include "listviews.h"

/* 
 *  Constructs a MoietyWidget which is a child of 'parent', with the 
 *  name 'name' and widget flags set to 'f'.
 *
 */

MoietyWidget1::MoietyWidget1( QWidget *parent, const char * name, WFlags f )
    : QWidget(parent, name, f)

{	

	//This is to make the Main Frame of the page
	//The Main layout used is the Vertical Layout

	QVBoxLayout *vboxLayout = new QVBoxLayout(this, 0 );
	Frame1 = new QFrame( this, "Frame1" );
	Frame1->setFrameShape( QFrame::Box );
    Frame1->setFrameShadow( QFrame::Plain);
	vboxLayout->addWidget(Frame1);

	//This Frame had to be added because of the border around the frame
	//The grid Layout is used for this frame
	QVBoxLayout *vboxLayout1 = new QVBoxLayout(Frame1, 0 );
	vboxLayout1->addSpacing(1);
   	Frame3 = new QFrame( Frame1, "Frame3" );
	vboxLayout1->addWidget(Frame3);
	QGridLayout *gridLayout = new QGridLayout(Frame3, 0 );

	//All the other frames(rows) are embeded in it
	Frame2 = new QFrame( Frame3, "Frame2" );
	gridLayout->addWidget(Frame2,0,0,0);
	QGridLayout *gridLayout1 = new QGridLayout( Frame2, 0 );
	
	
	//Frame for Ist Row
	Frame4a = new QFrame(Frame2, "Frame4a" );
    gridLayout1->addWidget(Frame4a,0,0,0);
	QHBoxLayout *hBoxLayout4a = new QHBoxLayout( Frame4a, 0 );
	hBoxLayout4a->addSpacing(15);
	
	TextLabel1 = new QLabel( "Equation", Frame4a );
    hBoxLayout4a->addWidget(TextLabel1);
	hBoxLayout4a->addSpacing(83);
    LineEdit1 = new QLineEdit( "",Frame4a  );
	hBoxLayout4a->addWidget(LineEdit1);
    hBoxLayout4a->addSpacing(20);
	
	//Frame for 2nd Row
	Frame4b = new QFrame( Frame2, "Frame4b" );
    gridLayout1->addWidget(Frame4b,1,0,0);
	QHBoxLayout *hBoxLayout4b = new QHBoxLayout( Frame4b, 0 );
	hBoxLayout4b->addSpacing(15);
	
	TextLabel2= new QLabel( "Total Particle Number",Frame4b );
    hBoxLayout4b->addWidget( TextLabel2);
    hBoxLayout4b->addSpacing(25);
	
	LineEdit2 = new QLineEdit( "", Frame4b );
	hBoxLayout4b->addWidget(LineEdit2 );
	hBoxLayout4b->addSpacing(180);

	
	//Frame for 3rd Row
	Frame4c = new QFrame( Frame2, "Frame4c" );
    gridLayout1->addWidget(Frame4c,2,0,0);
	QHBoxLayout *hBoxLayout4c = new QHBoxLayout( Frame4c, 0 );
	hBoxLayout4c->addSpacing(15);
    
	TextLabel3 = new QLabel( "Dependent Metabolite",Frame4c);
    hBoxLayout4c->addWidget(TextLabel3);
	hBoxLayout4c->addSpacing(25);

	LineEdit3 = new QLineEdit( "", Frame4c );
	hBoxLayout4c->addWidget(LineEdit3 );
	hBoxLayout4c->addSpacing(180);
	   
	
      
    //This is the frame for the cancel and the commit buttons   
	Frame4d= new QFrame( Frame2, "Frame4d" );
	gridLayout1->addWidget(Frame4d,7,0,0);
	QHBoxLayout *hBoxLayout4d = new QHBoxLayout( Frame4d, 0 );
	hBoxLayout4d->addSpacing(15);

	//Th buttons are laid out using the Horizontal Layout
	commitChanges = new QPushButton("&Commit Changes", Frame4d);
	cancelChanges = new QPushButton("&Cancel Changes", Frame4d);
	hBoxLayout4d->addWidget(commitChanges);
	hBoxLayout4d->addSpacing(15);
	hBoxLayout4d->addWidget(cancelChanges);
	hBoxLayout4d->addSpacing(15);
   
   
}


/*This function is used to connect this class to the listviews 
    class to basically choose the right widget to display   */
int MoietyWidget1::isName(QString setValue)
{

	if (mModel == NULL)
	{ 
		return 0;
	}
	

	
		CCopasiVectorN < CMoiety >  &moieties = mModel->getMoieties();
		C_INT32 noOfMoietyRows = moieties.size();
		CMoiety *moiety1;
		moiety1= moieties[(string) setValue];

				
	if(	moiety1 !=NULL)
	{	
		loadName(setValue);
		return 1;
	}
	else
		return 0;
}



/*This function is to load the model for the Moieties*/
void MoietyWidget1::loadMoieties(CModel *model)
{
	if (model != NULL)
	{
		mModel = model;
	}
}





/* This function loads the moiety widget when its name is 
   clicked in the tree   */

void MoietyWidget1::loadName(QString setValue)
{
	
    if (mModel == NULL)
	{ return;
	}
		
		CCopasiVectorN < CMoiety >  &moieties = mModel->getMoieties();
		//C_INT32 noOfMoietyRows = moieties.size();
		CMoiety *moiety;
		moiety= moieties[(string)setValue];
	
		
		LineEdit1->setText(moiety->getDescription().c_str());
		LineEdit3->setText(moiety->getName().c_str());
		LineEdit2->setText(QString::number(moiety->getNumber()));
		  	
}

///end of all the functions






