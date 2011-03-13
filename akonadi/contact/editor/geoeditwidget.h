/*
    This file is part of Akonadi Contact.

    Copyright (c) 2009 Tobias Koenig <tokoe@kde.org>

    This library is free software; you can redistribute it and/or modify it
    under the terms of the GNU Library General Public License as published by
    the Free Software Foundation; either version 2 of the License, or (at your
    option) any later version.

    This library is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Library General Public
    License for more details.

    You should have received a copy of the GNU Library General Public License
    along with this library; see the file COPYING.LIB.  If not, write to the
    Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
    02110-1301, USA.
*/

#ifndef GEOEDITWIDGET_H
#define GEOEDITWIDGET_H

#include "config-akonadi-contact.h"

#include <kabc/geo.h>
#include <kdialog.h>

#include <QtGui/QWidget>

namespace KABC
{
class Addressee;
class Address;
}

namespace Marble
{
  class GeoDataCoordinates;
  class GeoDataPlacemark;
  class MarbleRunnerManager;
  class MarbleWidget;
}
using Marble::GeoDataCoordinates; // FIXME: marble doesn't use fully qualified type names in its signals...
using Marble::GeoDataPlacemark;

class QAbstractItemModel;
class QDoubleSpinBox;
class QLabel;
class QPushButton;
class QSpinBox;

class KComboBox;

class GeoMapWidget;

class GeoEditWidget : public QWidget
{
  Q_OBJECT

  public:
    GeoEditWidget( QWidget *parent = 0 );
    ~GeoEditWidget();

    void loadContact( const KABC::Addressee &contact );
    void storeContact( KABC::Addressee &contact ) const;

    void setReadOnly( bool readOnly );

  public Q_SLOTS:
#ifdef HAVE_MARBLE
    void centerOnAddress( const KABC::Address &addr );
#endif

  private Q_SLOTS:
    void changeClicked();
#ifdef HAVE_MARBLE
    void copyAddressClicked();
    void reverseGeocodingFinished( const GeoDataCoordinates &coord, const GeoDataPlacemark &placemark );
    void searchResultChanged( QAbstractItemModel *model );
#endif

  private:
    void updateView();
#ifdef HAVE_MARBLE
    void setupRunnerManager();
#endif

#ifndef HAVE_MARBLE
    GeoMapWidget *mMap;
#else
    Marble::MarbleWidget *mMap;
    Marble::MarbleRunnerManager *mRunnerManager;
#endif
    QLabel *mLatitudeLabel;
    QLabel *mLongitudeLabel;
    QPushButton *mChangeButton;
    KABC::Geo mCoordinates;
    bool mReadOnly;
};

class GeoDialog : public KDialog
{
  Q_OBJECT

  public:
    GeoDialog( const KABC::Geo &coordinates, QWidget *parent );

    KABC::Geo coordinates() const;

  private:
    enum ExceptType {
      ExceptNone = 0,
      ExceptCity = 1,
      ExceptSexagesimal = 2,
      ExceptDecimal = 4
    };

  private Q_SLOTS:
    void updateInputs( ExceptType type = ExceptNone );

    void decimalInputChanged();
    void sexagesimalInputChanged();
    void cityInputChanged();

  private:
    void loadCityList();
    int nearestCity( double, double ) const;

    typedef struct {
      double latitude;
      double longitude;
      QString country;
    } GeoData;

    KComboBox *mCityCombo;

    QDoubleSpinBox *mLatitude;
    QDoubleSpinBox *mLongitude;

    QSpinBox *mLatDegrees;
    QSpinBox *mLatMinutes;
    QSpinBox *mLatSeconds;
    KComboBox *mLatDirection;

    QSpinBox *mLongDegrees;
    QSpinBox *mLongMinutes;
    QSpinBox *mLongSeconds;
    KComboBox *mLongDirection;

    KABC::Geo mCoordinates;
    QMap<QString, GeoData> mGeoDataMap;
    bool mUpdateSexagesimalInput;
};

#endif
