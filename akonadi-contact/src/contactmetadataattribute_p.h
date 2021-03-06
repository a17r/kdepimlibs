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

#ifndef AKONADI_CONTACTMETADATAATTRIBUTE_P_H
#define AKONADI_CONTACTMETADATAATTRIBUTE_P_H

#include "akonadi-contact_export.h"

#include <attribute.h>

#include <QtCore/QVariant>

namespace Akonadi
{

/**
 * @short Attribute to store contact specific meta data.
 *
 * @author Tobias Koenig <tokoe@kde.org>
 */
class AKONADI_CONTACT_EXPORT ContactMetaDataAttribute : public Akonadi::Attribute
{
public:
    /**
     * Creates a new contact meta data attribute.
     */
    ContactMetaDataAttribute();

    /**
     * Destroys the contact meta data attribute.
     */
    ~ContactMetaDataAttribute();

    /**
     * Sets the meta @p data.
     */
    void setMetaData(const QVariantMap &data);

    /**
     * Returns the meta data.
     */
    QVariantMap metaData() const;

    QByteArray type() const Q_DECL_OVERRIDE;
    Attribute *clone() const Q_DECL_OVERRIDE;
    QByteArray serialized() const Q_DECL_OVERRIDE;
    void deserialize(const QByteArray &data) Q_DECL_OVERRIDE;

private:
    //@cond PRIVATE
    class Private;
    Private *const d;
    //@endcond
};

}

#endif
