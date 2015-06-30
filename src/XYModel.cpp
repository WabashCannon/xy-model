
#include <QApplication>
#include "src/gui/SimulationWidget.h"

/**
 * Entry point of the program. Creates a new Qt application
 * and makes the window visible.
 */
int main( int argc, char * argv[] )
{
	QApplication app(argc, argv);
	app.setApplicationName("XY Model");
	
	QFrame* mainFrame = new SimulationWidget();
	mainFrame->show();
	
	return app.exec();
}
