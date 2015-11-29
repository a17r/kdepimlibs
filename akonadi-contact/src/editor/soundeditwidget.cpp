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

#include "soundeditwidget.h"

#include <kcontacts/addressee.h>
//#include <kfiledialog.h>

#include <KIO/StoredTransferJob>
#include <KJobWidgets>
#include <KLocalizedString>
#include <KMessageBox>
#include <QUrl>

#include <phonon/mediaobject.h>

#include <QFileDialog>

#include <QtCore/QBuffer>
#include <QContextMenuEvent>
#include <QMenu>

/**
 * @short Small helper class to load sound from network
 */
class SoundLoader
{
public:
    SoundLoader(QWidget *parent = Q_NULLPTR);

    QByteArray loadSound(const QUrl &url, bool *ok);

private:
    QByteArray mSound;
    QWidget *mParent;
};

SoundLoader::SoundLoader(QWidget *parent)
    : mParent(parent)
{
}

QByteArray SoundLoader::loadSound(const QUrl &url, bool *ok)
{
    QByteArray sound;

    if (url.isEmpty()) {
        return sound;
    }

    (*ok) = false;

    if (url.isLocalFile()) {
        QFile file(url.toLocalFile());
        if (file.open(QIODevice::ReadOnly)) {
            sound = file.readAll();
            file.close();
            (*ok) = true;
        }
    } else {
        auto job = KIO::storedGet(url);
        KJobWidgets::setWindow(job, mParent);
        if (job->exec()) {
            sound = job->data();
            (*ok) = true;
        }
    }

    if (!(*ok)) {
        KMessageBox::sorry(mParent, i18n("This contact's sound cannot be found."));
        return sound;
    }

    (*ok) = true;

    return sound;
}

SoundEditWidget::SoundEditWidget(QWidget *parent)
    : QToolButton(parent)
    , mHasSound(false)
    , mReadOnly(false)
    , mSoundLoader(0)
{
    connect(this, &SoundEditWidget::clicked, this, &SoundEditWidget::playSound);

    updateView();
}

SoundEditWidget::~SoundEditWidget()
{
    delete mSoundLoader;
}

void SoundEditWidget::loadContact(const KContacts::Addressee &contact)
{
    const KContacts::Sound sound = contact.sound();
    if (sound.isIntern() && !sound.data().isEmpty()) {
        mHasSound = true;
        mSound = sound.data();
    }

    updateView();
}

void SoundEditWidget::storeContact(KContacts::Addressee &contact) const
{
    KContacts::Sound sound(contact.sound());
    sound.setData(mSound);
    contact.setSound(sound);
}

void SoundEditWidget::setReadOnly(bool readOnly)
{
    mReadOnly = readOnly;
}

void SoundEditWidget::updateView()
{
    if (mHasSound) {
        setIcon(QIcon::fromTheme(QStringLiteral("audio-volume-medium")));
        setToolTip(i18n("Click to play pronunciation"));
    } else {
        setIcon(QIcon::fromTheme(QStringLiteral("audio-volume-muted")));
        setToolTip(i18n("No pronunciation available"));
    }
}

void SoundEditWidget::contextMenuEvent(QContextMenuEvent *event)
{
    QMenu menu;

    if (mHasSound) {
        menu.addAction(i18n("Play"), this, SLOT(playSound()));
    }

    if (!mReadOnly) {
        menu.addAction(i18n("Change..."), this, SLOT(changeSound()));
    }

    if (mHasSound) {
        menu.addAction(i18n("Save..."), this, SLOT(saveSound()));

        if (!mReadOnly) {
            menu.addAction(i18n("Remove"), this, SLOT(deleteSound()));
        }
    }

    menu.exec(event->globalPos());
}

void SoundEditWidget::playSound()
{
    if (!mHasSound) {
        return;
    }
    Phonon::MediaObject *player = Phonon::createPlayer(Phonon::NotificationCategory);
    QBuffer *soundData = new QBuffer(player);
    soundData->setData(mSound);
    player->setCurrentSource(soundData);
    player->setParent(this);
    connect(player, &Phonon::MediaObject::finished, player, &Phonon::MediaObject::deleteLater);
    player->play();
}

void SoundEditWidget::changeSound()
{
    const QUrl url = QFileDialog::getOpenFileUrl(this, QString(), QUrl(), QStringLiteral("*.wav"));
    if (url.isValid()) {
        bool ok = false;
        const QByteArray sound = soundLoader()->loadSound(url, &ok);
        if (ok) {
            mSound = sound;
            mHasSound = true;
            updateView();
        }
    }
}

void SoundEditWidget::saveSound()
{
    const QString fileName = QFileDialog::getSaveFileName(this, QString(), QString(), QStringLiteral("*.wav"));
    if (!fileName.isEmpty()) {
        QFile file(fileName);
        if (file.open(QIODevice::WriteOnly)) {
            file.write(mSound);
            file.close();
        }
    }
}

void SoundEditWidget::deleteSound()
{
    mHasSound = false;
    mSound = QByteArray();
    updateView();
}

SoundLoader *SoundEditWidget::soundLoader()
{
    if (!mSoundLoader) {
        mSoundLoader = new SoundLoader;
    }

    return mSoundLoader;
}
