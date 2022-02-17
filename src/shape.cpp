#include <shape.h>

void Shape::draw(vtkSmartPointer<vtkGenericOpenGLRenderWindow> renderWindow, vtkSmartPointer<vtkRenderer> renderer)
{
	// drawing steps
	renderer->RemoveAllViewProps();
	renderer->AddViewProp(shapeActor);
	renderer->ResetCamera();
	renderer->GetActiveCamera()->Azimuth(30);
	renderer->GetActiveCamera()->Elevation(30);
	renderWindow->Render();
}