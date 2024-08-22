#include "HistoryManager.h"

HistoryManager::HistoryManager(QStackedWidget *stackedWidget)
    : stackedWidget(stackedWidget), currentIndex(-1)
{
}

void HistoryManager::navigateTo(int index)
{
    if (index < 0 || index >= stackedWidget->count()) {
        return;
    }

    if (currentIndex != -1) {
        backStack.push(currentIndex);
    }

    currentIndex = index;
    stackedWidget->setCurrentIndex(currentIndex);
    // Clear the forward stack whenever a new page is navigated to
    forwardStack.clear();
}

void HistoryManager::goToPreviousPage()
{
    if (!backStack.isEmpty()) {
        forwardStack.push(currentIndex);
        currentIndex = backStack.pop();
        stackedWidget->setCurrentIndex(currentIndex);
    }
}

void HistoryManager::goToNextPage()
{
    if (!forwardStack.isEmpty()) {
        backStack.push(currentIndex);
        currentIndex = forwardStack.pop();
        stackedWidget->setCurrentIndex(currentIndex);
    }
}

