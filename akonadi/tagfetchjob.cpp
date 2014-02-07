/*
    Copyright (c) 2014 Christian Mollekopf <mollekopf@kolabsys.com>

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

#include "tagfetchjob.h"
#include "job_p.h"
#include "tag.h"
#include "protocolhelper_p.h"
#include <QTimer>

using namespace Akonadi;

class Akonadi::TagFetchJobPrivate : public JobPrivate
{
public:
    TagFetchJobPrivate(TagFetchJob *parent)
        :JobPrivate(parent)
    {
    }

    void init()
    {
        Q_Q(TagFetchJob);
        mEmitTimer = new QTimer(q);
        mEmitTimer->setSingleShot(true);
        mEmitTimer->setInterval(100);
        q->connect(mEmitTimer, SIGNAL(timeout()), q, SLOT(timeout()));
        q->connect(q, SIGNAL(result(KJob*)), q, SLOT(timeout()));
    }

    void timeout()
    {
        Q_Q(TagFetchJob);
        mEmitTimer->stop(); // in case we are called by result()
        if (!mPendingTags.isEmpty()) {
            if (!q->error()) {
                emit q->tagsReceived(mPendingTags);
            }
            mPendingTags.clear();
        }
    }

    Q_DECLARE_PUBLIC(TagFetchJob)

    Tag::List mRequestedTags;
    Tag::List mResultTags;
    Tag::List mPendingTags; // items pending for emitting itemsReceived()
    QTimer* mEmitTimer;
};

TagFetchJob::TagFetchJob(QObject *parent)
    :Job(new TagFetchJobPrivate(this), parent)
{
    Q_D(TagFetchJob);
    d->init();
}

TagFetchJob::TagFetchJob(const Tag &tag, QObject *parent)
    :Job(parent)
{
    Q_D(TagFetchJob);
    d->init();
    d->mRequestedTags << tag;
}


void TagFetchJob::doStart()
{
    Q_D(TagFetchJob);

    QByteArray command = d->newTag();
    command += " UID";
    command += " TAGFETCH";
    if (d->mRequestedTags.isEmpty()) {
      command += " 1:*";
    } else {
      command += ' ' + QString::number(d->mRequestedTags.first().id()).toLatin1();
    }
    command += " (UID";
//       Q_FOREACH (const QByteArray &part, fetchScope.attributes()) {
//         command += ' ' + ProtocolHelper::encodePartIdentifier(ProtocolHelper::PartAttribute, part);
//       }
    command += ")\n";

    d->writeData( command );
}

void TagFetchJob::doHandleResponse(const QByteArray &tag, const QByteArray &data)
{
    Q_D(TagFetchJob);

    if (tag == "*") {
        int begin = data.indexOf("TAGFETCH");
        if (begin >= 0) {
            // split fetch response into key/value pairs
            QList<QByteArray> fetchResponse;
            ImapParser::parseParenthesizedList(data, fetchResponse, begin + 9);

            Tag tag;

            for (int i = 0; i < fetchResponse.count() - 1; i += 2) {
                const QByteArray key = fetchResponse.value(i);
                const QByteArray value = fetchResponse.value(i + 1);

                if (key == "UID") {
                    tag.setId(value.toLongLong());
                } else if (key == "GID") {
                    tag.setGid(value);
                } else if (key == "REMOTEID") {
                    tag.setRemoteId(value);
                }
            }

            if ( !tag.isValid() )
              return;

            d->mResultTags.append(tag);
            d->mPendingTags.append(tag);
            if ( !d->mEmitTimer->isActive() ) {
                d->mEmitTimer->start();
            }
            return;
        }
    }
    kDebug() << "Unhandled response: " << tag << data;
}

Tag::List TagFetchJob::tags() const
{
    Q_D(const TagFetchJob);
    return d->mResultTags;
}

#include "moc_tagfetchjob.cpp"
