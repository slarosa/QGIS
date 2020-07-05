/***************************************************************************
                          plugin.h
 Functions:
                             -------------------
    begin                : Jan 21, 2004
    copyright            : (C) 2004 by Tim Sutton
    email                : tim@linfiniti.com

 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/
#ifndef QGSCOPYRIGHTLABELPLUGIN
#define QGSCOPYRIGHTLABELPLUGIN

#include "qgsdecorationitem.h"
#include "qgstextformat.h"

#include <QColor>
#include <QFont>
#include <QObject>
#include "qgis_sip.h"
#include "qgis_gui.h"
class QAction;
class QPainter;

class QgsDecorationCopyrightDialog;

/**
 * \ingroup gui
 * \class QgsDecorationCopyright
 * \brief Main class for copyright map decoration
 *
 * \since QGIS 3.16
 */
class GUI_EXPORT QgsDecorationCopyright : public QgsDecorationItem
{
    Q_OBJECT
  public:

    //! Constructor
    QgsDecorationCopyright( QObject *parent SIP_TRANSFERTHIS = nullptr );

  public slots:
    //! Sets values on the gui when a project is read or the gui first loaded
    void projectRead() override;
    //! save values to the project
    void saveToProject() override;

    //! Show the dialog box
    void run() override;
    //! render the copyright label
    void render( const QgsMapSettings &mapSettings, QgsRenderContext &context ) override;

    /**
     * Set the decoration title
     * \param label decoration grid
     */
    void setLabel( const QString &label ) { mLabelText = label; }

    /**
     * Get the decoration title
     * \param label decoration grid
     */
    QString label() const { return mLabelText; }

    /**
     * Returns the text format for extent labels.
     * \see setTextFormat()
     * \see labelExtents()
     * \since QGIS 3.2
     */
    QgsTextFormat textFormat() const { return mTextFormat; }

    /**
     * Sets the text \a format for extent labels.
     * \see textFormat()
     * \see setLabelExtents()
     * \since QGIS 3.2
     */
    void setTextFormat( const QgsTextFormat &format ) { mTextFormat = format; }

  private:
    //! This is the string that will be used for the copyright label
    QString mLabelText;

    //! enable or disable use of position percentage for placement
    int mMarginHorizontal = 0;
    int mMarginVertical = 0;

    QgsTextFormat mTextFormat;

    friend class QgsDecorationCopyrightDialog;
};

#endif
