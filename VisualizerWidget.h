/*
    The Visualizer Page, acting as a placeholder for the VSXu Renderer.
    Copyright (C) 2012  Dinesh <saidinesh5@gmail.com>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/


#ifndef VISUALIZERWIDGET_H
#define VISUALIZERWIDGET_H

#include "ViewPage.h"
#include "VSXuRenderer.h"

#include <utils/ImageRegistry.h>

#include <phonon/audiodataoutput.h>

#include <QGLWidget>
#include <QPixmap>
#include <QResizeEvent>
#include <QShowEvent>
#include <QHideEvent>
#include <QtOpenGL/QGLFormat>

class VisualizerWidget : public QGLWidget,public Tomahawk::ViewPage
{
    Q_OBJECT

public:
    VisualizerWidget( QWidget *parent = 0 );
    ~VisualizerWidget();

    bool jumpToCurrentTrack() { return false; }
    QString description() const { return QString("Vovoid VSXu Music Visualizer"); }
    QString title() const{ return QString("Visualizer"); }
    QPixmap pixmap() const { return ImageRegistry::instance()->pixmap( RESPATH "images/visualizer.png", QSize( 0, 0 ) ); }
    Tomahawk::playlistinterface_ptr playlistInterface() const { return Tomahawk::playlistinterface_ptr(); }
    QWidget* widget(){ return this; }
    //TODO: Add the activate and deactivate methods, which can be called from  ViewManager.cpp
    //when some other page is being activated, to save the CPU cycles.
    static bool canRun(){
      Phonon::AudioDataOutput dataout;
      return QGLFormat::hasOpenGL() && dataout.isValid();
    }

protected:
    void resizeEvent(QResizeEvent* event);
    void paintEvent(QPaintEvent* ){;}//Will be taken Care by the Rendering thread
    void hideEvent(QHideEvent* ){ m_renderer.deactivate(); }
    void showEvent(QShowEvent* ){ m_renderer.activate(); }

private:
    VSXuRenderer m_renderer;
};
#endif // VISUALIZERWIDGET_H
