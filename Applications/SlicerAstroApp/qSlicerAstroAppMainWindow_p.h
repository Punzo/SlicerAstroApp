#ifndef __qSlicerAstroAppMainWindow_p_h
#define __qSlicerAstroAppMainWindow_p_h

// SlicerAstro includes
#include "qSlicerAstroAppMainWindow.h"

// Slicer includes
#include "qSlicerMainWindow_p.h"

//-----------------------------------------------------------------------------
class Q_SLICERASTRO_APP_EXPORT qSlicerAstroAppMainWindowPrivate
  : public qSlicerMainWindowPrivate
{
  Q_DECLARE_PUBLIC(qSlicerAstroAppMainWindow);
public:
  typedef qSlicerMainWindowPrivate Superclass;
  qSlicerAstroAppMainWindowPrivate(qSlicerAstroAppMainWindow& object);
  virtual ~qSlicerAstroAppMainWindowPrivate();

  virtual void init();
  /// Reimplemented for custom behavior
  virtual void setupUi(QMainWindow * mainWindow);
};

#endif
