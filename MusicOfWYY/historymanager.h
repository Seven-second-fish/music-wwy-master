#ifndef HISTORYMANAGER_H
#define HISTORYMANAGER_H

#include <QStack>
#include <QStackedWidget>

class HistoryManager
{
public:
    HistoryManager(QStackedWidget *stackedWidget);

    void navigateTo(int index);       // Navigate to a page
    void goToPreviousPage();          // Go back to the previous page
    void goToNextPage();              // Go forward to the next page

private:
    QStackedWidget *stackedWidget;
    QStack<int> backStack;            // Stack for previous pages
    QStack<int> forwardStack;         // Stack for next pages
    int currentIndex;                 // Current page index
};

#endif // HISTORYMANAGER_H
