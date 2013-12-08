/*
 * This file is part of the krss library
 *
 * Copyright (C) 2007 Frank Osterfeld <osterfeld@kde.org>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public License
 * along with this library; see the file COPYING.LIB.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301, USA.
 *
 */

#ifndef KRSS_CATEGORY_H
#define KRSS_CATEGORY_H

#include <krss/krss_export.h>

#include <QtCore/QSharedDataPointer>

class QString;

namespace KRss {

class KRSS_EXPORT Category
{
public:
    Category();
    Category( const Category& other );
    ~Category();

    QString term() const;
    void setTerm( const QString& term );

    QString scheme() const;
    void setScheme( const QString& scheme );

    QString label() const;
    void setLabel( const QString& label );

    Category& operator=( const Category& other );
    bool operator==( const Category& other ) const;
    bool operator!=( const Category& other ) const;

    void swap( Category& other );

private:
    class Private;
    QSharedDataPointer<Private> d;
};

} // namespace KRss

#endif // KRss_CATEGORY_H