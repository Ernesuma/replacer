#ifndef TST_REPLACER_H
#define TST_REPLACER_H

// add necessary includes here
#include <QtTest/QtTest>
#include "tagmapmodel.h"
#include "replacer.h"

/*
 * test case class to test the class replacer
 */
class test_replacer : public QObject
{
    // neccessary because of QObject is superclass
    Q_OBJECT

public:
    // constructor and destructor
    test_replacer();
    ~test_replacer();

private slots:
    // every test has to be a private slot of the test case class
    void test_toMuchTags();
    void test_simpleReplace();
    void test_tagsMissing();
    void test_caseSensitivity();
};
#endif // TST_REPLACER_H
