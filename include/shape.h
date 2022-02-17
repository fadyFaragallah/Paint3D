#pragma once

#include <vtkSmartPointer.h>
#include <vtkPolyDataAlgorithm.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>


#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkGenericOpenGLRenderWindow.h>

#include <vtkCamera.h>

class Shape
{
protected:
	vtkSmartPointer<vtkPolyDataAlgorithm> shapeSource;
	vtkSmartPointer<vtkPolyDataMapper> shapeMapper;
	vtkSmartPointer<vtkActor> shapeActor;
public:
	Shape() :shapeMapper(vtkSmartPointer<vtkPolyDataMapper>::New()), shapeActor(vtkSmartPointer<vtkActor>::New())
	{

	}
	void draw(vtkSmartPointer<vtkGenericOpenGLRenderWindow> renderWindow, vtkSmartPointer<vtkRenderer> renderer);
};