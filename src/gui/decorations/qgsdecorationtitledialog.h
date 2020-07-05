/***************************************************************************
  qgsdecorationtitledialog.h
  --------------------------------------
  Date                 : November 2018
  Copyright            : (C) 2018 by Mathieu Pellerin
  Email                : nirvn dot asia at gmail dot com
 ***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#ifndef QGSDECORATIONTITLEDIALOG_H
#define QGSDECORATIONTITLEDIALOG_H

#include "ui_qgsdecorationtitledialog.h"
#include "qgis_sip.h"
#include "qgis_gui.h"

class QColor;
class QFont;

class QgsDecorationTitle;

/**
 * \ingroup gui
 * \class QgsDecorationTitleDialog
 * \brief Dialog for title map decoration
 *
 * \since QGIS 3.16
 */
class GUI_EXPORT QgsDecorationTitleDialog : public QDialog, private Ui::QgsDecorationTitleDialog
{
    Q_OBJECT

  public:
    QgsDecorationTitleDialog( QgsDecorationTitle &deco, QWidget *parent SIP_TRANSFERTHIS = nullptr );

  private slots:
    void buttonBox_accepted();
    void buttonBox_rejected();
    void mInsertExpressionButton_clicked();
    void showHelp();
    void apply();

  private:
    QgsDecorationTitle &mDeco;
};

#endif
