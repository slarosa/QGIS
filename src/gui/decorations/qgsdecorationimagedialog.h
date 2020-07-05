/***************************************************************************
  qgsdecorationimagedialog.h
  --------------------------------------
  Date                 : August 2019
  Copyright            : (C) 2019 by Mathieu Pellerin
  Email                : nirvn dot asia at gmail dot com
 ***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#ifndef QGSDECORATIONIMAGEDIALOG_H
#define QGSDECORATIONIMAGEDIALOG_H

#include "ui_qgsdecorationimagedialog.h"
#include "qgis_sip.h"
#include "qgis_gui.h"

class QgsDecorationImage;

/**
 * \ingroup gui
 * \class QgsDecorationImageDialog
 * \brief Dialog for image map decoration
 *
 * \since QGIS 3.16
 */
class GUI_EXPORT QgsDecorationImageDialog : public QDialog, private Ui::QgsDecorationImageDialog
{
    Q_OBJECT

  public:
    QgsDecorationImageDialog( QgsDecorationImage &deco, QWidget *parent SIP_TRANSFERTHIS = nullptr );

  private:
    void drawImage();
    void updateEnabledColorButtons();
    void updateImagePath( const QString &imagePath );

    QgsDecorationImage &mDeco;

  private slots:
    void buttonBox_accepted();
    void buttonBox_rejected();
    void showHelp();
    void apply();

  protected:
    void resizeEvent( QResizeEvent * ) override; //overloads qwidget

};

#endif
