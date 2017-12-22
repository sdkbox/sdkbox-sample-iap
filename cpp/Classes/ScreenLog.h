/*
* Author: Chris Campbell - www.iforce2d.net
*
* See usage details at http://www.iforce2d.net/cc2dxres/screenlog
*
* This software is provided 'as-is', without any express or implied warranty.
* In no event will the authors be held liable for any damages arising from
* the use of this software. Permission is granted to anyone to use this software
* for any purpose, including commercial applications, and to alter it and
* redistribute it freely.
*
* 2017/03/21 modified by http://github.com/yinjimmy
* - getInstance
* - one header
*   #define SCREENLOG_IMPLEMENTATION
*   #include "ScreenLog.h"
*/

#ifndef SCREEN_LOG_H
#define SCREEN_LOG_H

#include <string>
#include <vector>
#include "cocos2d.h"

#define LL_FATAL    0x01
#define LL_ERROR    0x02
#define LL_WARNING  0x04
#define LL_INFO     0x08
#define LL_DEBUG    0x10
#define LL_TRACE    0x20


//////////////////////////////////////////////////////////////////////

class screenLogMessage {
    friend class ScreenLog;
private:
    class ScreenLog* m_layer;
    int m_level;
    std::string m_text;
    float m_timestamp;
    cocos2d::CCLabelTTF* m_label;
    bool m_dirty;

private:
    screenLogMessage(ScreenLog* layer) {
        m_layer = layer;
        m_label = NULL;
        m_level = 0;
        m_timestamp = 0;
        m_dirty = true;
    }
    virtual ~screenLogMessage() { }

    void setLabelText(std::string msg);
    void createLabel();
    bool checkLabel();
};

//////////////////////////////////////////////////////////////////////

#define INFO(format, ...) ScreenLog::getInstance()->log(LL_INFO, format, ##__VA_ARGS__)
#define ERROR(format, ...) ScreenLog::getInstance()->log(LL_ERROR, format, ##__VA_ARGS__)

class ScreenLog : public cocos2d::CCLayer
{
    friend class screenLogMessage;
private:
    std::string m_fontFile;
    int m_level;
    float m_timeout;
    std::vector<screenLogMessage*> m_messages;
    pthread_mutex_t m_contentMutex;

public:

    static ScreenLog* getInstance();
    ScreenLog();
    ~ScreenLog();

    void setFontFile(std::string file);
    void setLevelMask(int level);
    void setTimeoutSeconds(float seconds);
    void attachToScene(cocos2d::CCNode* scene);

    screenLogMessage* log(int level, const char* msg, ...);
    void setMessageText(screenLogMessage* slm, const char *p_str, ...);

    void update(float dt);
    void moveLabelsUp(int maxIndex);
    void clearEntries();
};

//////////////////////////////////////////////////////////////////////

class ScopeLock {
public:
    pthread_mutex_t* m_mutex;
    ScopeLock(pthread_mutex_t* m) {
        m_mutex = m;
        pthread_mutex_lock(m_mutex);
    }
    ~ScopeLock() {
        pthread_mutex_unlock(m_mutex);
    }
};

//////////////////////////////////////////////////////////////////////

class ScopeLog {
public:
    std::string m_functionName;
    ScopeLog(std::string fn) {
        m_functionName = fn;
        ScreenLog::getInstance()->log(LL_TRACE, "Entered %s", m_functionName.c_str());
    }
    ~ScopeLog() {
        ScreenLog::getInstance()->log(LL_TRACE, "Exiting %s", m_functionName.c_str());
    }
};

#endif

//////////////////////////////////////////////////////////////////////
////////////////////// END OF HEADER /////////////////////////////////
//////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////

#ifdef SCREENLOG_IMPLEMENTATION
#undef SCREENLOG_IMPLEMENTATION

#include <sstream>

#define SCREENLOG_NUM_LINES             32                          // The total number of lines shown (font height will be the screen height divided by this)
#define SCREENLOG_START_HEIGHT_PERCENT  0.2                         // Zero will make the first log line appear at the bottom of the screen. A value of about 0.2 will place it above the fps counter.
#define SCREENLOG_PRINT_BUFFER_SIZE     8192                        // The maximum total length of one log message.
#define SCREENLOG_LAYER_LEVEL           1000                        // The child level of this layer in the scene. Make it higher than your other layers, if you want to see the log :)

static char g_screenLogPrintBuffer[SCREENLOG_PRINT_BUFFER_SIZE];
float getTimeMillis() {
    timeval time;
    gettimeofday(&time, NULL);
    unsigned long millisecs = (time.tv_sec * 1000) + (time.tv_usec/1000);
    return (float) millisecs;
}

template < typename T > std::string to_string( const T& n )
{
    std::ostringstream stm ;
    stm << n ;
    return stm.str() ;
}

ScreenLog* ScreenLog::getInstance()
{
    static ScreenLog *log = NULL;
    if (!log) {
        log = new ScreenLog();
    }
    return log;
}

ScreenLog::ScreenLog()
{
    pthread_mutexattr_t Attr;
    pthread_mutexattr_init(&Attr);
    pthread_mutexattr_settype(&Attr, PTHREAD_MUTEX_RECURSIVE);
    
    pthread_mutex_init(&m_contentMutex, &Attr);
    
    m_timeout = 5000;//ms
    m_level = 0;
    
    cocos2d::CCDirector::sharedDirector()->getScheduler()->scheduleUpdate(this, 10000, false);
}

ScreenLog::~ScreenLog()
{
    cocos2d::CCDirector::sharedDirector()->getScheduler()->unscheduleUpdate(this);
    
    {
        ScopeLock lock(&m_contentMutex);
        for (unsigned int i = 0; i < m_messages.size(); i++)
            delete m_messages[i];
    }
    
    pthread_mutex_destroy(&m_contentMutex);
}

