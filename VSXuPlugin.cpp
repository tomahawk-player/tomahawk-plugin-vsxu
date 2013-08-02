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


Tomahawk::Widgets::VSXuPlugin::VSXuPlugin()
{
    tDebug() << Q_FUNC_INFO;
}


Tomahawk::Widgets::VSXuPlugin::~VSXuPlugin()
{
    tDebug() << Q_FUNC_INFO;
}


const QString
Tomahawk::Widgets::VSXuPlugin::defaultName()
{
    return "visualizer";
}

QString Tomahawk::Widgets::VSXuPlugin::title() const
{
    return "Visualizer";
}


QString Tomahawk::Widgets::VSXuPlugin::description() const
{
    return QString();
}


const QString Tomahawk::Widgets::VSXuPlugin::pixmapPath() const
{
    return ( RESPATH "images/visualizer.png" );
}


bool
Tomahawk::Widgets::VSXuPlugin::jumpToCurrentTrack()
{
    return false;
}


Tomahawk::playlistinterface_ptr Tomahawk::Widgets::VSXuPlugin::playlistInterface() const
{
    return playlistinterface_ptr();
}



Q_EXPORT_PLUGIN2( Tomahawk::ViewPagePlugin, Tomahawk::Widgets::VSXuPlugin )
