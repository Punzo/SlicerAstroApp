// SlicerAstro includes
#include "qSlicerAstroAppMainWindow.h"
#include "Widgets/qAppStyle.h"

// Qt includes
#include <QAction>
#include <QSettings>

// CTK includes
#include <ctkAxesWidget.h>
#include <ctkCollapsibleButton.h>

// VTK includes
#include <vtkCollection.h>

// Slicer includes
#include <qMRMLThreeDWidget.h>
#include <qMRMLThreeDViewControllerWidget.h>
#include <qSlicerAbstractCoreModule.h>
#include <qSlicerAbstractModuleRepresentation.h>
#include <qSlicerApplicationHelper.h>
#include <qSlicerLayoutManager.h>
#include <qSlicerModuleManager.h>
#include <qSlicerModulePanel.h>

// MRML includes
#include <vtkMRMLLayoutNode.h>
#include <vtkMRMLModelNode.h>
#include <vtkMRMLScene.h>
#include <vtkMRMLSliceNode.h>
#include <vtkMRMLViewNode.h>

// Logic includes
#include <vtkMRMLLayoutLogic.h>

namespace
{

//----------------------------------------------------------------------------
int SlicerAppMain(int argc, char* argv[])
{
  typedef qSlicerAstroAppMainWindow SlicerMainWindowType;

  qSlicerApplicationHelper::preInitializeApplication(argv[0], new qAppStyle);

  qSlicerApplication app(argc, argv);
  if (app.returnCode() != -1)
    {
    return app.returnCode();
    }

  QApplication::setStyle(new qAppStyle);

  QScopedPointer<QSplashScreen> splashScreen;
  QScopedPointer<SlicerMainWindowType> window;

  qSlicerApplicationHelper::postInitializeApplication<SlicerMainWindowType>(
        app, splashScreen, window);

  if(!window.isNull())
    {
    QString windowTitle = QString("%1 %2").arg(Slicer_MAIN_PROJECT_APPLICATION_NAME).arg(Slicer_MAIN_PROJECT_VERSION_FULL);
    window->setWindowTitle(windowTitle);

    // Setup Sample Data module icon
    if(!app.mrmlScene())
      {
      return 0;
      }

    // Open Help & acknowledgment
    qSlicerModulePanel* modulePanel = window->findChild<qSlicerModulePanel*>("ModulePanel");
    ctkCollapsibleButton* helpButton = modulePanel->findChild<ctkCollapsibleButton*>("HelpCollapsibleButton");
    helpButton->setCollapsed(true);

    qSlicerLayoutManager *layoutManager = qSlicerApplication::application()->layoutManager();

    // Use Custom settings
    bool axisLables3DVisibility = QSettings().value("Default3DView/AxisLabelsVisibility").toBool();
    bool box3DVisibility = QSettings().value("Default3DView/BoxVisibility").toBool();
    QString orientaionMarkerType3D = QSettings().value("Default3DView/OrientationMarkerType").toString();
    QString orientaionMarkerSize3D = QSettings().value("Default3DView/OrientationMarkerSize").toString();
    QString rulerType3D = QSettings().value("Default3DView/RulerType").toString();
    bool UseDepthPeeling = QSettings().value("Default3DView/UseDepthPeeling").toBool();
    bool UseOrthographicProjection = QSettings().value("Default3DView/UseOrthographicProjection").toBool();

    vtkSmartPointer<vtkCollection> viewNodes = vtkSmartPointer<vtkCollection>::Take
        (app.mrmlScene()->GetNodesByClass("vtkMRMLViewNode"));
    for (int viewIndex = 0; viewIndex < viewNodes->GetNumberOfItems(); ++viewIndex)
      {
      vtkMRMLViewNode *viewNode =
        vtkMRMLViewNode::SafeDownCast(viewNodes->GetItemAsObject(viewIndex));
      if (!viewNode)
        {
        continue;
        }

      viewNode->SetOrientationMarkerSize(viewNode->GetOrientationMarkerSizeFromString(orientaionMarkerSize3D.toStdString().c_str()));
      viewNode->SetOrientationMarkerType(viewNode->GetOrientationMarkerTypeFromString(orientaionMarkerType3D.toStdString().c_str()));
      viewNode->SetRulerType(viewNode->GetRulerTypeFromString(rulerType3D.toStdString().c_str()));
      viewNode->SetAxisLabelsVisible(axisLables3DVisibility);
      viewNode->SetBoxVisible(box3DVisibility);
      viewNode->SetUseDepthPeeling(UseDepthPeeling);
      if (UseOrthographicProjection)
        {
        viewNode->SetRenderMode(vtkMRMLViewNode::Orthographic);
        }
      else
        {
        viewNode->SetRenderMode(vtkMRMLViewNode::Perspective);
        }
      }

    vtkMRMLViewNode *viewNode =
      vtkMRMLViewNode::SafeDownCast(app.mrmlScene()->GetDefaultNodeByClass("vtkMRMLViewNode"));
    if (viewNode)
      {
      viewNode->SetOrientationMarkerSize(viewNode->GetOrientationMarkerSizeFromString(orientaionMarkerSize3D.toStdString().c_str()));
      viewNode->SetOrientationMarkerType(viewNode->GetOrientationMarkerTypeFromString(orientaionMarkerType3D.toStdString().c_str()));
      viewNode->SetRulerType(viewNode->GetRulerTypeFromString(rulerType3D.toStdString().c_str()));
      viewNode->SetAxisLabelsVisible(axisLables3DVisibility);
      viewNode->SetBoxVisible(box3DVisibility);
      viewNode->SetUseDepthPeeling(UseDepthPeeling);
      if (UseOrthographicProjection)
        {
        viewNode->SetRenderMode(vtkMRMLViewNode::Orthographic);
        }
      else
        {
        viewNode->SetRenderMode(vtkMRMLViewNode::Perspective);
        }
      }

    QString orientaionMarkerSize2D = QSettings().value("DefaultSliceView/OrientationMarkerSize").toString();
    QString orientaionMarkerType2D = QSettings().value("DefaultSliceView/OrientationMarkerType").toString();
    QString rulerType2D = QSettings().value("DefaultSliceView/RulerType").toString();

    vtkSmartPointer<vtkCollection> sliceNodes = vtkSmartPointer<vtkCollection>::Take
        (app.mrmlScene()->GetNodesByClass("vtkMRMLSliceNode"));
    for (int sliceIndex = 0; sliceIndex < sliceNodes->GetNumberOfItems(); ++sliceIndex)
      {
      vtkMRMLSliceNode *sliceNode =
        vtkMRMLSliceNode::SafeDownCast(sliceNodes->GetItemAsObject(sliceIndex));
      if (!sliceNode)
        {
        continue;
        }
      sliceNode->SetOrientationMarkerSize(sliceNode->GetOrientationMarkerSizeFromString(orientaionMarkerSize2D.toStdString().c_str()));
      sliceNode->SetOrientationMarkerType(sliceNode->GetOrientationMarkerTypeFromString(orientaionMarkerType2D.toStdString().c_str()));
      sliceNode->SetRulerType(sliceNode->GetRulerTypeFromString(rulerType2D.toStdString().c_str()));
     }

    vtkMRMLSliceNode *sliceNode =
      vtkMRMLSliceNode::SafeDownCast(app.mrmlScene()->GetDefaultNodeByClass("vtkMRMLSliceNode"));
    if (sliceNode)
      {
      sliceNode->SetOrientationMarkerSize(sliceNode->GetOrientationMarkerSizeFromString(orientaionMarkerSize2D.toStdString().c_str()));
      sliceNode->SetOrientationMarkerType(sliceNode->GetOrientationMarkerTypeFromString(orientaionMarkerType2D.toStdString().c_str()));
      sliceNode->SetRulerType(sliceNode->GetRulerTypeFromString(rulerType2D.toStdString().c_str()));
      }

    layoutManager->setLayout(vtkMRMLLayoutNode::SlicerLayoutConventionalWidescreenView);
    }

  return app.exec();
}

} // end of anonymous namespace

#include "qSlicerApplicationMainWrapper.cxx"
