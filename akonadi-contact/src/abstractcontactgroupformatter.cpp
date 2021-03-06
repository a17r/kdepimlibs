/*
    This file is part of Akonadi Contact.

    Copyright (c) 2010 Tobias Koenig <tokoe@kde.org>

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

#include "abstractcontactgroupformatter.h"

#include <item.h>
#include <kcontacts/contactgroup.h>

using namespace Akonadi;

class Q_DECL_HIDDEN AbstractContactGroupFormatter::Private
{
public:
    KContacts::ContactGroup mContactGroup;
    Akonadi::Item mItem;
    QVector<QVariantMap> mAdditionalFields;
};

AbstractContactGroupFormatter::AbstractContactGroupFormatter()
    : d(new Private)
{
}

AbstractContactGroupFormatter::~AbstractContactGroupFormatter()
{
    delete d;
}

void AbstractContactGroupFormatter::setContactGroup(const KContacts::ContactGroup &group)
{
    d->mContactGroup = group;
}

KContacts::ContactGroup AbstractContactGroupFormatter::contactGroup() const
{
    return d->mContactGroup;
}

void AbstractContactGroupFormatter::setItem(const Akonadi::Item &item)
{
    d->mItem = item;
}

Akonadi::Item AbstractContactGroupFormatter::item() const
{
    return d->mItem;
}

void AbstractContactGroupFormatter::setAdditionalFields(const QVector<QVariantMap> &fields)
{
    d->mAdditionalFields = fields;
}

QVector<QVariantMap> AbstractContactGroupFormatter::additionalFields() const
{
    return d->mAdditionalFields;
}
