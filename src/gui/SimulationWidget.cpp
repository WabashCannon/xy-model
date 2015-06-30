/*
 * SimulationWidget.cpp
 *
 *  Created on: Jun 29, 2015
 *      Author: ashton
 */

#include "SimulationWidget.h"

SimulationWidget::SimulationWidget() {
	//Create the simulation
	Simulation* simulation = new Simulation(128);
	
	//Create the layout
	QLayout* layout = new QHBoxLayout();
	setLayout(layout);
	
	//Create the simulation render widget
	SimulationRenderWidget* renderWidget = new SimulationRenderWidget();
	renderWidget->setFixedSize(512, 512);
	layout->addWidget(renderWidget);
	
	//Create the simulation dialog widget
	QDialog* dialog = new SimulationDialog(simulation);
	layout->addWidget(dialog);
	
	//start the simulation
	simulation->start();
	
	//Connect the 
	connect(simulation, SIGNAL(render(QImage)), renderWidget, SLOT(draw(QImage)));
	
}

