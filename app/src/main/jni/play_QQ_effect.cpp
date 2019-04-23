//
// Created by 8500 on 2019/4/22 0022.
//
#include "inc/fmod.hpp"
#include "com_xue_song_fmod_PlayQQEffectActivity.h"
#include "common.h"

#include <unistd.h>
#include <android/log.h>

#define NOMAL  0
#define LUOLI  1
#define DASHU  2
#define THRILL 3
#define YOULING 4
#define LOGI(...)  __android_log_print(ANDROID_LOG_INFO,"wang",__VA_ARGS__)


/**
 * 初始化声音
 * @param env
 * @param obj
 */
JNIEXPORT void JNICALL Java_com_xue_song_fmod_PlayQQEffectActivity_init
        (JNIEnv *env, jobject obj, jstring path) {

}

JNIEXPORT void JNICALL Java_com_xue_song_fmod_PlayQQEffectActivity_playSound
        (JNIEnv *env, jobject obj, jint javaInt, jstring path) {
    FMOD::System *system;
    void *extradriverdata;
    FMOD_RESULT result;
    unsigned int version;
    FMOD::ChannelGroup *mastergroup;
    FMOD::Sound *sound;
    FMOD::Channel *channel;
    FMOD::DSP *dsp;
    const char *path_c = env->GetStringUTFChars(path, NULL);
    result = FMOD::System_Create(&system);
    // ERRCHECK(result);
    result = system->getVersion(&version);
    // ERRCHECK(result);

    if (version < FMOD_VERSION) {
        LOGI("%s", "FMOD lib version %08x doesn't match header version %08x version FMOD_VERSION");
        /*   Common_Fatal("FMOD lib version %08x doesn't match header version %08x", version,
                        FMOD_VERSION);*/
    }
    result = system->init(32, FMOD_INIT_NORMAL, extradriverdata);
    //  ERRCHECK(result);

    //  result = system->getMasterChannelGroup(&mastergroup);
//    ERRCHECK(result);
    LOGI("%s", path_c);
    result = system->createSound(path_c, FMOD_DEFAULT, 0, &sound);
    //  ERRCHECK(result);
    try {

        switch (javaInt) {
            case NOMAL:
                system->playSound(sound, 0, false, &channel);
                break;
            case LUOLI:
                //loli
                //DSP digital singal process
                //dsp->音效
                //dsp 提升或者降低音调的一种音效
                system->createDSPByType(FMOD_DSP_TYPE_PITCHSHIFT, &dsp);
                //设置音调的参数
                dsp->setParameterFloat(FMOD_DSP_PITCHSHIFT_PITCH, 8.0);
                //添加进到channel
                system->playSound(sound, 0, false, &channel);
                channel->addDSP(0, dsp);
                break;
            case DASHU:
                system->createDSPByType(FMOD_DSP_TYPE_PITCHSHIFT, &dsp);
                //设置音调的参数
                dsp->setParameterFloat(FMOD_DSP_PITCHSHIFT_PITCH, 0.8);
                //添加进到channel
                system->playSound(sound, 0, false, &channel);
                channel->addDSP(0, dsp);
                break;
            case THRILL:
                system->createDSPByType(FMOD_DSP_TYPE_TREMOLO, &dsp);
                dsp->setParameterFloat(FMOD_DSP_TREMOLO_SKEW, 5);
                system->playSound(sound, 0, false, &channel);
                channel->addDSP(0, dsp);
                break;
            case YOULING:
                system->createDSPByType(FMOD_DSP_TYPE_ECHO, &dsp);
                dsp->setParameterFloat(FMOD_DSP_ECHO_DELAY, 300);
                dsp->setParameterFloat(FMOD_DSP_ECHO_FEEDBACK, 20);
                system->playSound(sound, 0, false, &channel);
                channel->addDSP(0, dsp);
                break;
        }
        system->update();
        bool isPlaying = true;
        while (isPlaying) {
            channel->isPlaying(&isPlaying);
            LOGI("正在播放 %d", isPlaying);
            usleep(2 * 1000 * 1000);
        }
        goto end;
    } catch (...) {
        LOGI("%s", "播放出错");
        goto end;
    }
    end:
    env->ReleaseStringUTFChars(path,path_c);
    sound->release();
    system->close();
    system->release();
  //  Common_Close();


}