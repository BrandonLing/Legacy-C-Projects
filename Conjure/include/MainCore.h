#ifndef MAINCORE_H
#define MAINCORE_H

//Error Dependencies
#include <iostream>

//Library Dependencies
#include <windows.h>
#include <time.h>

//Core Dependencies
#include <GameDataCore.h>
#include <ShaderCore.h>
#include <RenderCore.h>
#include <InputCore.h>
#include <EventQueueCore.h>
#include <EventProcessCore.h>
#include <ResourceCore.h>
#include <MapCore.h>
#include <MonsterCore.h>
#include <SoundProcessCore.h>
#include <SoundQueueCore.h>

void init_systems();
void quit_systems();

int frameRate = 45;

#endif // MAINCORE_H
