/***************************************************************************
                         qgsdecorationgriddialog.cpp
                         ----------------------
    begin                : May 10, 2012
    copyright            : (C) 2012 by Etienne Tourigny
    email                : etourigny.dev at gmail dot com

 ***************************************************************************/
/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#include "qgsdecorationgriddialog.h"

#include "qgsdecorationgrid.h"

#include "qgslogger.h"
#include "qgshelp.h"
#include "qgsstyle.h"
#include "qgssymbol.h"
#include "qgssymbolselectordialog.h"
#include "qgsguiutils.h"
#include "qgsgui.h"

QgsDecorationGridDialog::QgsDecorationGridDialog( QgsDecorationGrid &deco, QWidget *parent )
  : QDialog( parent )
  , mDeco( deco )
{
  setupUi( this );

  QgsGui::enableAutoGeometryRestore( this );

  connect( buttonBox, &QDialogButtonBox::accepted, this, &QgsDecorationGridDialog::buttonBox_accepted );
  connect( buttonBox, &QDialogButtonBox::rejected, this, &QgsDecorationGridDialog::buttonBox_rejected );
  connect( mGridTypeComboBox, static_cast<void ( QComboBox::* )( int )>( &QComboBox::currentIndexChanged ), this, [ = ]( int ) { updateSymbolButtons(); } );
  connect( mPbtnUpdateFromExtents, &QPushButton::clicked, this, &QgsDecorationGridDialog::mPbtnUpdateFromExtents_clicked );
  connect( mPbtnUpdateFromLayer, &QPushButton::clicked, this, &QgsDecorationGridDialog::mPbtnUpdateFromLayer_clicked );
  connect( buttonBox, &QDialogButtonBox::helpRequested, this, &QgsDecorationGridDialog::showHelp );

  mMarkerSymbolButton->setSymbolType( QgsSymbol::Marker );
  mLineSymbolButton->setSymbolType( QgsSymbol::Line );

  grpEnable->setChecked( mDeco.enabled() );
  connect( grpEnable, &QGroupBox::toggled, this, [ = ] { updateSymbolButtons(); } );

  // mXMinLineEdit->setValidator( new QDoubleValidator( mXMinLineEdit ) );

  mGridTypeComboBox->addItem( tr( "Line" ), QgsDecorationGrid::Line );
  mGridTypeComboBox->addItem( tr( "Marker" ), QgsDecorationGrid::Marker );

  // mAnnotationPositionComboBox->insertItem( QgsDecorationGrid::InsideMapFrame, tr( "Inside frame" ) );
  // mAnnotationPositionComboBox->insertItem( QgsDecorationGrid::OutsideMapFrame, tr( "Outside frame" ) );

  mAnnotationDirectionComboBox->insertItem( QgsDecorationGrid::Horizontal,
      tr( "Horizontal" ) );
  mAnnotationDirectionComboBox->insertItem( QgsDecorationGrid::Vertical,
      tr( "Vertical" ) );
  mAnnotationDirectionComboBox->insertItem( QgsDecorationGrid::HorizontalAndVertical,
      tr( "Horizontal and Vertical" ) );
  mAnnotationDirectionComboBox->insertItem( QgsDecorationGrid::BoundaryDirection,
      tr( "Boundary direction" ) );

  updateGuiElements();

  connect( buttonBox->button( QDialogButtonBox::Apply ), &QAbstractButton::clicked, this, &QgsDecorationGridDialog::apply );

  // font settings
  mAnnotationFontButton->setDialogTitle( tr( "Annotation Text Format" ) );
  mAnnotationFontButton->setMapCanvas( mDeco.mCanvas );
  mAnnotationFontButton->setTextFormat( mDeco.textFormat() );

  mMarkerSymbolButton->setMapCanvas( mDeco.mCanvas );
  mMarkerSymbolButton->setMessageBar( mDeco.mMessageBar );
  mLineSymbolButton->setMapCanvas( mDeco.mCanvas );
  mLineSymbolButton->setMessageBar( mDeco.mMessageBar );
}

void QgsDecorationGridDialog::updateGuiElements()
{
  // blockAllSignals( true );

  grpEnable->setChecked( mDeco.enabled() );

  mIntervalXEdit->setText( QString::number( mDeco.gridIntervalX() ) );
  mIntervalYEdit->setText( QString::number( mDeco.gridIntervalY() ) );
  mOffsetXEdit->setText( QString::number( mDeco.gridOffsetX() ) );
  mOffsetYEdit->setText( QString::number( mDeco.gridOffsetY() ) );

  mGridTypeComboBox->setCurrentIndex( mGridTypeComboBox->findData( mDeco.gridStyle() ) );
  mDrawAnnotationCheckBox->setChecked( mDeco.showGridAnnotation() );
  mAnnotationDirectionComboBox->setCurrentIndex( static_cast< int >( mDeco.gridAnnotationDirection() ) );
  mCoordinatePrecisionSpinBox->setValue( mDeco.gridAnnotationPrecision() );

  mDistanceToMapFrameSpinBox->setValue( mDeco.annotationFrameDistance() );
  // QPen gridPen = mDeco.gridPen();
  // mLineWidthSpinBox->setValue( gridPen.widthF() );
  // mLineColorButton->setColor( gridPen.color() );

  mAnnotationFontButton->setTextFormat( mDeco.textFormat() );

  mLineSymbolButton->setSymbol( mDeco.lineSymbol()->clone() );
  mMarkerSymbolButton->setSymbol( mDeco.markerSymbol()->clone() );

  whileBlocking( mAnnotationFontButton )->setCurrentFont( mDeco.gridAnnotationFont() );

  updateInterval( false );

  // blockAllSignals( false );
}

