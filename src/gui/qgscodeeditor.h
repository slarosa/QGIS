/***************************************************************************
    qgscodeeditor.h - description
     --------------------------------------
    Date                 : 06-Oct-2013
    Copyright            : (C) 2013 by Salvatore Larosa
    Email                : lrssvtml (at) gmail (dot) com
 ***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#ifndef QGSCODEEDITOR_H
#define QGSCODEEDITOR_H

#include <QString>
// qscintilla includes
#include <Qsci/qsciapis.h>

class QWidget;

/** \ingroup gui
 * A text editor based on QScintilla2.
 * \note added in 2.1
 */
class GUI_EXPORT QgsCodeEditor : public QsciScintilla
{
    Q_OBJECT

  public:
    QgsCodeEditor( QWidget *parent = 0, QString title = "" );
    ~QgsCodeEditor();

    void addMargin();

  private:

    void setSciWidget();

    QString mWidgetTitle;
    //bool mMargin;
};

#endif
