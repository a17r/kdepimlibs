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

#ifndef AKONADI_CONTACTGROUPVIEWER_H
#define AKONADI_CONTACTGROUPVIEWER_H

#include "akonadi-contact_export.h"

#include <itemmonitor.h>

#include <QWidget>

namespace Akonadi
{

class AbstractContactGroupFormatter;

/**
 * @short A viewer component for contact groups in Akonadi.
 *
 * This widgets provides a way to show a contact group from the
 * Akonadi storage.
 *
 * Example:
 *
 * @code
 *
 * using namespace Akonadi;
 *
 * const Item group = ...
 *
 * ContactGroupViewer *viewer = new ContactGroupViewer( this );
 * viewer->setContactGroup( group );
 *
 * @endcode
 *
 * @author Tobias Koenig <tokoe@kde.org>
 * @since 4.4
 */
class AKONADI_CONTACT_EXPORT ContactGroupViewer : public QWidget, public Akonadi::ItemMonitor
{
    Q_OBJECT

public:
    /**
     * Creates a new contact group viewer.
     *
     * @param parent The parent widget.
     */
    ContactGroupViewer(QWidget *parent = Q_NULLPTR);

    /**
     * Destroys the contact group viewer.
     */
    ~ContactGroupViewer();

    /**
     * Returns the contact group that is currently displayed.
     */
    Akonadi::Item contactGroup() const;

    /**
     * Sets the contact group @p formatter that should be used for formatting the
     * contact group. If formatter is @c 0, the standard formatter will be used.
     * @param formatter the formatter to use
     * @note The contact viewer won't take ownership of the formatter.
     * @since 4.6
     */
    void setContactGroupFormatter(AbstractContactGroupFormatter *formatter);

public Q_SLOTS:
    /**
     * Sets the contact @p group that shall be displayed in the viewer.
     */
    void setContactGroup(const Akonadi::Item &group);

Q_SIGNALS:
    /**
     * This signal is emitted whenever the user has clicked on
     * an email address in the viewer.
     *
     * @param name The name of the contact.
     * @param email The plain email address of the contact.
     */
    void emailClicked(const QString &name, const QString &email);

private:
    /**
     * This method is called whenever the displayed contact @p group has been changed.
     */
    void itemChanged(const Item &group) Q_DECL_OVERRIDE;

    /**
     * This method is called whenever the displayed contact group has been
     * removed from Akonadi.
     */
    void itemRemoved() Q_DECL_OVERRIDE;

private:
    //@cond PRIVATE
    class Private;
    Private *const d;

    Q_PRIVATE_SLOT(d, void slotMailClicked(const QUrl &))
    Q_PRIVATE_SLOT(d, void _k_expandResult(KJob *))
    Q_PRIVATE_SLOT(d, void slotParentCollectionFetched(KJob *))
    //@endcond
};

}

#endif
