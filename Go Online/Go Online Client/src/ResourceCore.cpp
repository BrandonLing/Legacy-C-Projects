#include "ResourceCore.h"

void ResourceCore::init()
{
    FontSystem.init();
    SpriteData.init();
}

void ResourceCore::quit()
{
    SpriteData.quit();
    FontSystem.quit();
}
