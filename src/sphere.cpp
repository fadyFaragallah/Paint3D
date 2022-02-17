#include <sphere.h>

Sphere::Sphere()
{
	shapeSource = vtkSmartPointer<vtkSphereSource>::New();
	shapeSource->Update();
	shapeMapper->SetInputData(shapeSource->GetOutput());
	shapeActor->SetMapper(shapeMapper);
}