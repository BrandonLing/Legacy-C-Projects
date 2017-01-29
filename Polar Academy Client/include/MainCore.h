#ifndef MAINCORE_H
#define MAINCORE_H

#include <windows.h> //Sleep
#include <string>
#include <iostream>

//Core Dependencies
#include <InputCore.h>
#include <ClientSend.h>
#include <ClientRecv.h>
#include <RenderCore.h>
#include <EventCore.h>

void init_systems();
void quit_systems();

#endif // MAINCORE_H
