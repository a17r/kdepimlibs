/*
    Copyright (C) 2008       Dmitry Ivanov <vonami@gmail.com>
                  2007, 2009 Frank Osterfeld <osterfeld@kde.org>

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef KRSS_FEEDLISTVIEW_H
#define KRSS_FEEDLISTVIEW_H

#include "krss/krss_export.h"

#include <Akonadi/EntityTreeView>

#include <QtGui/QTreeView>

class KConfigGroup;

namespace Akonadi {
    class Collection;
}
namespace KRss {

class KRSS_EXPORT FeedListView : public Akonadi::EntityTreeView
{
    Q_OBJECT

public:

    explicit FeedListView( QWidget *parent = 0 );
    ~FeedListView();

    /* reimp */ void setModel( QAbstractItemModel* model );

    KConfigGroup configGroup() const;
    void setConfigGroup( const KConfigGroup& group);

    void scrollToCollection( const Akonadi::Collection& c, QAbstractItemView::ScrollHint hint=EnsureVisible );

public Q_SLOTS:
    void slotPrevFeed();
    void slotNextFeed();
    void slotPrevUnreadFeed();
    void slotNextUnreadFeed();

Q_SIGNALS:

    void clicked( const Akonadi::Collection& );
    void activated( const Akonadi::Collection& );

private:
    class Private;
    Private* const d;
    Q_PRIVATE_SLOT( d, void slotClicked( const QModelIndex& ) )
    Q_PRIVATE_SLOT( d, void slotActivated( const QModelIndex& ) )
    Q_PRIVATE_SLOT( d, void showHeaderMenu( const QPoint& ) )
    Q_PRIVATE_SLOT( d, void headerMenuItemTriggered( QAction* ) )
};

} // namespace KRss

#endif // KRSS_FEEDLISTVIEW_H
