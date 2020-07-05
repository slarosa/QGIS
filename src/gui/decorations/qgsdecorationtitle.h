/***************************************************************************
  qgsdecorationtitle.h
  --------------------------------------
  Date                 : November 2018
  Copyright            : (C) 2018 by Mathieu Pellerin
  Email                : nirvn dot asia at gmail dot com
 ***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#ifndef QGSDECORATIONTITLE_H
#define QGSDECORATIONTITLE_H

#include "qgsdecorationitem.h"
#include "qgstextformat.h"
#include "qgstextrenderer.h"
#include "qgis_sip.h"
#include "qgis_gui.h"

#include <QColor>
#include <QFont>
#include <QObject>

class QgsDecorationTitleDialog;

class QAction;
class QPainter;

/**
 * \ingroup gui
 * \class QgsDecorationTitle
 * \brief Main class for title map decoration
 *
 * \since QGIS 3.16
 */
class GUI_EXPORT QgsDecorationTitle : public QgsDecorationItem
{
    Q_OBJECT
  public:

    //! Constructor
    QgsDecorationTitle( QObject *parent SIP_TRANSFERTHIS = nullptr );

  public slots:
    //! Sets values on the gui when a project is read or the gui first loaded
    void projectRead() override;
    //! save values to the project
    void saveToProject() override;

    //! Show the dialog box
    void run() override;
    //! render the title label
    void render( const QgsMapSettings &mapSettings, QgsRenderContext &context ) override;

    /**
     * Sets the decoration title.
     * Set the decoration title
     * \param label decoration title
     */
    void setLabel( const QString &label ) { mLabelText = label; }

    /**
     * Get the decoration title
     * \param label decoration title
     */
    QString label() const { return mLabelText; }


    /**
     * Returns the title text format.
     * \see setTextFormat()
     * \see labelExtents()
     */
    QgsTextFormat textFormat() const { return mTextFormat; }

    /**
     * Sets the title text \a format.
     * \see textFormat()
     * \see setLabelExtents()
     */
    void setTextFormat( const QgsTextFormat &format ) { mTextFormat = format; }

  private:
    //! This is the string that will be used for the title label
    QString mLabelText;

    //! The background bar color
    QColor mBackgroundColor;

    //! enable or disable use of position percentage for placement
    int mMarginHorizontal = 0;
    int mMarginVertical = 0;

    QgsTextFormat mTextFormat;

    friend class QgsDecorationTitleDialog;
};

#endif
