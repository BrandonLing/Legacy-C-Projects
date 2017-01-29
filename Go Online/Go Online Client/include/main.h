#ifndef MAIN_H
#define MAIN_H

#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0501
#endif

#include <Client.h>
#include <RenderCore.h>
#include <InputCore.h>
#include <EventCore.h>
#include <ShaderCore.h>
#include <GameDataCore.h>
#include <ModelDataCore.h>
#include <SoundDataCore.h>
#include <AnimationDataCore.h>

void init();
void quit();

#endif // MAIN_H
