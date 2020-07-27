// SlicerAstro includes
#include "qSlicerAstroAboutDialog.h"
#include "qSlicerApplication.h"
#include "ui_qSlicerAstroAboutDialog.h"

//-----------------------------------------------------------------------------
class qSlicerAstroAboutDialogPrivate: public Ui_qSlicerAstroAboutDialog
{
public:
};

//-----------------------------------------------------------------------------
// qSlicerAstroAboutDialogPrivate methods


//-----------------------------------------------------------------------------
// qSlicerAstroAboutDialog methods
qSlicerAstroAboutDialog::qSlicerAstroAboutDialog(QWidget* parentWidget)
 :QDialog(parentWidget)
  , d_ptr(new qSlicerAstroAboutDialogPrivate)
{
  Q_D(qSlicerAstroAboutDialog);
  d->setupUi(this);

  qSlicerApplication* slicer = qSlicerApplication::application();
  d->CreditsTextBrowser->setFontPointSize(25);
  d->CreditsTextBrowser->append(slicer->applicationName());
  d->CreditsTextBrowser->setFontPointSize(11);
  d->CreditsTextBrowser->append("");
  d->CreditsTextBrowser->append(slicer->applicationVersion() + " (" + slicer->mainApplicationRepositoryRevision() + ")");
  d->CreditsTextBrowser->append("");
  QString acknowledgmentText(
    "<br /><br />"
    "SlicerAstro is an Astronomical (HI) customization of 3DSlicer.<br /><br />"
    "Developed by: Davide Punzo (www.davidepunzo.com) <br /><br />");
  d->CreditsTextBrowser->insertHtml(acknowledgmentText);
  QString librariesText(
    "Built on top of: "
    "<a href=\"https://www.slicer.org/\">3DSlicer</a>, "
    "<a href=\"http://www.vtk.org/\">VTK</a>, "
    "<a href=\"http://www.itk.org/\">ITK</a>, "
    "<a href=\"http://www.commontk.org/index.php/Main_Page\">CTK</a>, "
    "<a href=\"https://www.qt.io/\">Qt</a>, "
    "<a href=\"http://www.python.org/\">Python</a><br />");
  d->CreditsTextBrowser->insertHtml(librariesText);
  QString copyrightsText(
    "");
  d->SlicerLinksTextBrowser->insertHtml(copyrightsText);
  d->CreditsTextBrowser->moveCursor(QTextCursor::Start, QTextCursor::MoveAnchor);

  connect(d->ButtonBox, SIGNAL(rejected()), this, SLOT(close()));
}

//-----------------------------------------------------------------------------
void qSlicerAstroAboutDialog::setLogo(const QPixmap& newLogo)
{
  Q_D(qSlicerAstroAboutDialog);
  d->SlicerLabel->setPixmap(newLogo);
}

//-----------------------------------------------------------------------------
qSlicerAstroAboutDialog::~qSlicerAstroAboutDialog()
= default;
