#include "ScreenManager.h"

ScreenManager::ScreenManager(SDL_Renderer* renderer) : renderer(renderer) {}

void ScreenManager::pushScreen(std::unique_ptr<Screen> screen) {
    screen->init(renderer);
    screenStack.push(std::move(screen));
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

void ScreenManager::handleInput(SDL_Event& event) {
    if (!screenStack.empty()) {
        screenStack.top()->handleInput(event);
    }
}

bool ScreenManager::isEmpty() const {
    return screenStack.empty();
}