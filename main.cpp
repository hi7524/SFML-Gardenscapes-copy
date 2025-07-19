#include "stdafx.h"

int main()
{
    FRAMEWORK.Init(1280, 720, "SFML_Gardenscapes_KHI");
    FRAMEWORK.GetWindow().setFramerateLimit(60);
    FRAMEWORK.Do();
    FRAMEWORK.Release();

    return 0;
}