/*
 * Simulation.h
 *
 *  Created on: Jun 29, 2015
 *      Author: ashton
 */

#ifndef SIMULATION_H_
#define SIMULATION_H_

#include <QThread>
#include <QImage>
#include <iostream>
#include <QMutex>
#include <QWaitCondition>
#include <QElapsedTimer>
#include <QTime>

#include <math.h>
#include <stdlib.h>
#include <iostream>

/**
 * The thread that runs the simulation and updates the
 * GUI with the results
 */
class Simulation : public QThread {
	Q_OBJECT
	
public:
	/**
	 * Constructor for the simulation thread
	 * @param size number of nodes wide to make the square simulation grid
	 */
	Simulation(int size);
	/**
	 * Deconstructor for the simulation thread
	 */
	virtual ~Simulation();
	
public slots:
	/**
	 * Slot to reset the simulation with the provided size
	 */
	void reset(int size);
	/**
	 * Slot to set the paused state of the simulation
	 * @param shouldBePaused
	 */
	void setPaused(bool shouldBePaused);
	/**
	 * Slot to set the temperature of the simulation
	 * @param temperature
	 */
	void setTemperature(double temperature);
	
private:
	/**
	 * Steps the simulation forward by one pass
	 */
	void simulate();
	/**
	 * Renders the simulation and emits it using the signal render
	 */
	void updateRender();
	
	/**
	 * Maps an angle theta to a color in a rainbow color map
	 * @param theta to map to color
	 * @return uint representing the color
	 */
	uint getColor(double theta);
	
	//For simulation
	/**
	 * Calculates the fraction of the hamiltonian due to the spin
	 * located at nodeIndex
	 * 
	 * @param nodeIndex corresponding to the node in question
	 * @return the fraction of the hamiltonian due to the node at nodeIndex
	 */
	double calcHi(int nodeIndex);
	/**
	 * Returns the angle of the neighbor specified
	 * @param nodeIndex of node whose neighbor is being queried
	 * @param ngbhIndex of the neighbor to query, int in [0,3]
	 * @return the angle of the queried neighbor
	 */
	double getNeighbor(int nodeIndex, int ngbhIndex);	
	
signals:
	/**
	 * Signal sending out the QImage representing the simulation state
	 */
	void render(const QImage &image);
	/**
	 * Signal to alert observers of the simulation state variables
	 * @param paused if the simulation is paused
	 * @param temp the temperature the simulation is using
	 * @param step the current step the simulation is on
	 */
	void setMeasurements(bool paused, double temp, int step);
	

protected:
	/**
	 * The core method of the thread, where all the computation and
	 * rendering is called from
	 */
	void run() Q_DECL_OVERRIDE;
	
private:
	//Thread variables
	/** If the simulation is paused */
	bool paused;
	/** Mutex used in maintaining thread safety */
	QMutex mutex;
	/** Wait condition used by the thread */
	QWaitCondition condition;
	
	//Simulation variables
	/** Step counter for the simulation */
	int step;
	/** How many nodes wide the simulation grid is */
	int size;
	/** The ambient temperature used in the simulation */
	double temperature;
	/** The vector of nodes in the grid */
	std::vector<double> nodes;
};

#endif /* SIMULATION_H_ */
