#pragma once
#include <SDL.h>
#include <filesystem>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>

void discardAllEvents(bool quit);

int countFolderContents(const std::string& folderPath);
