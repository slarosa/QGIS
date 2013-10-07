/***************************************************************************
    qgscodeeditor.cpp - description
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

#include "qgscodeeditor.h"

#include <QWidget>
#include <QFont>

QgsCodeEditor::QgsCodeEditor( QWidget *parent, QString title )
    : QsciScintilla( parent ), 
    mWidgetTitle( title )//, 
    //mMargin( true )
{
  setSciWidget();
}

QgsCodeEditor::~QgsCodeEditor()
{
}

void QgsCodeEditor::setSciWidget()
{
  setCaretLineVisible( true );
  setCaretLineBackgroundColor( QColor( "#fcf3ed" ) );
  setFolding( QsciScintilla::PlainFoldStyle );
  setFoldMarginColors( QColor( "#f4f4f4" ), QColor( "#f4f4f4" ) );
  // indentation
  setAutoIndent( true );
  setIndentationWidth( 4 );
  setTabIndents( true );
  setBackspaceUnindents( true );
  setTabWidth( 4 );
  // autocomplete
  setAutoCompletionThreshold( 2 );
  setAutoCompletionSource( QsciScintilla::AcsAPIs );
}

void QgsCodeEditor::addMargin()
{
  QFont marginFont( "Courier", 10 );
  setMarginLineNumbers( 1, true );
  setMarginsFont( marginFont );
  setMarginWidth( 1, "0000" );
  setMarginsForegroundColor( QColor( "#3E3EE3" ) );
  setMarginsBackgroundColor( QColor( "#f9f9f9" ) );
}
