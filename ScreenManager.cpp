#include "ScreenManager.h"

ScreenManager::ScreenManager(SDL_Renderer* renderer) : renderer(renderer) {
    if (!renderer) {
        printf("can't find renderer");
    }
}

void ScreenManager::pushScreen(std::shared_ptr<Screen> screen) {
    screenStack.push(screen);
}

void ScreenManager::popScreen() {
    if (!screenStack.empty()) {
        screenStack.pop();
    }
}

void ScreenManager::updateScreen() {
    if (!screenStack.empty()) {
        screenStack.top()->update();
    }
}

void ScreenManager::renderScreen() {
    if (!screenStack.empty()) {
        screenStack.top()->render(renderer);
    }
}

bool ScreenManager::isEmpty() const {
    return screenStack.empty();
}

