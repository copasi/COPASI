#include <qmainwindow.h>


class MyTreeAndListWidget;

class CopasiUI3Window : public QMainWindow
{
	Q_OBJECT
public:
	CopasiUI3Window( QWidget* parent = 0, const char* name = 0, WFlags f = WType_TopLevel );

protected:
	MyTreeAndListWidget *mtlw;
};

