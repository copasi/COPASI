#include <qmainwindow.h>
#include <qtoolbar.h>

#include "copasi.h"
#include "model/model.h"

class MyTreeAndListWidget;
class CopasiUI3Window : public QMainWindow
{
	Q_OBJECT
public:
	CopasiUI3Window( QWidget* parent = 0, const char* name = 0, WFlags f = WType_TopLevel );

protected:
	MyTreeAndListWidget *mtlw;
	QToolBar *tbMain;

	CModel mModel;

protected slots:
	void slotFileOpen();
	void slotFileSave();
	void slotFilePrint();

};

