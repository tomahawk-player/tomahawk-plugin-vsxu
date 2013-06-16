/* === This file is part of Tomahawk Player - <http://tomahawk-player.org> ===
 *
 *   Copyright 2011, Dominik Schmidt <domme@tomahawk-player.org>
 *
 *   Tomahawk is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   Tomahawk is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with Tomahawk. If not, see <http://www.gnu.org/licenses/>.
 */

#include "VSXuPlugin.h"


#include "VisualizerWidget.h"

#include <utils/Logger.h>
#include <ViewManager.h>

#include <QCoreApplication>


Tomahawk::InfoSystem::VSXuPlugin::VSXuPlugin()
{
    tDebug() << Q_FUNC_INFO;
}


Tomahawk::InfoSystem::VSXuPlugin::~VSXuPlugin()
{
    tDebug() << Q_FUNC_INFO;
}


void
Tomahawk::InfoSystem::VSXuPlugin::init()
{
    tDebug() << Q_FUNC_INFO;

    // HACK: we wait for Tomahawk (the MainWindow with the ViewManager to be ready) and use the DirectConnection to make addViewPage be called from the GUI thread
    connect(QCoreApplication::instance(), SIGNAL( tomahawkLoaded() ), SLOT( addViewPage() ), Qt::DirectConnection );
}


void
Tomahawk::InfoSystem::VSXuPlugin::addViewPage()
{
    tLog() << Q_FUNC_INFO;

    // don't add this twice, for some reason tomahawkLoaded() is fired more than once
    disconnect(QCoreApplication::instance(), SIGNAL( tomahawkLoaded() ), this, SLOT( addViewPage() ) );

    ViewManager::instance()->addDynamicPage("Visualizer", new VisualizerWidget( 0 ) );
}


void
Tomahawk::InfoSystem::VSXuPlugin::getInfo( Tomahawk::InfoSystem::InfoRequestData requestData )
{
    tDebug() << Q_FUNC_INFO;
}


void
Tomahawk::InfoSystem::VSXuPlugin::notInCacheSlot( Tomahawk::InfoSystem::InfoStringHash criteria, Tomahawk::InfoSystem::InfoRequestData requestData )
{
    tDebug() << Q_FUNC_INFO;
}


void
Tomahawk::InfoSystem::VSXuPlugin::pushInfo( Tomahawk::InfoSystem::InfoPushData pushData )
{
    tDebug() << Q_FUNC_INFO;
}


Q_EXPORT_PLUGIN2( Tomahawk::InfoSystem::InfoPlugin, Tomahawk::InfoSystem::VSXuPlugin )
