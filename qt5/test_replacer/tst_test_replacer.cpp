#include <QtTest>

// add necessary includes here
#include "tagmapmodel.h"
#include "replacer.h"

class test_replacer : public QObject
{
    Q_OBJECT

public:
    test_replacer();
    ~test_replacer();

private slots:
    void test_case1();
    void test_simpleReplace();

};

test_replacer::test_replacer()
{

}

test_replacer::~test_replacer()
{

}

void test_replacer::test_case1()
{

}

void test_replacer::test_simpleReplace()
{
    QString plainText{"Hallo {name},\nwie geht es Dir und {name2}?"};
    tagMap *tags = new tagMap();
    tags->insert(tags->begin(), QString("name"), QString("Marie"));
    //tags[QString("name")] = QString("Peter");
    (*tags)[QString("name2")] = "Elsa";

    Replacer rep;
    QString finalText{""};
    bool res = rep.replace(plainText, finalText, (*tags));

    QVERIFY(true == res);
    QCOMPARE(res, true);
    //QCOMPARE(finalText, "Hallo Peter,\nwie geht es Dir und Elsa?");

    delete(tags);
}

QTEST_APPLESS_MAIN(test_replacer)

#include "tst_test_replacer.moc"
