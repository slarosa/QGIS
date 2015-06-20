/***************************************************************************
    qgssplashscreen.cpp - A class to create a splash screen.
     --------------------------------------
    Date                 : 20-Jun-2015
    Copyright            : (C) 2015 by Salvatore Larosa
    Email                : lrssvtml (at) gmail (dot) com
 ***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#include "qgssplashscreen.h"
#include "qgsapplication.h"

#include <QPainter>

QgsSplashScreen::QgsSplashScreen( const QPixmap &pixmap, QWidget *parent )
    : QSplashScreen( parent )
    , mProgress( NULL )
    , mPixmap( pixmap )
{

  QString splashPath( QgsApplication::splashPath() );
  QPixmap defaultPixmap = QPixmap( splashPath + QString( "splash.png" ) );

  !mPixmap.isNull() ? setImage( mPixmap ) : setImage( defaultPixmap );
  int heightPixmap = !mPixmap.isNull() ? mPixmap.height() : defaultPixmap.height();
  int widthPixmap = !mPixmap.isNull() ? mPixmap.width() : defaultPixmap.width();

  setCursor( Qt::BusyCursor );

  mProgress = new QProgressBar( this );
  mProgress->setGeometry( 0, heightPixmap, widthPixmap, 8 );
  mProgress->setTextVisible( false );
  mProgress->setAlignment( Qt::AlignHCenter | Qt::AlignVCenter );
  mProgress->setValue( 0 );
  mProgress->setMaximum( 100 );
  mProgress->setEnabled( true );
  mProgress->setStyleSheet( "QProgressBar{"
                            "border: 1px solid transparent;"
                            "text-align: center;"
                            "color:rgba(0,0,0,100);"
                            "border-radius: 5px;"
                            "background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1,"
                            "stop:0 rgba(182, 182, 182, 100), stop:1 rgba(209, 209, 209, 100));}"
                            "QProgressBar::chunk{"
                            "background-color: rgba(0,255,0,100);"
                            "}" );

  connect( mProgress, SIGNAL( valueChanged( int ) ), this, SLOT( progressBarUpdated( int ) ) );
}

void QgsSplashScreen::drawContents( QPainter *painter )
{
  QSplashScreen::drawContents( painter );
  mProgress->render( painter );
}

void QgsSplashScreen::progressBarUpdated( int value )
{
  Q_UNUSED( value );
  repaint();
  qApp->processEvents();
}

void QgsSplashScreen::setProgressValue( int value )
{
  mProgress->setValue( value );
}

void QgsSplashScreen::setImage( const QPixmap &pixmap )
{
  setPixmap( pixmap );
}

void QgsSplashScreen::setProgressText( const QString &text )
{
  mProgress->setFormat( text );
}
