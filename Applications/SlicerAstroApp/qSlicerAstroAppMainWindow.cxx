/* Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
   file LICENSE.  */

// Qt includes
#include <QDebug>
#include <QDesktopWidget>
#include <QMessageBox>
#include <QObject>
#include <QSettings>

// CTK includes
#include <ctkMenuComboBox.h>

// VTK includes
#include <vtkCleanPolyData.h>
#include <vtkCollection.h>
#include <vtkCurvatures.h>
#include <vtkImageData.h>
#include <vtkLookupTable.h>
#include <vtkPointData.h>
#include <vtkPolyDataNormals.h>
#include <vtkRenderer.h>

// Slicer includes
#include "qSlicerAbstractModule.h"
#include "qSlicerApplication.h"
#include "qSlicerLayoutManager.h"
#include "qSlicerModuleSelectorToolBar.h"
#include "qSlicerModulesMenu.h"
#include "qSlicerModuleManager.h"
#include "vtkSlicerApplicationLogic.h"

// qMRMLWidgets include
#include "qMRMLThreeDViewControllerWidget.h"
#include "qMRMLThreeDWidget.h"
#include "qMRMLThreeDView.h"

// SlicerAstro includes
#include "qSlicerAstroAppMainWindow_p.h"
#include "Widgets/qSlicerAstroAboutDialog.h"

// MRML includes
#include "vtkMRMLCameraNode.h"
#include "vtkMRMLColorTableNode.h"
#include "vtkMRMLDisplayNode.h"
#include "vtkMRMLModelNode.h"
#include "vtkMRMLModelDisplayNode.h"
#include "vtkMRMLModelStorageNode.h"
#include "vtkMRMLScalarVolumeNode.h"
#include "vtkMRMLScene.h"
#include "vtkMRMLSelectionNode.h"

//-----------------------------------------------------------------------------
// qSlicerAstroAppMainWindowPrivate methods

qSlicerAstroAppMainWindowPrivate::qSlicerAstroAppMainWindowPrivate(qSlicerAstroAppMainWindow& object)
  : Superclass(object)
{
}

//-----------------------------------------------------------------------------
qSlicerAstroAppMainWindowPrivate::~qSlicerAstroAppMainWindowPrivate()
{
}

//-----------------------------------------------------------------------------
void qSlicerAstroAppMainWindowPrivate::init()
{
#if (QT_VERSION >= QT_VERSION_CHECK(5, 7, 0))
  QApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);
#endif
  this->Superclass::init();
}

//-----------------------------------------------------------------------------
void qSlicerAstroAppMainWindowPrivate::setupUi(QMainWindow * mainWindow)
{
  Q_Q(qSlicerAstroAppMainWindow);

  this->Superclass::setupUi(mainWindow);

  //----------------------------------------------------------------------------
  // Add Help action
  //----------------------------------------------------------------------------
  this->menubar->removeAction(this->HelpMenu->menuAction());
  QAction *SlicerAstroHelpAction = new QAction();
  SlicerAstroHelpAction->setObjectName(QString::fromUtf8("SlicerAstroHelpMenu"));
  SlicerAstroHelpAction->setText("&Help");
  this->menubar->addAction(SlicerAstroHelpAction);

  q->connect(SlicerAstroHelpAction, SIGNAL(triggered()),
             q, SLOT(onHelpSlicerAstroTriggered()));

  //----------------------------------------------------------------------------
  // Configure
  //----------------------------------------------------------------------------
  mainWindow->setWindowIcon(QIcon(":/Icons/Medium/DesktopIcon.png"));
  QPixmap logo(":/Icons/Large/FullLogo.png");
  this->LogoLabel->setAlignment(Qt::AlignCenter); // XXX Synx with template ?
  this->LogoLabel->setPixmap(logo);

  // To see any effect of changes over here in the application first delete the .ini file pointed by
  // --settings-path option of the project executable.

  // Hide the toolbars
  this->MainToolBar->setVisible(true);
  this->ModuleSelectorToolBar->setVisible(true);
  this->ModuleToolBar->setVisible(true);
  this->ViewToolBar->setVisible(true);
  this->MouseModeToolBar->setVisible(true);
  this->CaptureToolBar->setVisible(true);
  this->ViewersToolBar->setVisible(true);
  this->DialogToolBar->setVisible(false);

  // Hide the modules panel
  this->PanelDockWidget->setVisible(true);
  this->DataProbeCollapsibleWidget->setCollapsed(false);
  this->DataProbeCollapsibleWidget->setVisible(true);
  this->StatusBar->setVisible(true);

  qSlicerModulesMenu* modulesMenu = this->ModuleSelectorToolBar->modulesMenu();
  modulesMenu->setTopLevelCategoryOrder(
        QStringList()
        << "Astronomy"
        << "Informatics"
        << "Registration"
        << "Utilities"
        );
}

//-----------------------------------------------------------------------------
// qSlicerAstroAppMainWindow methods

//-----------------------------------------------------------------------------
qSlicerAstroAppMainWindow::qSlicerAstroAppMainWindow(QWidget* windowParent)
  : Superclass(new qSlicerAstroAppMainWindowPrivate(*this), windowParent)
{
  Q_D(qSlicerAstroAppMainWindow);
  d->init();
}

//-----------------------------------------------------------------------------
qSlicerAstroAppMainWindow::qSlicerAstroAppMainWindow(
  qSlicerAstroAppMainWindowPrivate* pimpl, QWidget* windowParent)
  : Superclass(pimpl, windowParent)
{
  // init() is called by derived class.
}

//-----------------------------------------------------------------------------
qSlicerAstroAppMainWindow::~qSlicerAstroAppMainWindow()
{
}

//-----------------------------------------------------------------------------
void qSlicerAstroAppMainWindow::onHelpSlicerAstroTriggered()
{
  qSlicerAstroAboutDialog about(this);
  about.setLogo(QPixmap(":/Icons/XLarge/DesktopIcon.png"));

  QString acknowledgmentText(
      "SlicerAstro.<br /><br />");

  about.exec();
}

//-----------------------------------------------------------------------------
void qSlicerAstroAppMainWindow::show()
{
  // Show
  this->Superclass::show();
}
