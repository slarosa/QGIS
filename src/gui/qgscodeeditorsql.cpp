/***************************************************************************
    qgscodeeditorsql.cpp - A SQL editor based on QScintilla
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
#include "qgscodeeditorsql.h"

#include <QWidget>
#include <QString>
#include <QFont>
#include <QSettings>
#include <Qsci/qscilexersql.h>


QgsCodeEditorSQL::QgsCodeEditorSQL( QWidget *parent )
    : QgsCodeEditor( parent )
{
  if ( !parent )
  {
    setTitle( tr( "SQL Editor" ) );
  }
  setMarginVisible( false );
  setFoldingVisible( true );
  setSciLexerSQL();
}

QgsCodeEditorSQL::~QgsCodeEditorSQL()
{
}

void QgsCodeEditorSQL::setSciLexerSQL()
{
  QsciLexerSQL* sqlLexer = new QsciLexerSQL();

  QSettings settings;
  QFont mFont;
  QString sqlFont = settings.value( "/CodeEditor/sqlFont" ).toString();
  mFont.setFamily( sqlFont );
  mFont.setPointSize( settings.value( "/CodeEditor/sqlFontSize", 10 ).toInt() );
  sqlLexer->setDefaultFont( mFont );

  sqlLexer->setFont( mFont, 0 ); // default
  sqlLexer->setFont( mFont, 1 ); // comment
  sqlLexer->setFont( mFont, 2 ); // commentline
  sqlLexer->setFont( mFont, 4 ); // number
  sqlLexer->setFont( mFont, 5 ); // keyword
  sqlLexer->setColor( settings.value( "/CodeEditor/sqlColorDefault", QColor( Qt::black ) ).value<QColor>(), 0 );
  sqlLexer->setColor( settings.value( "/CodeEditor/sqlColorComment", QColor( Qt::gray ) ).value<QColor>(), 1 );
  sqlLexer->setColor( settings.value( "/CodeEditor/sqlColorCommentLine", QColor( Qt::gray ) ).value<QColor>(), 2 );
  sqlLexer->setColor( settings.value( "/CodeEditor/sqlColorNumber", QColor( Qt::blue ) ).value<QColor>(), 4 );
  sqlLexer->setColor( settings.value( "/CodeEditor/sqlColorKeyword", QColor( Qt::darkBlue ) ).value<QColor>(), 5 );

  setLexer( sqlLexer );
}
