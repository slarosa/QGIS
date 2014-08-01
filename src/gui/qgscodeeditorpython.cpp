/***************************************************************************
    qgscodeeditorpython.cpp  - A Python editor based on QScintilla
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
#include "qgslogger.h"

#include <QWidget>
#include <QString>
#include <QFont>
#include <QFileInfo>
#include <QMessageBox>
#include <QSettings>
#include <QTextStream>
#include <Qsci/qscilexerpython.h>

QgsCodeEditorPython::QgsCodeEditorPython( QWidget *parent, const QList<QString> &filenames )
    : QgsCodeEditor( parent )
    , mAPISFilesList( filenames )
{
  if ( !parent )
  {
    setTitle( tr( "Python Editor" ) );
  }
  setSciLexerPython();
}

QgsCodeEditorPython::~QgsCodeEditorPython()
{
}

void QgsCodeEditorPython::setSciLexerPython()
{
  // current line
  setCaretWidth( 2 );

  setEdgeMode( QsciScintilla::EdgeLine );
  setEdgeColumn( 80 );
  setEdgeColor( QColor( "#FF0000" ) );

  setWhitespaceVisibility( QsciScintilla::WsVisibleAfterIndent );

  QSettings settings;
  bool monospaceFont = settings.value( "/CodeEditor/pyMonospaceFont", false ).toBool();
  QFont mFont;
  QString pyFont = settings.value( "/CodeEditor/pyFont" ).toString();
  if ( !monospaceFont )
  {
    mFont.setFamily( pyFont );
  }
  else
  {
    mFont = getMonospaceFont();
  }

  mFont.setPointSize( settings.value( "/CodeEditor/pyFontSize", 10 ).toInt() );

  QsciLexerPython* pyLexer = new QsciLexerPython();
  pyLexer->setDefaultFont( mFont );
  pyLexer->setFont( mFont, 1 ); // comment
  pyLexer->setFont( mFont, 3 ); // singlequotes
  pyLexer->setFont( mFont, 4 ); // doublequotes
  pyLexer->setFont( mFont, 6 ); // triplequotes
  pyLexer->setColor( Qt::red, 1 ); // comment color
  pyLexer->setColor( Qt::darkGreen, 5 ); // keyword color
  pyLexer->setColor( Qt::darkBlue, 15 ); // decorator color

  QsciAPIs* apis = new QsciAPIs( pyLexer );

  // check if the file is a prepared apis file.
  //QString mPapFileName = QFileInfo( mAPISFilesList[0] ).fileName();
  //QString isPapFile = mPapFileName.right( 3 );
  //QgsDebugMsg( QString( "file extension: %1" ).arg( isPapFile ) );

  if ( mAPISFilesList.isEmpty() )
  {
    mPapFile = QgsApplication::pkgDataPath() + "/python/qsci_apis/pyqgis.pap";
    apis->loadPrepared( mPapFile );
  }
  else if ( mAPISFilesList.length() == 1 && mAPISFilesList[0].right( 3 ) == "pap" )
  {
    if ( !QFileInfo( mAPISFilesList[0] ).exists() )
    {
      QgsDebugMsg( QString( "The apis file %1 not found" ).arg( mAPISFilesList[0] ) );
      return;
    }
    mPapFile = mAPISFilesList[0];
    apis->loadPrepared( mPapFile );
  }
  else
  {
    for ( int i = 0; i < mAPISFilesList.size(); i++ )
    {
      if ( !QFileInfo( mAPISFilesList[i] ).exists() )
      {
        QgsDebugMsg( QString( "The apis file %1 was not found" ).arg( mAPISFilesList[i] ) );
        return;
      }
      else
      {
        apis->load( mAPISFilesList[i] );
      }
    }
    apis->prepare();
    pyLexer->setAPIs( apis );
  }
  setLexer( pyLexer );

  setMarginVisible( true );
  setFoldingVisible( true );
}


void QgsCodeEditorPython::loadAPIs( const QList<QString> &filenames )
{
  mAPISFilesList = filenames;
  //QgsDebugMsg( QString( "The apis files: %1" ).arg( mAPISFilesList[0] ) );
  setSciLexerPython();
}

bool QgsCodeEditorPython::loadScript( const QString &script )
{
  QgsDebugMsg( QString( "The script file: %1" ).arg( script ) );
  QFile file( script );
  if ( !file.open( QIODevice::ReadOnly ) )
  {
    return false;
  }

  QTextStream in( &file );

  setText( in.readAll() );
  file.close();

  setSciLexerPython();
  return true;
}
