/*
    The Rendering Thread doing the main VSXu Rendering
    Copyright (C) 2012  Dinesh Manajipet <saidinesh5@gmail.com>

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along
    with this program; if not, write to the Free Software Foundation, Inc.,
    51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
*/

#include <QImage>

#include <GL/glu.h>
#include <vsx_manager.h>
#include "VSXuRenderer.h"
#include "VisualizerWidget.h"
#include "utils/TomahawkUtils.h"

VSXuRenderer::VSXuRenderer(VisualizerWidget* parent)
    : m_manager(0)
    , m_widget(parent)
    , m_isRunning(true)
    , m_isActive(true)
    , m_doResize(true)
    , m_doAudioUpdate(true)
    , m_frontbuffer(false)
    , m_width(640)
    , m_height(480)
{
    //initializing the sound data buffers
    for(int i = 0; i < SAMPLES; i++)
    {
        m_soundData[0][i] = 0;
        m_soundData[1][i] = 0;
    }
    //connecting the audio paths
    connect ( AudioEngine::instance(),SIGNAL( audioDataReady(QMap<AudioEngine::AudioChannel,QVector<qint16> >) ) ,
	      this, SLOT( receiveAudioData(QMap<AudioEngine::AudioChannel,QVector<qint16> >)) );
    AudioEngine::instance()->activateDataOutput();
}


void VSXuRenderer::resize(int w, int h)
{
    m_mutex.lock();
    m_width = w;
    m_height = h;
    m_doResize = true;
    m_mutex.unlock();
}


void VSXuRenderer::activate()
{
    m_mutex.lock();
    m_isActive = true;
    m_mutex.unlock();
}


void VSXuRenderer::deactivate()
{
    m_mutex.lock();
    m_isActive = false;
    m_mutex.unlock();
}


void
VSXuRenderer::stop()
{
    m_mutex.lock();
    m_isRunning = false;
    m_mutex.unlock();
}


void
VSXuRenderer::receiveAudioData(const QMap< AudioEngine::AudioChannel, QVector< qint16 > > data)
{
    if ( data.size() <= 0 )
        return;

    //decide which buffer to use
    m_mutex.lock();
    int buf = (int)m_frontbuffer;
    m_mutex.unlock();

    //Making a local copy of the sound data for updating the sound data
    for (int i = 0; i < SAMPLES; i++)
    {
        m_soundData[buf][i] = 0;
        if( data.contains( AudioEngine::LeftChannel ) )
            m_soundData[buf][i] += (float)(data[AudioEngine::LeftChannel][i])/65536.0;
        if ( data.contains(AudioEngine::LeftSurroundChannel) )
            m_soundData[buf][i] += (float)(data[AudioEngine::LeftSurroundChannel][i])/65536.0;

        if ( data.contains(AudioEngine::RightChannel) )
            m_soundData[buf][i] += (float)(data[AudioEngine::RightChannel][i])/65536.0;
        if ( data.contains(AudioEngine::RightSurroundChannel) )
            m_soundData[buf][i] += (float)(data[AudioEngine::RightSurroundChannel][i])/65536.0;

        if ( data.contains(AudioEngine::CenterChannel) )
            m_soundData[buf][i] += (float)(data[AudioEngine::CenterChannel][i])/65536.0;
        if ( data.contains(AudioEngine::SubwooferChannel) )
            m_soundData[buf][i] += (float)(data[AudioEngine::SubwooferChannel][i])/65536.0;

        m_soundData[buf][i] *= 3.5/(float)data.size();
    }

    m_mutex.lock();
    m_doAudioUpdate = true;
    m_mutex.unlock();

}


void
VSXuRenderer::drawSplashScreen()
{
    QImage splash = QGLWidget::convertToGLFormat(QImage(RESPATH "images/visualizer-splash.png"));

    int edge = m_width > m_height? m_height : m_width;

    glEnable(GL_TEXTURE_2D);
    GLuint texture_splash;
    glGenTextures(1,&texture_splash);
    glBindTexture(GL_TEXTURE_2D, texture_splash);
    glTexImage2D(GL_TEXTURE_2D, 0, 3 , splash.width(), splash.height(),0,GL_RGBA,GL_UNSIGNED_BYTE,splash.bits());

    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glViewport((m_width-edge)/2, (m_height-edge)/2, edge, edge);

    glClearColor(0,0,0,0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glTranslatef(-0.5,-0.5,0);

    glBegin(GL_TRIANGLE_STRIP);
      glTexCoord2f(0.0, 0.0);
      glVertex2f(0.0,0.0);

      glTexCoord2f(0.0, 1.0);
      glVertex2f(0.0,1.0);

      glTexCoord2f(1.0, 0.0);
      glVertex2f(1.0,0.0);

      glTexCoord2f(1.0, 1.0);
      glVertex2f(1.0,1.0);

    glEnd();

    m_widget->swapBuffers();
}


void
VSXuRenderer::run()
{
    //HACK: Waiting till the QGLWidget has been actually created
    msleep(200);
    // init manager with the shared path and sound input type.
    m_widget->makeCurrent();

    glEnable(GL_BLEND);
    glEnable(GL_POLYGON_SMOOTH);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // A nice splash screen till VSXu actually loads itself
    // TODO: Make this splash screen fade in and fade out when the widget is activated/deactivated.
    drawSplashScreen();

    m_manager = manager_factory();
    m_manager->init(0,"media_player");
    //m_manager->init(0,"pulseaudio");

    bool isRunning = true,isActive = true;
    bool doResize = true, doAudioUpdate = true;
    bool frontbuffer = false;
    while ( isRunning )
    {
        m_mutex.lock();
        //Reading the control variables
        isRunning = m_isRunning;
        isActive = m_isActive;
        doAudioUpdate = m_doAudioUpdate;
        doResize = m_doResize;
        frontbuffer = m_frontbuffer;

        //updating the control variables
        if ( m_doAudioUpdate )
        {
            m_frontbuffer = !m_frontbuffer;
            m_doAudioUpdate = false;
        }
        if ( m_doResize )
            m_doResize = false;

        m_mutex.unlock();

        if ( !isActive )
        {
            //do not flood the system with too many rendering calls.
            msleep(10);
            continue;
        }

        m_widget->makeCurrent();
        if ( doResize )
        {
            glViewport(0, 0, m_width, m_height);
            glMatrixMode(GL_PROJECTION);
            glLoadIdentity();
            // set origin to bottom left corner
            gluOrtho2D(0, m_width, 0, m_height);
            doResize = false;
        }
        if ( doAudioUpdate )
        {
            m_manager->set_sound_wave( m_soundData[(int)frontbuffer] );
            doAudioUpdate = false;
        }

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        if ( m_manager )
            m_manager->render();
        m_widget->swapBuffers();
    }
}


VSXuRenderer::~VSXuRenderer()
{
    stop();
    AudioEngine::instance()->deactivateDataOutput();
    if ( m_manager )
        manager_destroy(m_manager);
}
