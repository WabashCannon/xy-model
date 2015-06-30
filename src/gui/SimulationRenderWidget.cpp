/*
 * SimulationRenderWidget.cpp
 *
 *  Created on: Jun 29, 2015
 *      Author: ashton
 */

#include "SimulationRenderWidget.h"

void SimulationRenderWidget::draw(QImage image){
	QImage scaledImage = image.scaled(width(), height(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
	pixmap = QPixmap::fromImage(scaledImage);
	update();
}

void SimulationRenderWidget::paintEvent(QPaintEvent * /* event */){
	QPainter painter(this);
	painter.fillRect(rect(), Qt::black);

	if (pixmap.isNull()) {
		painter.setPen(Qt::white);
		painter.drawText(rect(), Qt::AlignCenter, tr("Click Play"));
		return;
	}
	
	painter.drawPixmap( QPoint(0,0), pixmap);
}

