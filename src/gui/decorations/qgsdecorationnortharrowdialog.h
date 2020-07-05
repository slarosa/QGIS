/***************************************************************************
 *   Copyright (C) 2003 by Tim Sutton                                      *
 *   tim@linfiniti.com                                                     *
 *                                                                         *
 *   This is a plugin generated from the QGIS plugin template              *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 ***************************************************************************/

#ifndef QGSNORTHARROWPLUGINGUI_H
#define QGSNORTHARROWPLUGINGUI_H

#include "ui_qgsdecorationnortharrowdialog.h"
#include "qgis_sip.h"
#include "qgis_gui.h"

class QgsDecorationNorthArrow;

/**
 * \ingroup gui
 * \class QgsDecorationNorthArrowDialog
 * \brief Dialog for north arrow map decoration
 *
 * \since QGIS 3.16
 */
class GUI_EXPORT QgsDecorationNorthArrowDialog : public QDialog, private Ui::QgsDecorationNorthArrowDialog
{
    Q_OBJECT

  public:
    QgsDecorationNorthArrowDialog( QgsDecorationNorthArrow &deco, QWidget *parent SIP_TRANSFERTHIS = nullptr );

  private:
    void updateSvgPath( const QString &svgPath );
    void drawNorthArrow();

    QgsDecorationNorthArrow &mDeco;

  private slots:
    void buttonBox_accepted();
    void buttonBox_rejected();
    void showHelp();
    void spinAngle_valueChanged( int spinAngle );
    void sliderRotation_valueChanged( int rotationValue );
    void apply();

  protected:
    void resizeEvent( QResizeEvent * ) override; //overloads qwidget
};

#endif
