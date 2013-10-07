/***************************************************************************
    qgscodeeditorpython.cpp - description
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

#include "qgsapplication.h"
#include "qgscodeeditorpython.h"

#include <QSettings>
#include <QWidget>
#include <QString>
#include <QFont>
#include <Qsci/qscilexerpython.h>


QgsCodeEditorPython::QgsCodeEditorPython( QWidget *parent ) : QgsCodeEditor( parent )
{
  if ( !parent )
  {
    setTitle( "Qscintilla2 Python Editor" );
  }
  addMargin();
  setSciLexerPython();
}

QgsCodeEditorPython::~QgsCodeEditorPython()
{
}

void QgsCodeEditorPython::setSciLexerPython()
{
  QSettings mySettings;
  QFont fontPythonMacros( mySettings.value( "pythonConsole/fontfamilytextEditor", "Monospace" ).toString() );
  int fontSizePythonMacros = mySettings.value( "pythonConsole/fontsizeEditor", 10 ).toInt();
  fontPythonMacros.setPointSize( fontSizePythonMacros );

  QsciLexerPython* pyLexer = new QsciLexerPython();
  pyLexer->setDefaultFont( fontPythonMacros );
  pyLexer->setFont( fontPythonMacros, 1 ); // comment
  pyLexer->setFont( fontPythonMacros, 3 ); // singlequotes
  pyLexer->setFont( fontPythonMacros, 4 ); // doublequotes
  pyLexer->setFont( fontPythonMacros, 6 ); // triplequotes
  pyLexer->setColor( Qt::red, 1 ); // comment color
  pyLexer->setColor( Qt::darkGreen, 5 ); // keyword color
  pyLexer->setColor( Qt::darkBlue, 15 ); // decorator color

  QsciAPIs* apis = new QsciAPIs( pyLexer );

  QString papFile = QgsApplication::pkgDataPath() + "/python/qsci_apis/pyqgis.pap";
  apis->loadPrepared( papFile );
  setLexer( pyLexer );
}

void QgsCodeEditorPython::setTitle(QString title )
{
  setWindowTitle( title );
}
