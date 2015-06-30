/*
 * SimulationDialog.h
 *
 *  Created on: Jun 29, 2015
 *      Author: ashton
 */

#ifndef GUI_SIMULATIONDIALOG_H_
#define GUI_SIMULATIONDIALOG_H_

#include <QDialog>
#include <QFrame>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QPushButton>
#include <QLabel>
#include <QComboBox>
#include <QLineEdit>
#include <QSpacerItem>
#include <QGroupBox>
#include <QTextEdit>
#include <QAction>
#include <QVariant>

#include "src/simulation/Simulation.h"

#include <iostream>

/**
 * This widget contins the input and output fields for interacting
 * with the simulation
 */
class SimulationDialog: public QDialog {
	Q_OBJECT
	
public:
	/**
	 * Constructs a new SimulationDialog linked to the
	 * given simulation.
	 * @param simulation to connect dialog with
	 */
	SimulationDialog(Simulation* simulation);
	
	/**
	 * Creates the controls section of the dialog
	 * @return the QGroupBox containing this controls
	 */
	QGroupBox* createControls();
	/**
	 * Creates the inputs section of the dialog
	 * @return the QGroupBox containing this inputs
	 */
	QGroupBox* createInputs();
	/**
	 * Creates the output section of the dialog
	 * @return the QGroupBox containing this outputs
	 */
	QGroupBox* createOutputs();
	
public slots:
	/** Slot for receiving updates on the simulation state parameters */
	void setMeasurements(bool paused, double temp, int step);
	
private slots:
	/** Slot for receiving the togglePause command from playButton */
	void togglePaused();
	/** Slot for receiving the reset command */
	void reset();
	/** Slot for receiving the set temperature command from tempField */
	void setTemperature();
	
private:
	/** The simulation that this dialog is linked to */
	Simulation* simulation;
	/** The paused state that the dialog wants for the simulation */
	bool paused = false;
	
	//Output fields
	/** Field that displays the simulation's step counter */
	QLineEdit* stepField;
	
	//Input widgets
	/** The field that is used to change the simulation's temperature */
	QLineEdit* tempField;
	/** The selector used for changing simulation size */
	QComboBox* sizeSelector;
	/** The button that is used to play/pause the simulation */
	QPushButton* playButton;
	
};

#endif /* GUI_SIMULATIONDIALOG_H_ */
