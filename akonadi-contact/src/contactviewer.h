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

#ifndef AKONADI_CONTACTVIEWER_H
#define AKONADI_CONTACTVIEWER_H

#include "akonadi-contact_export.h"

#include <itemmonitor.h>

#include <QWidget>

namespace KContacts
{
class Address;
class Addressee;
class PhoneNumber;
}

namespace Akonadi
{

class AbstractContactFormatter;

/**
 * @short A viewer component for contacts in Akonadi.
 *
 * This widgets provides a way to show a contact from the
 * Akonadi storage or a raw contact object.
 *
 * Examples:
 *
 * @code
 *
 * using namespace Akonadi;
 *
 * const Item contact = ...
 *
 * ContactViewer *viewer = new ContactViewer( this );
 * viewer->setContact( contact );
 *
 * @endcode

 * @code
 *
 * using namespace Akonadi;
 *
 * const KContacts::Addressee contact = ...
 *
 * ContactViewer *viewer = new ContactViewer( this );
 * viewer->setContact( contact );
 *
 * @endcode
 *
 * @author Tobias Koenig <tokoe@kde.org>
 * @since 4.4
 */
class AKONADI_CONTACT_EXPORT ContactViewer : public QWidget, public Akonadi::ItemMonitor
{
    Q_OBJECT

public:
    /**
     * Creates a new contact viewer.
     *
     * @param parent The parent widget.
     */
    explicit ContactViewer(QWidget *parent = Q_NULLPTR);

    /**
     * Destroys the contact viewer.
     */
    ~ContactViewer();

    /**
     * Returns the contact that is currently displayed.
     *
     * @note The returned contact is only valid if it was
     *       set with setContact() before.
     */
    Akonadi::Item contact() const;

    /**
     * Returns the raw contact that is currently displayed.
     *
     * @since 4.5
     */
    KContacts::Addressee rawContact() const;

    /**
     * Sets the contact @p formatter that should be used for formatting the
     * contact. If formatter is @c 0, the standard formatter will be used.
     * @param formatter the contact formatter to set
     * @note The contact viewer won't take ownership of the formatter.
     *
     * @since 4.6
     */
    void setContactFormatter(AbstractContactFormatter *formatter);
    /**
     * @since 5.1
     */
    void updateView();

    /**
     * @since 5.2
     */
    void setShowQRCode(bool b);
    bool showQRCode() const;
public Q_SLOTS:
    /**
     * Sets the @p contact that shall be displayed in the viewer.
     */
    void setContact(const Akonadi::Item &contact);

    /**
     * Sets the raw @p contact object that shall be displayed in the viewer.
     * @param contact the contact object to set
     * @since 4.5
     */
    void setRawContact(const KContacts::Addressee &contact);

Q_SIGNALS:
    /**
     * This signal is emitted whenever the user has clicked on
     * a url (e.g. homepage or blog url) in the viewer.
     *
     * @param url The url that has been clicked.
     */
    void urlClicked(const QUrl &url);

    /**
     * This signal is emitted whenever the user has clicked on
     * an email address in the viewer.
     *
     * @param name The name of the contact.
     * @param email The plain email address of the contact.
     */
    void emailClicked(const QString &name, const QString &email);

    /**
     * This signal is emitted whenever the user has clicked on a
     * phone number (that includes fax numbers as well) in the viewer.
     *
     * @param number The corresponding phone number.
     */
    void phoneNumberClicked(const KContacts::PhoneNumber &number);

    /**
     * This signal is emitted whenever the user has clicked on a SMS link of a
     * phone number in the viewer.
     *
     * @param number The corresponding phone number.
     */
    void smsClicked(const KContacts::PhoneNumber &number);

    /**
     * This signal is emitted whenever the user has clicked on an
     * address in the viewer.
     *
     * @param address The corresponding address.
     */
    void addressClicked(const KContacts::Address &address);

private:
    /**
     * This method is called whenever the displayed contact has been changed.
     */
    void itemChanged(const Item &contact) Q_DECL_OVERRIDE;

    /**
     * This method is called whenever the displayed contact has been
     * removed from Akonadi.
     */
    void itemRemoved() Q_DECL_OVERRIDE;

private:
    //@cond PRIVATE
    class Private;
    Private *const d;

    Q_PRIVATE_SLOT(d, void slotUrlClicked(const QUrl &))
    Q_PRIVATE_SLOT(d, void slotParentCollectionFetched(KJob *))
    //@endcond
};

}

#endif