void ScreenLog::setFontFile(std::string file)
{
    m_fontFile = file;
}

void ScreenLog::setLevelMask(int p_level)
{
    m_level = p_level;
}

void ScreenLog::setTimeoutSeconds(float t)
{
    m_timeout = t * 1000;
}

void ScreenLog::attachToScene(cocos2d::CCNode* scene)
{
    if ( getParent() )
        getParent()->removeChild(this,false);
    if ( scene )
        scene->addChild(this,SCREENLOG_LAYER_LEVEL);
}

screenLogMessage* ScreenLog::log(int p_level, const char *p_str, ...)
{
    ScopeLock lock(&m_contentMutex);
    
    if (! p_str )
        return NULL;
    
    if (!(p_level & m_level))
        return NULL;
    
    va_list t_va;
    va_start (t_va, p_str);
    vsnprintf(g_screenLogPrintBuffer, SCREENLOG_PRINT_BUFFER_SIZE - 1, p_str, t_va);
    va_end (t_va);
    
    CCLOG("%s", g_screenLogPrintBuffer);
    
    screenLogMessage *slm = new screenLogMessage(this);
    slm->m_level = p_level;
    slm->m_text = to_string(m_messages.size()+1) + ")" + g_screenLogPrintBuffer;
    slm->m_timestamp = getTimeMillis();
    m_messages.push_back(slm);
    
    return slm;
}

void ScreenLog::setMessageText(screenLogMessage *slm, const char *p_str, ...)
{
    ScopeLock lock(&m_contentMutex);
    
    //loop through to find matching message, in case it has already gone
    bool messageStillExists = false;
    for (int i = 0; i < m_messages.size(); i++) {
        if ( m_messages[i] == slm ) {
            messageStillExists = true;
            break;
        }
    }
    if ( ! messageStillExists )
        return;
    
    va_list t_va;
    va_start (t_va, p_str);
    vsnprintf(g_screenLogPrintBuffer, SCREENLOG_PRINT_BUFFER_SIZE - 1, p_str, t_va);
    va_end (t_va);
    
    slm->setLabelText(g_screenLogPrintBuffer);
    slm->m_timestamp = getTimeMillis();
}

void ScreenLog::update(float dt)
{
    ScopeLock lock(&m_contentMutex);
    
    for (int i = 0; i < m_messages.size(); i++) {
        screenLogMessage* slm = m_messages[i];
        if ( slm->checkLabel() )
            moveLabelsUp(i);
    }
    
    float now = getTimeMillis();
    int c = 0;
    for (int i = m_messages.size()-1; i >= 0; i--) {
        screenLogMessage *slm = m_messages[i];
        if (now - slm->m_timestamp > m_timeout || c > (2*SCREENLOG_NUM_LINES)) {
            removeChild(slm->m_label,true);
            delete slm;
            m_messages.erase( m_messages.begin() + i );
        }
        c++;
    }
}

void ScreenLog::moveLabelsUp(int maxIndex)
{
    ScopeLock lock(&m_contentMutex);
    
    float screenHeightPixels = cocos2d::CCDirector::sharedDirector()->getWinSize().height;
    float fontSize =  screenHeightPixels / (float)SCREENLOG_NUM_LINES - 1;
    
    if ( maxIndex >= m_messages.size() )
        maxIndex = m_messages.size();
    
    for (int i = 0; i < maxIndex; i++) {
        screenLogMessage* slm = m_messages[i];
        cocos2d::CCPoint p = slm->m_label->getPosition();
        p.y += fontSize;
        slm->m_label->setPosition( p );
    }
}

void ScreenLog::clearEntries()
{
    ScopeLock lock(&m_contentMutex);
    
    for (unsigned int i = 0; i < m_messages.size(); i++)
        delete m_messages[i];
    m_messages.clear();
}

void screenLogMessage::setLabelText(std::string msg)
{
    // can be called from other threads, delay label creation to main thread to make sure OpenGL works
    ScopeLock lock(&m_layer->m_contentMutex);
    
    m_text = msg;
    m_dirty = true;
}

void screenLogMessage::createLabel()
{
    float screenHeightPixels = cocos2d::CCDirector::sharedDirector()->getWinSize().height;
    float fontSize =  screenHeightPixels / (float)SCREENLOG_NUM_LINES - 1;
    m_label = cocos2d::CCLabelTTF::create(m_text.c_str(), m_layer->m_fontFile, fontSize);
    m_label->setAnchorPoint(cocos2d::CCPoint(0,0));
    
    switch ( m_level ) {
        case LL_TRACE:
        case LL_DEBUG:   m_label->setColor(cocos2d::ccc3(255, 255, 255)); break; // white
        case LL_INFO:    m_label->setColor(cocos2d::ccc3( 32, 255,  32)); break; // green
        case LL_WARNING: m_label->setColor(cocos2d::ccc3(255, 127,  32)); break; // orange
        default:         m_label->setColor(cocos2d::ccc3(255,  32,  32)); break; // red
    }
    
    m_label->setPosition( 2, SCREENLOG_START_HEIGHT_PERCENT * screenHeightPixels );
    m_layer->addChild(m_label);
}

//returns true if label was created for the first time (other labels should be moved upward)
bool screenLogMessage::checkLabel()
{
    if ( !m_label ) {
        createLabel();
        m_dirty = false;
        return true;
    }
    
    if (m_dirty) {
        cocos2d::CCPoint originalPos = m_label->getPosition();
        m_layer->removeChild(m_label,true);
        m_label = NULL;
        createLabel();
        m_label->setPosition(originalPos);
        m_dirty = false;
    }
    
    return false;
}

#endif // SCREENLOG_IMPLEMENTATION
