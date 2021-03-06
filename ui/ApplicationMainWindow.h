#pragma once

#include <QMainWindow>
#include <memory>

class ApplicationManager;
class QOpenGLWidget;
namespace Ui{ class MainWindow;}

class ApplicationMainWindow : public QMainWindow
{
    Q_OBJECT
public:
    ApplicationMainWindow(QWidget* fParent = nullptr, Qt::WindowFlags fFlags = 0);
    virtual ~ApplicationMainWindow();

private:
    enum class ToolsTabsNames: int
    {
        SURFACS_LIST_TAB = 0
    };

    QOpenGLWidget* mRenderingWidget;
    std::unique_ptr<ApplicationManager> mApplicationManager;

    Ui::MainWindow* mUi;
};
