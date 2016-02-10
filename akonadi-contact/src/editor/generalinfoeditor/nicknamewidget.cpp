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

#include "nicknamewidget.h"
#include <KLocalizedString>
#include <QLabel>
#include <QVBoxLayout>
#include <QLineEdit>
using namespace Akonadi;

NicknameWidget::NicknameWidget(QWidget *parent)
    : QWidget(parent)
{
    QVBoxLayout *topLayout = new QVBoxLayout(this);
    topLayout->setMargin(0);
    QLabel *nickNameLabel = new QLabel(i18n("Nickname"), this);
    nickNameLabel->setObjectName(QStringLiteral("nicknamelabel"));
    topLayout->addWidget(nickNameLabel);

    mNickName = new QLineEdit(this);
    mNickName->setPlaceholderText(i18n("Add a Nickname"));
    mNickName->setObjectName(QStringLiteral("nickname"));
    topLayout->addWidget(mNickName);
}

NicknameWidget::~NicknameWidget()
{

}

void NicknameWidget::loadContact(const KContacts::Addressee &contact)
{
    //TODO
}

void NicknameWidget::storeContact(KContacts::Addressee &contact) const
{
    //TODO
}

void NicknameWidget::setReadOnly(bool readOnly)
{
    mNickName->setReadOnly(readOnly);
}
