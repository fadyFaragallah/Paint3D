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
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);


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
	vtkNew<vtkNamedColors> colors;

	// Create a sphere
	vtkNew<vtkSphereSource> sphereSource;
	sphereSource->SetCenter(0.0, 0.0, 0.0);
	sphereSource->SetRadius(5.0);
	// Make the surface smooth.
	sphereSource->SetPhiResolution(100);
	sphereSource->SetThetaResolution(100);

	vtkNew<vtkPolyDataMapper> mapper;
	mapper->SetInputConnection(sphereSource->GetOutputPort());

	vtkNew<vtkActor> actor;
	actor->SetMapper(mapper);
	actor->GetProperty()->SetColor(colors->GetColor3d("Cornsilk").GetData());
	vtkNew<vtkRenderer> renderer;
	vtkNew<vtkRenderWindow> renderWindow;
	renderWindow->SetWindowName("Sphere");
	renderWindow->AddRenderer(renderer);
	vtkNew<vtkRenderWindowInteractor> renderWindowInteractor;
	renderWindowInteractor->SetRenderWindow(renderWindow);

	renderer->AddActor(actor);
	renderer->SetBackground(colors->GetColor3d("DarkGreen").GetData());

	renderWindow->Render();
	renderWindowInteractor->Start();
}
void MainWindow::onDrawCubeClick()
{
	vtkNew<vtkNamedColors> colors;

	std::array<std::array<double, 3>, 8> pts = { {{{0, 0, 0}},
												 {{1, 0, 0}},
												 {{1, 1, 0}},
												 {{0, 1, 0}},
												 {{0, 0, 1}},
												 {{1, 0, 1}},
												 {{1, 1, 1}},
												 {{0, 1, 1}}} };
	// The ordering of the corner points on each face.
	std::array<std::array<vtkIdType, 4>, 6> ordering = { {{{0, 3, 2, 1}},
														 {{4, 5, 6, 7}},
														 {{0, 1, 5, 4}},
														 {{1, 2, 6, 5}},
														 {{2, 3, 7, 6}},
														 {{3, 0, 4, 7}}} };

	// We'll create the building blocks of polydata including data attributes.
	vtkNew<vtkPolyData> cube;
	vtkNew<vtkPoints> points;
	vtkNew<vtkCellArray> polys;
	vtkNew<vtkFloatArray> scalars;

	// Load the point, cell, and data attributes.
	for (auto i = 0ul; i < pts.size(); ++i)
	{
		points->InsertPoint(i, pts[i].data());
		scalars->InsertTuple1(i, i);
	}
	for (auto&& i : ordering)
	{
		polys->InsertNextCell(vtkIdType(i.size()), i.data());
	}

	// We now assign the pieces to the vtkPolyData.
	cube->SetPoints(points);
	cube->SetPolys(polys);
	cube->GetPointData()->SetScalars(scalars);

	// Now we'll look at it.
	vtkNew<vtkPolyDataMapper> cubeMapper;
	cubeMapper->SetInputData(cube);
	cubeMapper->SetScalarRange(cube->GetScalarRange());
	vtkNew<vtkActor> cubeActor;
	cubeActor->SetMapper(cubeMapper);

	// The usual rendering stuff.
	vtkNew<vtkCamera> camera;
	camera->SetPosition(1, 1, 1);
	camera->SetFocalPoint(0, 0, 0);

	vtkNew<vtkRenderer> renderer;
	vtkNew<vtkRenderWindow> renWin;
	renWin->AddRenderer(renderer);
	renWin->SetWindowName("Cube");

	vtkNew<vtkRenderWindowInteractor> iren;
	iren->SetRenderWindow(renWin);

	renderer->AddActor(cubeActor);
	renderer->SetActiveCamera(camera);
	renderer->ResetCamera();
	renderer->SetBackground(colors->GetColor3d("Cornsilk").GetData());

	renWin->SetSize(600, 600);

	// interact with data
	renWin->Render();
	iren->Start();


}
void MainWindow::onDrawConeClick()
{
	vtkNew<vtkNamedColors> colors;

	// Create a cone
	vtkNew<vtkConeSource> coneSource;
	coneSource->Update();

	// Create a mapper and actor
	vtkNew<vtkPolyDataMapper> mapper;
	mapper->SetInputConnection(coneSource->GetOutputPort());

	vtkNew<vtkActor> actor;
	actor->SetMapper(mapper);
	actor->GetProperty()->SetDiffuseColor(colors->GetColor3d("bisque").GetData());

	// Create a renderer, render window, and interactor
	vtkNew<vtkRenderer> renderer;
	vtkNew<vtkRenderWindow> renderWindow;
	renderWindow->AddRenderer(renderer);
	renderWindow->SetSize(640, 480);

	vtkNew<vtkRenderWindowInteractor> renderWindowInteractor;
	renderWindowInteractor->SetRenderWindow(renderWindow);
	// Add the actors to the scene
	renderer->AddActor(actor);
	renderer->SetBackground(colors->GetColor3d("Salmon").GetData());

	// Render and interact
	renderWindow->SetWindowName("Cone");
	renderWindow->Render();
	renderWindowInteractor->Start();
}

