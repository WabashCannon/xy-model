/*
 * SimulationWidget.h
 *
 *  Created on: Jun 29, 2015
 *      Author: ashton
 */

#ifndef GUI_SIMULATIONWIDGET_H_
#define GUI_SIMULATIONWIDGET_H_

#include "src/gui/SimulationDialog.h"
#include "src/gui/SimulationRenderWidget.h"
#include "src/simulation/Simulation.h"

#include <QFrame>
#include <QPalette>
#include <QHBoxLayout>
#include <QSizePolicy>

/**
 * This widget creates two child widgets, the SimulationRenderWidget and
 * the SimulationDialog widget. Additionally, it creates a new Simulation
 * and linkes it with it's children
 */
class SimulationWidget : public QFrame {
public:
	/**
	 * Construct a new simulation widget
	 */
	SimulationWidget();
};

#endif /* GUI_SIMULATIONWIDGET_H_ */
