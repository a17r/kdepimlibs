/*
    Copyright (c) 2014 Christian Mollekopf <mollekopf@kolabsys.com>

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

#ifndef AKONADI_TAG_H
#define AKONADI_TAG_H

#include <akonadi/attributeentity.h>
#include <QVector>
#include <QSharedPointer>

namespace Akonadi {

class AKONADI_EXPORT Tag : public AttributeEntity
{
public:
    typedef QList<Tag> List;
    typedef qint64 Id;

    Tag();
    explicit Tag(Id id);
    explicit Tag(const QByteArray &gid, const QByteArray &type = QByteArray(), const QString &displayName = QString(), const Tag &parent = Tag());

    Tag(const Tag &);

    Tag &operator=(const Tag &);
    bool operator==(const Tag &);

    /**
     * Sets the unique @p identifier of the tag.
     */
    void setId(Id identifier);

    /**
     * Returns the unique identifier of the tag.
     */
    Id id() const;

    void setGid(const QByteArray &) const;
    QByteArray gid() const;

    void setRemoteId(const QByteArray &) const;
    QByteArray remoteId() const;

    void setType(const QByteArray &) const;
    QByteArray type() const;

    void setName(const QString &);
    QString name() const;

    void setParent(const Tag &);
    Tag parent() const;

    bool isValid() const;

private:
    class Private;
    QSharedPointer<Private> d;
};

}

Q_DECLARE_METATYPE(Akonadi::Tag)
Q_DECLARE_METATYPE(Akonadi::Tag::List)

#endif