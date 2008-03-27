/*
    Copyright (c) 2008 Tobias Koenig <tokoe@kde.org>

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

#ifndef AKONADI_AGENTTYPE_H
#define AKONADI_AGENTTYPE_H

#include "akonadi_export.h"

#include <QtCore/QList>
#include <QtCore/QMetaType>
#include <QtCore/QSharedDataPointer>

class QIcon;
class QString;
class QStringList;

namespace Akonadi
{

class AKONADI_EXPORT AgentType
{
  friend class AgentManager;
  friend class AgentManagerPrivate;

  public:
    /**
     * Describes a list of agent type objects.
     */
    typedef QList<AgentType> List;

    /**
     * Creates a new agent type object.
     */
    AgentType();

    /**
     * Creates an agent type from an @p other agent type.
     */
    AgentType( const AgentType &other );

    /**
     * Destroys the agent type object.
     */
    ~AgentType();

    /**
     * Returns whether the agent type object is valid.
     */
    bool isValid() const;

    /**
     * Returns the unique identifier of the agent type.
     */
    QString identifier() const;

    /**
     * Returns the user visible name of the agent type.
     */
    QString name() const;

    /**
     * Returns the description of the agent type.
     */
    QString description() const;

    /**
     * Returns the name of the icon of the agent type.
     */
    QString iconName() const;

    /**
     * Returns the icon of the agent type.
     */
    QIcon icon() const;

    /**
     * Returns the list of supported mime types of the agent type.
     */
    QStringList mimeTypes() const;

    /**
     * Returns the list of supported capabilities of the agent type.
     */
    QStringList capabilities() const;

    /**
     * @internal
     */
    AgentType& operator=( const AgentType &other );

    /**
     * @internal
     */
    bool operator==( const AgentType &other ) const;

  private:
    class Private;
    QSharedDataPointer<Private> d;
};

}

Q_DECLARE_METATYPE( Akonadi::AgentType )

#endif
