/***************************************************************************
                         qgsdecorationitem.h
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
#ifndef QGSDECORATIONITEM_H
#define QGSDECORATIONITEM_H

#include <QObject>

#include "qgsmapdecoration.h"
#include "qgsunittypes.h"
#include "qgis_sip.h"
#include "qgis_gui.h"

class QPainter;
class QgsMapCanvas;
class QgsMessageBar;

#define INCHES_TO_MM 0.0393700787402

/**
 * \ingroup core
 * \class QgsDecoration
 * \brief Interface for map decorations.
 *
 * \since QGIS 3.10
 */
class GUI_EXPORT QgsDecorationItem : public QObject, public QgsMapDecoration
{
    Q_OBJECT

  public:

    //! Item placements
    enum Placement
    {
      BottomLeft = 0,
      TopLeft,
      TopRight,
      BottomRight,
      TopCenter,
      BottomCenter
    };

    //! Constructor
    QgsDecorationItem( QObject *parent SIP_TRANSFERTHIS = nullptr );

    void setEnabled( bool enabled ) { mEnabled = enabled; }
    bool enabled() const { return mEnabled; }

    /**
     * Returns the current placement for the item.
     * \see setPlacement()
     */
    Placement placement() const { return mPlacement; }

    /**
     * Sets the placement of the item.
     * \see placement()
     */
    void setPlacement( Placement placement ) { mPlacement = placement; }

    /**
     * Sets the map canvas associated with the decoration item.
     * \param canvas map canvas
     */
    void setMapCanvas( QgsMapCanvas *canvas ) { mCanvas = canvas; }

    /**
     * Sets the messagebar associated with the decoration item.
     */
    void setMessageBar( QgsMessageBar *messagebar ) { mMessageBar = messagebar; }

    QString name() const { return mName; }

  signals:
    void toggled( bool t );

  public slots:
    //! Sets values on the gui when a project is read or the gui first loaded
    virtual void projectRead();
    //! save values to the project
    virtual void saveToProject();

    //! Show the dialog box
    virtual void run() {}

    //! Redraws the decoration
    void update();

  protected:

    void setName( const char *name );

    //! True if decoration item has to be displayed
    bool mEnabled = false;

    //! Placement of the decoration
    Placement mPlacement = TopLeft;
    //! Units used for the decoration placement margin
    QgsUnitTypes::RenderUnit mMarginUnit = QgsUnitTypes::RenderMillimeters;

    //! pointer to map canvas
    QgsMapCanvas *mCanvas = nullptr;

    //! pointer to message bar
    QgsMessageBar *mMessageBar = nullptr;

    QString mName;
    QString mNameConfig;
    QString mNameTranslated;
};

#endif
