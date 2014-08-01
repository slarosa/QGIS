/***************************************************************************
    qgscodeeditorhtml.cpp - A HTML editor based on QScintilla
     --------------------------------------
    Date                 : 20-Jul-2014
    Copyright            : (C) 2014 by Nathan Woodrow
    Email                : woodrow.nathan (at) gmail (dot) com
 ***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#include "qgsapplication.h"
#include "qgscodeeditorhtml.h"

#include <QWidget>
#include <QString>
#include <QFont>
#include <QSettings>
#include <Qsci/qscilexerhtml.h>


QgsCodeEditorHTML::QgsCodeEditorHTML( QWidget *parent )
    : QgsCodeEditor( parent )
{
  if ( !parent )
  {
    setTitle( tr( "HTML Editor" ) );
  }
  setMarginVisible( false );
  setFoldingVisible( true );
  setSciLexerHTML();
}

QgsCodeEditorHTML::~QgsCodeEditorHTML()
{
}

void QgsCodeEditorHTML::setSciLexerHTML()
{
  QsciLexerHTML* htmlLexer = new QsciLexerHTML();

  QSettings settings;
  QFont mFont;
  QString htmlFont = settings.value( "/CodeEditor/htmlFont" ).toString();
  mFont.setFamily( htmlFont );
  mFont.setPointSize( settings.value( "/CodeEditor/htmlFontSize", 10 ).toInt() );
  htmlLexer->setDefaultFont( mFont );

  htmlLexer->setFont( mFont, 0 ); // text
  htmlLexer->setFont( mFont, 1 ); // tag
  htmlLexer->setFont( mFont, 3 ); // attribute
  htmlLexer->setFont( mFont, 5 ); // htmlnumber

  setLexer( htmlLexer );
}
