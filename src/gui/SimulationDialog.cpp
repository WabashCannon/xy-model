/*
 * SimulationDialog.cpp
 *
 *  Created on: Jun 29, 2015
 *      Author: ashton
 */

#include "SimulationDialog.h"

SimulationDialog::SimulationDialog(Simulation* simulation) {
	
	this->simulation = simulation;
	connect(simulation, SIGNAL(setMeasurements(bool, double, int)), 
				this, SLOT(setMeasurements(bool, double, int)) );
	
	QGroupBox* controlsFrame = createControls();
	QGroupBox* inputsFrame = createInputs();
	QGroupBox* outputsFrame = createOutputs();
	
	QVBoxLayout* layout = new QVBoxLayout(this);
	layout->addWidget(controlsFrame);
	layout->addWidget(inputsFrame);
	layout->addWidget(outputsFrame);
	layout->addSpacerItem( new QSpacerItem(
			5, 5, QSizePolicy::Expanding, QSizePolicy::Expanding));

}

QGroupBox* SimulationDialog::createControls(){
	QGroupBox* controllsFrame = new QGroupBox( tr("Controls") );
	
	QHBoxLayout* layout = new QHBoxLayout(controllsFrame);
	
	playButton = new QPushButton( tr("Play") );
	connect( playButton, SIGNAL(clicked()) , 
				this, SLOT(togglePaused()) );
	
	QPushButton* resetButton = new QPushButton( tr("Reset") );
	connect( resetButton, SIGNAL(released()),
			this, SLOT(reset()));
	
	layout->addWidget(playButton);
	layout->addWidget(resetButton);
	
	return controllsFrame;
}

QGroupBox* SimulationDialog::createInputs(){
	QGroupBox* inputsFrame = new QGroupBox( tr("Parameters") );
	
	QFormLayout* layout = new QFormLayout(inputsFrame);
	
	QLabel* sizeLabel = new QLabel( tr("Size") );
	sizeSelector = new QComboBox();
	int sizes [] = {8, 16, 32, 64, 128, 256, 512};
	for ( int size : sizes ){
		QString itemLabel = "%1 x %1";
		sizeSelector->addItem( itemLabel.arg(size), QVariant(size) );
		
		if ( size == 128 ){
			sizeSelector->setCurrentIndex(sizeSelector->count()-1);
		}
	}
	connect( sizeSelector, SIGNAL(currentIndexChanged(int)),
			this, SLOT(reset()) );
	layout->addRow(sizeLabel, sizeSelector);
	
	QLabel* tempLabel = new QLabel( tr("Temperature (k)") );
	tempField = new QLineEdit();
	connect( tempField, SIGNAL(returnPressed()),
			this, SLOT(setTemperature()) );
	connect( tempField, SIGNAL(editingFinished()),
			this, SLOT(setTemperature()) );
	layout->addRow(tempLabel, tempField);
	
	reset();
	return inputsFrame;
}

QGroupBox* SimulationDialog::createOutputs(){
	QGroupBox* outputFrame = new QGroupBox( tr("Measurements") );
	
	QGridLayout* layout = new QGridLayout(outputFrame);
	
	QLabel* stepLabel = new QLabel( "Step: ");
	stepField = new QLineEdit();
	stepField->setReadOnly(true);
	
	layout->addWidget(stepLabel, 0, 0);
	layout->addWidget(stepField, 0, 1);
	
	return outputFrame;
}

void SimulationDialog::setMeasurements(bool paused, double temp, int step){
	//Update play-pause button
	this->paused = paused;
	playButton->setChecked(paused);
	if ( paused ){
		playButton->setText("Play");
	} else {
		playButton->setText("Pause");
	}
	//Update Temperature field if it is not focused
	if ( !tempField->hasFocus() ){
		tempField->setText( QString("%1").arg(temp) );
	}
	//Update measurement fields
	stepField->setText( QString("%1").arg(step) );
}

void SimulationDialog::togglePaused(){
	simulation->setPaused(!paused);
}

void SimulationDialog::setTemperature(){
	simulation->setTemperature(tempField->text().toDouble());
}

void SimulationDialog::reset(){
	QVariant sizeVariant = sizeSelector->currentData();
	int size = sizeVariant.toInt();
	
	simulation->reset(size);
}


