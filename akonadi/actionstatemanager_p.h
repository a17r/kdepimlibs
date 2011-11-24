/*
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

#ifndef AKONADI_ACTIONSTATEMANAGER_P_H
#define AKONADI_ACTIONSTATEMANAGER_P_H

#include <akonadi/collection.h>
#include <akonadi/item.h>

class QObject;

namespace Akonadi {

/**
 * @short A helper class to manage action states.
 *
 * @author Tobias Koenig <tokoe@kde.org>
 */
class ActionStateManager
{
  public:
    /**
     * Creates a new action state manager.
     */
    ActionStateManager();

    /**
     * Destroys the action state manager.
     */
    virtual ~ActionStateManager();

    /**
     * Updates the states according to the selected @p collections and @p items.
     */
    void updateState( const Collection::List &collections, const Item::List &items );

    /**
     * Sets the @p receiver object that will actually update the states.
     *
     * The object must provide the following three slots:
     *   - void enableAction( int, bool )
     *   - void updatePluralLabel( int, int )
     *   - bool isFavoriteCollection( const Akonadi::Collection& )
     */
    void setReceiver( QObject *receiver );

  protected:
    virtual bool isRootCollection( const Collection &collection ) const;
    virtual bool isResourceCollection( const Collection &collection ) const;
    virtual bool isFolderCollection( const Collection &collection ) const;
    virtual bool isSpecialCollection( const Collection &collection ) const;
    virtual bool isFavoriteCollection( const Collection &collection ) const;
    virtual bool hasResourceCapability( const Collection &collection, const QString &capability ) const;
    virtual bool collectionCanHaveItems( const Collection &collection ) const;

    virtual void enableAction( int action, bool state );
    virtual void updatePluralLabel( int action, int count );

  private:
    QObject *mReceiver;
};

}

#endif
