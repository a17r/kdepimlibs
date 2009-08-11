/*
    Copyright (c) 2009 Constantin Berzan <exit3219@gmail.com>

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

#include "dispatchmodeattribute.h"
#include "errorattribute.h"
#include "sentbehaviourattribute.h"
#include "transportattribute.h"

#include <akonadi/attributefactory.h>

namespace {

// Anonymous namespace; function is invisible outside this file.
bool dummy()
{
  using namespace Akonadi;
  using namespace MailTransport;
  AttributeFactory::registerAttribute<DispatchModeAttribute>();
  AttributeFactory::registerAttribute<ErrorAttribute>();
  AttributeFactory::registerAttribute<SentBehaviourAttribute>();
  AttributeFactory::registerAttribute<TransportAttribute>();
  return true;
}

// Called when this library is loaded.
const bool registered = dummy();

} // namespace
