/*
 * SimulationRenderWidget.h
 *
 *  Created on: Jun 29, 2015
 *      Author: ashton
 */

#ifndef GUI_SIMULATIONRENDERWIDGET_H_
#define GUI_SIMULATIONRENDERWIDGET_H_

#include <QWidget>
#include <QPaintEvent>
#include <QImage>
#include <QPixmap>
#include <QPainter>

/**
 * This widget is used for receiving render signals from the simulation
 * and displaying them.
 */
class SimulationRenderWidget: public QWidget {
	Q_OBJECT
	
public slots:
	/** Slot for receiving the render signal from the simulation */
	void draw(QImage image);

protected:
	void paintEvent(QPaintEvent * /* event */);
	
private:
	/** The pixmap generated from the simulation's QImage */
	QPixmap pixmap;
};

#endif /* GUI_SIMULATIONRENDERWIDGET_H_ */
