/*
    Copyright 2009 Constantin Berzan <exit3219@gmail.com>

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

#ifndef MAILTRANSPORT_ERRORATTRIBUTE_H
#define MAILTRANSPORT_ERRORATTRIBUTE_H

#include <mailtransport/mailtransport_export.h>

#include <QtCore/QString>

#include <akonadi/attribute.h>

namespace MailTransport {

/**
  Attribute given to the messages that failed to be sent.  Contains the error
  message encountered.

  @author Constantin Berzan <exit3219@gmail.com>
  @since 4.4
*/
class MAILTRANSPORT_EXPORT ErrorAttribute : public Akonadi::Attribute
{
  public:
    /**
      Creates a new ErrorAttribute.
    */
    ErrorAttribute( const QString &msg = QString() );

    /**
      Destroys this ErrorAttribute.
    */
    virtual ~ErrorAttribute();

    /* reimpl */
    virtual ErrorAttribute* clone() const;
    virtual QByteArray type() const;
    virtual QByteArray serialized() const;
    virtual void deserialize( const QByteArray &data );

    /**
      Returns the i18n'ed error message.
    */
    QString message() const;

    /**
      Sets the error message.
    */
    void setMessage( const QString &msg );

  private:
    class Private;
    Private *const d;

};

} // namespace MailTransport

#endif // MAILTRANSPORT_ERRORATTRIBUTE_H
