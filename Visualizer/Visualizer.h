#ifndef Visualizer_Visualizer_H_
#define Visualizer_Visualizer_H_
#pragma once

#include "Box.h"

#include <iostream>
#include <memory>
namespace Visualizer{
	class Visualizer{
	public:
		Visualizer(int &argc, char* argv[]);
		
		void go() const;

		void draw() const;
		void setData( std::unique_ptr<Box> displayData );

		static Visualizer* currentVisualizer;

	private:
		void setup();
		void checkGL() const;

		int winId;
		std::unique_ptr<Box> displayData;
	};
}

#endif
