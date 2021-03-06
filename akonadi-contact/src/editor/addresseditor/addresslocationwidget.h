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

#ifndef ADDRESSLOCATIONWIDGET_H
#define ADDRESSLOCATIONWIDGET_H

#include <QWidget>
#include <KContacts/Address>
class QStackedWidget;
class QCheckBox;
class KLineEdit;
class KComboBox;
class QPushButton;
namespace Akonadi
{
class SelectAddressTypeComboBox;
class AddressLocationWidget : public QWidget
{
    Q_OBJECT
public:
    enum Mode {
        CreateAddress = 0,
        ModifyAddress
    };

    explicit AddressLocationWidget(QWidget *parent = Q_NULLPTR);
    ~AddressLocationWidget();

    void setAddress(const KContacts::Address &address);
    KContacts::Address address() const;

    void slotModifyAddress(const KContacts::Address &address, int currentIndex);

    void clear();

    void setReadOnly(bool readOnly);

Q_SIGNALS:
    void addNewAddress(const KContacts::Address &address);
    void updateAddress(const KContacts::Address &address, int index);
    void updateAddressCanceled();

private Q_SLOTS:
    void slotAddAddress();
    void slotUpdateAddress();
    void slotCancelModifyAddress();

private:
    void fillCountryCombo();
    void switchMode();
    void reset();
    KContacts::Address mAddress;
    QCheckBox *mPreferredCheckBox;
    KLineEdit *mPOBoxEdit;
    KLineEdit *mLocalityEdit;
    KLineEdit *mRegionEdit;
    KLineEdit *mPostalCodeEdit;
    KLineEdit *mStreetEdit;
    KComboBox *mCountryCombo;
    QPushButton *mAddAddress;
    QPushButton *mModifyAddress;
    QPushButton *mCancelAddress;
    QStackedWidget *mButtonStack;
    SelectAddressTypeComboBox *mTypeCombo;
    int mCurrentAddress;
    Mode mCurrentMode;
};
}
#endif // ADDRESSLOCATIONWIDGET_H
