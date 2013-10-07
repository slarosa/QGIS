/***************************************************************************
    qgscodeeditorpython.h - description
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

#ifndef QGSCODEEDITORPYTHON_H
#define QGSCODEEDITORPYTHON_H

#include "qgscodeeditor.h"


/** \ingroup gui
 * A text editor based on QScintilla2. Adds syntax highlghiting and
 * code autocompletion.
 * \note added in 2.1
 */
class GUI_EXPORT QgsCodeEditorPython : public QgsCodeEditor
{
    Q_OBJECT

  public:
    QgsCodeEditorPython( QWidget *parent = 0 );
    ~QgsCodeEditorPython();

    void setTitle( QString );

  private:
    //QgsCodeEditor *mSciWidget;
    //QWidget *mWidget;
    void setSciLexerPython();

};

#endif
