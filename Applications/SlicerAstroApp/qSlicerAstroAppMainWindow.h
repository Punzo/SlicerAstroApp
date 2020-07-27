#ifndef __qSlicerAstroAppMainWindow_h
#define __qSlicerAstroAppMainWindow_h

// SlicerAstro includes
#include "qSlicerAstroAppExport.h"
class qSlicerAstroAppMainWindowPrivate;

// Slicer includes
#include "qSlicerMainWindow.h"

// CTK includes
#include <ctkVTKObject.h>

// VTK includes
#include <vtkSmartPointer.h>

class Q_SLICERASTRO_APP_EXPORT qSlicerAstroAppMainWindow : public qSlicerMainWindow
{
  Q_OBJECT
  QVTK_OBJECT
public:
  typedef qSlicerMainWindow Superclass;

  qSlicerAstroAppMainWindow(QWidget *parent=0);
  virtual ~qSlicerAstroAppMainWindow();

public:
  virtual void show();

public slots:
  void onHelpSlicerAstroTriggered();

protected:
  qSlicerAstroAppMainWindow(qSlicerAstroAppMainWindowPrivate* pimpl, QWidget* parent);

private:
  Q_DECLARE_PRIVATE(qSlicerAstroAppMainWindow);
  Q_DISABLE_COPY(qSlicerAstroAppMainWindow);
};

#endif
