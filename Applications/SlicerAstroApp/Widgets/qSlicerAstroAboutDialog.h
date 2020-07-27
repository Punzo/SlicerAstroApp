#ifndef __qSlicerAstroAboutDialog_h
#define __qSlicerAstroAboutDialog_h

// Qt includes
#include <QDialog>

// CTK includes
#include <ctkPimpl.h>

// SlicerAstro includes
#include "qSlicerAstroAppExport.h"

class qSlicerAstroAboutDialogPrivate;

/// Pre-request that a qSlicerApplication has been instanced
class Q_SLICERASTRO_APP_EXPORT qSlicerAstroAboutDialog :
  public QDialog
{
  Q_OBJECT
public:
  qSlicerAstroAboutDialog(QWidget *parentWidget = nullptr);
  ~qSlicerAstroAboutDialog() override;

  Q_INVOKABLE void setLogo(const QPixmap& newLogo);

protected:
  QScopedPointer<qSlicerAstroAboutDialogPrivate> d_ptr;

private:
  Q_DECLARE_PRIVATE(qSlicerAstroAboutDialog);
  Q_DISABLE_COPY(qSlicerAstroAboutDialog);
};

#endif
