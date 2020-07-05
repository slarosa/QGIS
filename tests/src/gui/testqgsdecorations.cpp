/***************************************************************************
  testqgsdecorations.cpp

 ---------------------
 begin                : May 2020
 copyright            : (C) 2020 by Salvatore Larosa
 email                : lrssvtml at gmail dot com
 ***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#include "qgstest.h"

#include "qgsapplication.h"
#include "qgsdecorationitem.h"
#include "qgsdecorationtitle.h"
#include "qgsdecorationcopyright.h"
#include "qgstextrenderer.h"
#include "qgsfontutils.h"
#include "qgsmapcanvas.h"
#include "qgsgui.h"

#include <memory>
#include <QColor>
#include <QFont>
#include <QObject>

class QgsDecorationItem;

class TestQgsDecorations : public QObject
{
    Q_OBJECT
  public:
    TestQgsDecorations() = default;

  private slots:
    void initTestCase(); // will be called before the first testfunction is executed.
    void cleanupTestCase(); // will be called after the last testfunction was executed.
    void init(); // will be called before each testfunction is executed.
    void cleanup(); // will be called after every testfunction.

    void testTitleDecorationSetGetTitleLabel();
    void testTitleDecorationSetGetTextFormat();
    void testCopyrightDecorationSetGetTitleLabel();
    void testCopyrightDecorationSetGetTextFormat();
  private:
    QString mTitleLabel = QString();
};

void TestQgsDecorations::initTestCase()
{
  QgsApplication::init();
  QgsApplication::initQgis();

  // Set up the QgsSettings environment
  QCoreApplication::setOrganizationName( QStringLiteral( "QGIS" ) );
  QCoreApplication::setOrganizationDomain( QStringLiteral( "qgis.org" ) );
  QCoreApplication::setApplicationName( QStringLiteral( "QGIS-TEST-DECORATIONS" ) );

}

void TestQgsDecorations::cleanupTestCase()
{
  QgsApplication::exitQgis();
}

void TestQgsDecorations::init()
{
}

void TestQgsDecorations::cleanup()
{
}

void TestQgsDecorations::testTitleDecorationSetGetTitleLabel()
{
  QgsDecorationTitle *mDeco = new QgsDecorationTitle();
  mTitleLabel = QString( "Testing setLabel method" );
  mDeco->setLabel( mTitleLabel );
  QCOMPARE( mDeco->label(), mTitleLabel );
}

void TestQgsDecorations::testTitleDecorationSetGetTextFormat()
{
  QgsDecorationTitle *mDeco = new QgsDecorationTitle();

  QgsTextFormat format;
  format.setFont( QgsFontUtils::getStandardTestFont( QStringLiteral( "Bold" ) ).family() );
  format.setSize( 12 );
  format.setNamedStyle( QStringLiteral( "Bold" ) );
  format.setColor( QColor( 200, 0, 200 ) );

  mDeco->setTextFormat( format );
  QCOMPARE( mDeco->textFormat().color(), format.color() );
  QCOMPARE( mDeco->textFormat().font(), format.font() );
  QCOMPARE( mDeco->textFormat().namedStyle(), format.namedStyle() );
  QCOMPARE( mDeco->textFormat().size(), format.size() );
}

void TestQgsDecorations::testCopyrightDecorationSetGetTitleLabel()
{
  QgsDecorationCopyright *mDeco = new QgsDecorationCopyright();
  mTitleLabel = QString( "Testing setLabel method" );
  mDeco->setLabel( mTitleLabel );
  QCOMPARE( mDeco->label(), mTitleLabel );
}

void TestQgsDecorations::testCopyrightDecorationSetGetTextFormat()
{
  QgsDecorationCopyright *mDeco = new QgsDecorationCopyright();

  QgsTextFormat format;
  format.setFont( QgsFontUtils::getStandardTestFont( QStringLiteral( "Bold" ) ).family() );
  format.setSize( 12 );
  format.setNamedStyle( QStringLiteral( "Bold" ) );
  format.setColor( QColor( 200, 0, 200 ) );

  mDeco->setTextFormat( format );
  QCOMPARE( mDeco->textFormat().color(), format.color() );
  QCOMPARE( mDeco->textFormat().font(), format.font() );
  QCOMPARE( mDeco->textFormat().namedStyle(), format.namedStyle() );
  QCOMPARE( mDeco->textFormat().size(), format.size() );
}

QGSTEST_MAIN( TestQgsDecorations )
#include "testqgsdecorations.moc"
