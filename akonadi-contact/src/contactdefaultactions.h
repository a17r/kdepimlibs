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

#ifndef AKONADI_CONTACTDEFAULTACTIONS_H
#define AKONADI_CONTACTDEFAULTACTIONS_H

#include "akonadi-contact_export.h"

#include <QtCore/QObject>

class QUrl;

namespace KContacts
{
class Address;
class PhoneNumber;
}

namespace Akonadi
{

/**
 * @short A convenience class that handles different contact related actions.
 *
 * This class handles contact related actions like opening an email address,
 * showing the address of a contact on a map etc.
 *
 * Example:
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
 * ContactDefaultActions *actions = new ContactDefaultActions( this );
 * actions->connectToView( viewer );
 * @endcode
 *
 * If you want to use the full functionality of ContactDefaultActions
 * but customize a single action (e.g. handling sending mail differently)
 * the following can be done:
 *
 * @code
 *
 * using namespace Akonadi;
 *
 * ContactViewer *viewer = new ContactViewer( this );
 * ContactDefaultActions *actions = new ContactDefaultActions( this );
 *
 * // first connect all actions
 * actions->connectToView( viewer );
 *
 * // then remove the signle/slot connection you want to overwrite
 * disconnect( viewer, SIGNAL(emailClicked(QString,QString)),
 *             actions, SLOT(sendEmail(QString,QString)) );
 *
 * // connect to your custom implementation
 * connect( viewer, SIGNAL(emailClicked(QString,QString)),
 *          this, SLOT(handleSpecial(QString,QString)) );
 *
 * @endcode
 *
 * @author Tobias Koenig <tokoe@kde.org>
 * @since 4.4
 */
class AKONADI_CONTACT_EXPORT ContactDefaultActions : public QObject
{
    Q_OBJECT

public:
    /**
     * Creates a new contact default actions object.
     *
     * @param parent The parent object.
     */
    explicit ContactDefaultActions(QObject *parent = Q_NULLPTR);

    /**
     * Destroys the contact default actions object.
     */
    virtual ~ContactDefaultActions();

    /**
     * Tries to connect the well known signals of the @p view
     * to the well known slots of this object.
     */
    void connectToView(QObject *view);

public Q_SLOTS:
    /**
     * Shows the given @p url in the users preferred webbrowser.
     */
    void showUrl(const QUrl &url);

    /**
     * Opens the users preferred mail composer and does the setup
     * to send a mail to the contact with the given @p name and
     * email @p address.
     */
    void sendEmail(const QString &name, const QString &address);

    /**
     * Dials the given phone @p number with the application as
     * configured by the user in the general settings dialog.
     */
    void dialPhoneNumber(const KContacts::PhoneNumber &number);

    /**
     * Sends a sms to @p number with the application as
     * configured by the user in the general settings dialog.
     */
    void sendSms(const KContacts::PhoneNumber &number);

    /**
     * Shows the @p address of a contact in a webbrowser or application
     * as configured by the user in the general settings dialog.
     */
    void showAddress(const KContacts::Address &address);

private:
    //@cond PRIVATE
    class Private;
    Private *const d;
    //@endcond PRIVATE
};

}

#endif
