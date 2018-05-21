// add necessary includes here
#include <QtTest/QtTest>
#include "tagmapmodel.h"
#include "replacer.h"

/*
 * test case to test the class replacer
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

/*
 * implementation of constructor
 */
test_replacer::test_replacer()
{
    // nothing to do here
}

/*
 * implementation of destructor
 */
test_replacer::~test_replacer()
{
    // nothing to do here
}

/*
 * test how the replacer handles a big amount of tags in the tagMap
 */
void test_replacer::test_toMuchTags()
{
    // create a tag map instance and fill with a big amount of key/value pairs
    tagMap tags = tagMap();
    const int iMax = 1e6;
    for (int i = 0; i<iMax; ++i)
    {
        tags[QString("tag_") + QString::number(i)] = QString("value_") + QString::number(i);
    }
    // check for the correct amount of map entries
    QCOMPARE(tags.size(), iMax);

    // declare and define plain and finalt text strings
    QString plainText = QString(">>{tag_123}<<");
    QString finalText = QString("");

    // call replacer on plain text; save result in final text
    Replacer rep;
    bool res = rep.replace(plainText, finalText, tags);

    // check return value of replacer
    QCOMPARE(res, true);

    // check final text to contain correct replacements
    QCOMPARE(finalText, QString(">>value_123<<"));
}

/*
 * just try a simple text with two simple replacements
 */
void test_replacer::test_simpleReplace()
{
    QString plainText{"Hallo {name},\nwie geht es Dir und {name2}?"};

    tagMap tags = tagMap();
    tags[QString("name2")] = "Elsa";
    tags[QString("name")] = QString("Peter");
    QCOMPARE(tags.size(), 2);

    Replacer rep;
    QString finalText{""};
    bool res = rep.replace(plainText, finalText, tags);

    QCOMPARE(res, true);
    QCOMPARE(finalText, QString("Hallo Peter,\nwie geht es Dir und Elsa?"));
}

/*
 * tags missing
 */
void test_replacer::test_tagsMissing()
{
    tagMap tags = tagMap();
    tags["myGreatTag"] = QString("myGreatValue");

    QString plainText{QString("This is {myGreatTag}. It will be replaced. But this {secondTag} has no tag in the tagMap ;( ")};
    QString finalText{""};

    Replacer rep;
    bool returnValue = rep.replace(plainText, finalText, tags);

    QCOMPARE(returnValue, true);
    QCOMPARE(finalText, QString("This is myGreatValue. It will be replaced. But this {secondTag} has no tag in the tagMap ;( "));
}

/*
 * case sensitivity
 */
void test_replacer::test_caseSensitivity()
{
    tagMap tags = tagMap();
    tags[QString("lower")] = QString("lowerValue");
    tags[QString("mIXeD")] = QString("mixedValue");
    tags[QString("UPPER")] = QString("upperValue");

    tags[QString("test")] = QString("lowerTest");
    tags[QString("tEsT")] = QString("mixedTest");
    tags[QString("TEST")] = QString("upperTest");

    QString plainText{QString("1.) {TEST}\n2.) {test}\n3.) {mIXeD}\n4.) {UPPER}\n5.) {tEsT}")};
    const QString expectedText{QString("1.) upperTest\n2.) lowerTest\n3.) mixedValue\n4.) upperValue\n5.) mixedTest")};
    QString finalText{QString("")};

    Replacer rep;
    bool retVal = rep.replace(plainText, finalText, tags);

    QCOMPARE(retVal, true);
    QCOMPARE(finalText, expectedText);


}

// mandatory code to let the QTests run
QTEST_APPLESS_MAIN(test_replacer)
#include "tst_test_replacer.moc"
