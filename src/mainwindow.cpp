#include "mainwindow.h"
#include "ui_mainwindow.h"

// sphere
#include <vtkSphereSource.h>
#include <vtkPolyData.h>
#include <vtkSmartPointer.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkNamedColors.h>
#include <vtkProperty.h>

// cube
#include <vtkActor.h>
#include <vtkCamera.h>
#include <vtkCellArray.h>
#include <vtkFloatArray.h>
#include <vtkNamedColors.h>
#include <vtkNew.h>
#include <vtkPointData.h>
#include <vtkPoints.h>
#include <vtkPolyData.h>
#include <vtkPolyDataMapper.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkCubeSource.h>
// cone
#include <vtkConeSource.h>
#include <vtkNew.h>

#include <vtkActor.h>
#include <vtkNamedColors.h>
#include <vtkPolyData.h>
#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent) , 
	ui(new Ui::MainWindow) ,
	renderWindow(vtkSmartPointer<vtkGenericOpenGLRenderWindow>::New()),
	renderer(vtkSmartPointer<vtkRenderer>::New()),
	interactor(vtkSmartPointer<QVTKInteractor>::New()),
	interactorStyle(vtkSmartPointer<vtkInteractorStyle>::New())
{
	// setup UI
    ui->setupUi(this);
	// Set up the rendering
	renderWindow->AddRenderer(renderer);
	renderWindow->SetInteractor(interactor);
	ui->openGLWidget->SetRenderWindow(renderWindow);
	interactor->SetInteractorStyle(interactorStyle);
	interactor->Initialize();
	
	// Set the UI connections
	QObject::connect(ui->sphereButton, &QPushButton::clicked,
		this, &MainWindow::onDrawSphereClick);
	QObject::connect(ui->cubeButton, &QPushButton::clicked,
		this, &MainWindow::onDrawCubeClick);
	QObject::connect(ui->coneButton, &QPushButton::clicked,
		this, &MainWindow::onDrawConeClick);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onDrawSphereClick()
{
	// Create sphere
	vtkSmartPointer<vtkSphereSource> sphereSource =
		vtkSmartPointer<vtkSphereSource>::New();
	sphereSource->SetRadius(5);
	sphereSource->Update();

	// Create the actor where the sphere is rendered
	vtkSmartPointer<vtkPolyDataMapper> sphereMapper =
		vtkSmartPointer<vtkPolyDataMapper>::New();
	sphereMapper->SetInputData(sphereSource->GetOutput());

	vtkSmartPointer<vtkActor> sphere = vtkSmartPointer<vtkActor>::New();
	sphere->SetMapper(sphereMapper);

	// Add the sphere actor to the OpenGL
	renderer->RemoveAllViewProps();
	renderer->AddViewProp(sphere);
	renderer->ResetCamera();
	renderWindow->Render();
}
void MainWindow::onDrawCubeClick()
{
	// Create cube
	vtkSmartPointer<vtkCubeSource> cubeSource =
		vtkSmartPointer<vtkCubeSource>::New();
	cubeSource->Update();

	// Create the actor where the cube is rendered
	vtkSmartPointer<vtkPolyDataMapper> cubeMapper =
		vtkSmartPointer<vtkPolyDataMapper>::New();
	cubeMapper->SetInputData(cubeSource->GetOutput());

	vtkSmartPointer<vtkActor> cube = vtkSmartPointer<vtkActor>::New();
	cube->SetMapper(cubeMapper);

	// Add the sphere actor to the OpenGL
	renderer->RemoveAllViewProps();
	renderer->AddViewProp(cube);
	renderer->ResetCamera();
	renderer->GetActiveCamera()->Azimuth(30);
	renderer->GetActiveCamera()->Elevation(30);
	renderWindow->Render();


}
void MainWindow::onDrawConeClick()
{
	// Create cube
	vtkSmartPointer<vtkConeSource> coneSource =
		vtkSmartPointer<vtkConeSource>::New();
	coneSource->Update();

	// Create the actor where the cone is rendered
	vtkSmartPointer<vtkPolyDataMapper> coneMapper =
		vtkSmartPointer<vtkPolyDataMapper>::New();
	coneMapper->SetInputData(coneSource->GetOutput());

	vtkSmartPointer<vtkActor> cone = vtkSmartPointer<vtkActor>::New();
	cone->SetMapper(coneMapper);

	// Add the sphere actor to the OpenGL
	renderer->RemoveAllViewProps();
	renderer->AddViewProp(cone);
	renderer->ResetCamera();
	renderer->GetActiveCamera()->Azimuth(30);
	renderer->GetActiveCamera()->Elevation(30);
	renderWindow->Render();
}

