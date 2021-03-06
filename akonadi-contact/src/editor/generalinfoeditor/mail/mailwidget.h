/*
    This file is part of Akonadi Contact.

    Copyright (C) 2016 eyeOS S.L.U., a Telefonica company, sales@eyeos.com
    Copyright (C) 2016 Laurent Montel <laurent.montel@kdab.com>

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

#ifndef MAILWIDGET_H
#define MAILWIDGET_H

#include <QWidget>
#include <KContacts/Email>
class QToolButton;
namespace Akonadi
{
class PreferredLineEditWidget;
class AkonadiContactSelectTypeCombobox;
class MailWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MailWidget(QWidget *parent = Q_NULLPTR);
    ~MailWidget();

    void clearWidget();
    void updateAddRemoveButton(bool addButtonEnabled);
    void setMail(const KContacts::Email &email);
    KContacts::Email email();
    void setPreferred(bool b);
Q_SIGNALS:
    void addWidget(MailWidget *);
    void removeWidget(MailWidget *);
    void preferredChanged(MailWidget *);

private Q_SLOTS:
    void slotAddMail();
    void slotRemoveMail();
    void slotPreferredChanged();
private:
    KContacts::Email mEmail;
    QString mOldType;
    PreferredLineEditWidget *mMailEdit;
    Akonadi::AkonadiContactSelectTypeCombobox *mMailType;
    QToolButton *mAddButton;
    QToolButton *mRemoveButton;
};
}
#endif // MAILWIDGET_H