void QgsDecorationGridDialog::updateDecoFromGui()
{
  mDeco.setDirty( false );
  mDeco.setEnabled( grpEnable->isChecked() );

  mDeco.setGridIntervalX( mIntervalXEdit->text().toDouble() );
  mDeco.setGridIntervalY( mIntervalYEdit->text().toDouble() );
  mDeco.setGridOffsetX( mOffsetXEdit->text().toDouble() );
  mDeco.setGridOffsetY( mOffsetYEdit->text().toDouble() );
  mDeco.setGridStyle( static_cast< QgsDecorationGrid::GridStyle >( mGridTypeComboBox->currentData().toInt() ) );

  mDeco.setTextFormat( mAnnotationFontButton->textFormat() );
  mDeco.setAnnotationFrameDistance( mDistanceToMapFrameSpinBox->value() );
  mDeco.setShowGridAnnotation( mDrawAnnotationCheckBox->isChecked() );
  QString text = mAnnotationDirectionComboBox->currentText();
  if ( text == tr( "Horizontal" ) )
  {
    mDeco.setGridAnnotationDirection( QgsDecorationGrid::Horizontal );
  }
  else if ( text == tr( "Vertical" ) )
  {
    mDeco.setGridAnnotationDirection( QgsDecorationGrid::Vertical );
  }
  else if ( text == tr( "Horizontal and Vertical" ) )
  {
    mDeco.setGridAnnotationDirection( QgsDecorationGrid::HorizontalAndVertical );
  }
  else //BoundaryDirection
  {
    mDeco.setGridAnnotationDirection( QgsDecorationGrid::BoundaryDirection );
  }
  mDeco.setGridAnnotationPrecision( mCoordinatePrecisionSpinBox->value() );
  mDeco.setLineSymbol( mLineSymbolButton->clonedSymbol< QgsLineSymbol >() );
  mDeco.setMarkerSymbol( mMarkerSymbolButton->clonedSymbol< QgsMarkerSymbol >() );
}

void QgsDecorationGridDialog::showHelp()
{
  QgsHelp::openHelp( QStringLiteral( "introduction/general_tools.html#grid" ) );
}

void QgsDecorationGridDialog::buttonBox_accepted()
{
  updateDecoFromGui();
  // mDeco.update();
  accept();
}

void QgsDecorationGridDialog::apply()
{
  updateDecoFromGui();
  mDeco.update();
  //accept();
}

void QgsDecorationGridDialog::buttonBox_rejected()
{
  reject();
}

void QgsDecorationGridDialog::updateSymbolButtons()
{
  switch ( mGridTypeComboBox->currentData().toInt() )
  {
    case ( QgsDecorationGrid::Marker ):
    {
      mMarkerSymbolButton->setVisible( true );
      mMarkerSymbolButton->setEnabled( grpEnable->isChecked() );
      mMarkerSymbolLabel->setVisible( true );
      mLineSymbolButton->setVisible( false );
      mLineSymbolButton->setEnabled( false );
      mLineSymbolLabel->setVisible( false );
      break;
    }
    case ( QgsDecorationGrid::Line ):
    {
      mLineSymbolButton->setVisible( true );
      mLineSymbolButton->setEnabled( grpEnable->isChecked() );
      mLineSymbolLabel->setVisible( true );
      mMarkerSymbolButton->setVisible( false );
      mMarkerSymbolButton->setEnabled( false );
      mMarkerSymbolLabel->setVisible( false );
      break;
    }
  }
}

void QgsDecorationGridDialog::mPbtnUpdateFromExtents_clicked()
{
  updateInterval( true );
}

void QgsDecorationGridDialog::mPbtnUpdateFromLayer_clicked()
{
  double values[4];
  if ( mDeco.getIntervalFromCurrentLayer( values ) )
  {
    mIntervalXEdit->setText( QString::number( values[0] ) );
    mIntervalYEdit->setText( QString::number( values[1] ) );
    mOffsetXEdit->setText( QString::number( values[2] ) );
    mOffsetYEdit->setText( QString::number( values[3] ) );
    if ( values[0] >= 1 )
      mCoordinatePrecisionSpinBox->setValue( 0 );
    else
      mCoordinatePrecisionSpinBox->setValue( 3 );
  }
}

void QgsDecorationGridDialog::updateInterval( bool force )
{
  if ( force || mDeco.isDirty() )
  {
    double values[4];
    if ( mDeco.getIntervalFromExtent( values, true ) )
    {
      mIntervalXEdit->setText( QString::number( values[0] ) );
      mIntervalYEdit->setText( QString::number( values[1] ) );
      mOffsetXEdit->setText( QString::number( values[2] ) );
      mOffsetYEdit->setText( QString::number( values[3] ) );
      // also update coord. precision
      // if interval >= 1, set precision=0 because we have a rounded value
      // else set it to previous default of 3
      if ( values[0] >= 1 )
        mCoordinatePrecisionSpinBox->setValue( 0 );
      else
        mCoordinatePrecisionSpinBox->setValue( 3 );
    }
  }
}
