/*
    This file is part of the KDE project

    Copyright 2010 Friedrich W. H. Kossebau <kossebau@kde.org>

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) version 3, or any
    later version accepted by the membership of KDE e.V. (or its
    successor approved by the membership of KDE e.V.), which shall
    act as a proxy defined in Section 6 of version 3 of the license.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this library. If not, see <http://www.gnu.org/licenses/>.
*/

#include "internetgatewaydevice1.h"

// Solid
#include "kupnpstorageaccess.h"
// Qt
#include <QtCore/QSet>

namespace Solid
{
namespace Backends
{
namespace KUPnP
{

static const char InternetGatewayDevice1Udn[] =
    "urn:schemas-upnp-org:device:InternetGatewayDevice:1";

InternetGatewayDevice1Factory::InternetGatewayDevice1Factory() {}


QObject* InternetGatewayDevice1Factory::tryCreateDevice( const Cagibi::Device& device ) const
{
    return ( device.type() == QLatin1String(InternetGatewayDevice1Udn) ) ?
        new InternetGatewayDevice1( device ) : 0;
}



InternetGatewayDevice1::InternetGatewayDevice1(const Cagibi::Device& device)
  : KUPnPDevice(device)
{
}

InternetGatewayDevice1::~InternetGatewayDevice1()
{
}

QString InternetGatewayDevice1::icon() const
{
    return QString::fromLatin1("network-server");
}


QString InternetGatewayDevice1::description() const
{
    return QObject::tr("UPnP Internet Gateway Device");
}


bool InternetGatewayDevice1::queryDeviceInterface(const Solid::DeviceInterface::Type &type) const
{
    Q_UNUSED( type );

    bool result = false;

    return result;
}

QObject* InternetGatewayDevice1::createDeviceInterface(const Solid::DeviceInterface::Type& type)
{
    Q_UNUSED( type );

    DeviceInterface* interface = 0;

    return interface;
}

}
}
}
