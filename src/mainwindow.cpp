#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <vtkNew.h>
#include <vtkActor.h>
#include <vtkProperty.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>

#include <sphere.h>
#include <cube.h>
#include <cone.h>

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
	ui->openGLWidget->setRenderWindow(renderWindow);
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
	Sphere sphere;
	sphere.draw(renderWindow,renderer);
}
void MainWindow::onDrawCubeClick()
{
	Cube cube;
	cube.draw(renderWindow, renderer);
}
void MainWindow::onDrawConeClick()
{
	Cone cone;
	cone.draw(renderWindow, renderer);
}

