#ifndef RESOURCECORE_H
#define RESOURCECORE_H

#include <FontCore.h>
#include <SpriteCore.h>

class ResourceCore
{
    public:
        void init();
        void quit();
        FontCore FontSystem;
        SpriteCore SpriteData;
    protected:
    private:
};

#endif // RESOURCECORE_H
