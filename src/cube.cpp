#include <cube.h>

Cube::Cube()
{
	shapeSource = vtkSmartPointer<vtkCubeSource>::New();
	shapeSource->Update();
	shapeMapper->SetInputData(shapeSource->GetOutput());
	shapeActor->SetMapper(shapeMapper);
}