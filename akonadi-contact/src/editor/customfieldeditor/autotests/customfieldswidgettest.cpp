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

#include "customfieldswidgettest.h"
#include "../customfieldswidget.h"
#include <QTest>
#include <editor/customfieldeditor/customfieldeditorwidget.h>
#include <editor/customfieldeditor/customfieldslistwidget.h>

CustomFieldsWidgetTest::CustomFieldsWidgetTest(QObject *parent)
    : QObject(parent)
{

}

CustomFieldsWidgetTest::~CustomFieldsWidgetTest()
{

}

void CustomFieldsWidgetTest::shouldHaveDefaultValue()
{
    Akonadi::CustomFieldsWidget w;
    Akonadi::CustomFieldEditorWidget *customFieldEditorWidget = w.findChild<Akonadi::CustomFieldEditorWidget *>(QStringLiteral("customfieldeditorwidget"));
    QVERIFY(customFieldEditorWidget);

    Akonadi::CustomFieldsListWidget *customFieldsListWidget = w.findChild<Akonadi::CustomFieldsListWidget *>(QStringLiteral("customfieldslistwidget"));
    QVERIFY(customFieldsListWidget);
}

QTEST_MAIN(CustomFieldsWidgetTest)
