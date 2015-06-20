/***************************************************************************
    qgssplashscreen.h - A class to create a splash screen.
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

#ifndef QGSSPLASHSCREEN_H
#define QGSSPLASHSCREEN_H

#include <QSplashScreen>
#include <QProgressBar>

class QWidget;

/** \ingroup gui
 * A class to create a splash screen.
 * \note added in 2.9
 */
class GUI_EXPORT QgsSplashScreen : public QSplashScreen
{
    Q_OBJECT

  public:
    explicit QgsSplashScreen( const QPixmap &pixmap = QPixmap(), QWidget *parent = 0 );
    QProgressBar *mProgress;

    void setProgressValue( int value );
    void setImage( const QPixmap &pixmap );
    void setProgressText( const QString &text );

  public slots:
    void progressBarUpdated( int value );

  protected:
    void drawContents( QPainter *painter );

    const QPixmap &mPixmap;

};

#endif
