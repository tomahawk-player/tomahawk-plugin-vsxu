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

#ifndef VSXUPLUGIN_H
#define VSXUPLUGIN_H

#include "VisualizerWidget.h"

#include <ViewPagePlugin.h>
#include <ViewPageLazyLoader.h>

namespace Tomahawk
{

namespace Widgets
{

class VSXuPlugin : public ViewPageLazyLoader< VisualizerWidget >
{
    Q_PLUGIN_METADATA( IID "org.tomahawk-player.Player.ViewPagePlugin" )
    Q_OBJECT
    Q_INTERFACES( Tomahawk::ViewPagePlugin )

public:
    VSXuPlugin();
    virtual ~VSXuPlugin();

    virtual Tomahawk::playlistinterface_ptr playlistInterface() const;

    virtual const QString defaultName();
    virtual QString title() const;
    virtual QString description() const;
    virtual const QString pixmapPath() const;

    virtual bool jumpToCurrentTrack();
};

}

}

#endif // VSXUPLUGIN_H
