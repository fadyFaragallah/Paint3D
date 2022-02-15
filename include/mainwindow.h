#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include<vtkNew.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
	vtkNew<vtkRenderer> renderer;
	vtkNew<vtkRenderWindow> renderWindow;
	vtkNew<vtkRenderWindowInteractor> interactor;

public slots:
	void onDrawSphereClick();
	void onDrawCubeClick();
	void onDrawConeClick();
};
#endif // MAINWINDOW_H
