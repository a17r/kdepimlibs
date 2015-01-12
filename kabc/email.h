/*
    This file is part of libkabc.
    Copyright (c) 2015 Laurent Montel <montel@kde.org>

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Library General Public
    License as published by the Free Software Foundation; either
    version 2 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Library General Public License for more details.

    You should have received a copy of the GNU Library General Public License
    along with this library; see the file COPYING.LIB.  If not, write to
    the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
    Boston, MA 02110-1301, USA.
*/


#ifndef EMAIL_H
#define EMAIL_H

#include "kabc_export.h"
#include <QtCore/QSharedDataPointer>
#include <QtCore/QString>
#include <qmap.h>

/** @short Class that holds a Email for a contact.
 *  @since 4.14.5
 */

namespace KABC {

class KABC_EXPORT Email
{
    friend KABC_EXPORT QDataStream &operator<<( QDataStream &, const Email & );
    friend KABC_EXPORT QDataStream &operator>>( QDataStream &, Email & );
public:
    /**
     * Creates an empty email object.
     */
    Email();
    Email(const QString &mail, bool preferred);

    ~Email();

    typedef QList<Email> List;

    void setEmail(const QString &mail);
    QString mail() const;

    bool isValid() const;

    void setParameters(const QMap<QString, QStringList> &params);
    QMap<QString, QStringList> parameters() const;

    void setPreferred(bool pref);
    bool preferred() const;

    bool operator==( const Email &other ) const;

    QString toString() const;
private:
    class Private;
    QSharedDataPointer<Private> d;
};

KABC_EXPORT QDataStream &operator<<( QDataStream &stream, const Email &object );

KABC_EXPORT QDataStream &operator>>( QDataStream &stream, Email &object );

}
#endif // EMAIL_H