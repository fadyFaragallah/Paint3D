#include <cone.h>

Cone::Cone()
{
	shapeSource = vtkSmartPointer<vtkConeSource>::New();
	shapeSource->Update();
	shapeMapper->SetInputData(shapeSource->GetOutput());
	shapeActor->SetMapper(shapeMapper);
}