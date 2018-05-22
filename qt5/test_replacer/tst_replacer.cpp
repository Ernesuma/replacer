#include"tst_replacer.h"

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
    // define a plain text with some replace tags
    QString plainText{"Hallo {name},\nwie geht es Dir und {name2}?"};

    // create a tag map with a entry for every tag in the plain text
    tagMap tags = tagMap();
    tags[QString("name2")] = "Elsa";
    tags[QString("name")] = QString("Peter");
    QCOMPARE(tags.size(), 2);

    // call replacer to replace tags in plain text and get the final text
    Replacer rep;
    QString finalText{""};
    bool res = rep.replace(plainText, finalText, tags);

    // check return value of replacer and the final text
    QCOMPARE(res, true);
    QCOMPARE(finalText, QString("Hallo Peter,\nwie geht es Dir und Elsa?"));
}

/*
 * test how the replacer handles missing tags
 */
void test_replacer::test_tagsMissing()
{
    // create a tag map with one entry
    tagMap tags = tagMap();
    tags["myGreatTag"] = QString("myGreatValue");

    // plain text with two tags
    QString plainText{QString("This is {myGreatTag}. It will be replaced. But this {secondTag} has no tag in the tagMap ;( ")};

    // call replacer to get final text
    Replacer rep;
    QString finalText{""};
    bool returnValue = rep.replace(plainText, finalText, tags);

    // check replacer return value and final text
    QCOMPARE(returnValue, true);
    QCOMPARE(finalText, QString("This is myGreatValue. It will be replaced. But this {secondTag} has no tag in the tagMap ;( "));
}

/*
 * test correct lower and upper case handling of replacer
 */
void test_replacer::test_caseSensitivity()
{
    // create tag map with lower und upper cased tags
    tagMap tags = tagMap();
    tags[QString("lower")] = QString("lowerValue");
    tags[QString("mIXeD")] = QString("mixedValue");
    tags[QString("UPPER")] = QString("upperValue");

    tags[QString("test")] = QString("lowerTest");
    tags[QString("tEsT")] = QString("mixedTest");
    tags[QString("TEST")] = QString("upperTest");

    // create plain text to test the lower and upper case tags
    QString plainText{QString("1.) {TEST}\n2.) {test}\n3.) {mIXeD}\n4.) {UPPER}\n5.) {tEsT}")};

    // define the expected final text
    const QString expectedText{QString("1.) upperTest\n2.) lowerTest\n3.) mixedValue\n4.) upperValue\n5.) mixedTest")};

    // use replacer to get final text
    Replacer rep;
    QString finalText{QString("")};
    bool retVal = rep.replace(plainText, finalText, tags);

    // check replacer return value and final text
    QCOMPARE(retVal, true);
    QCOMPARE(finalText, expectedText);
}

// mandatory code to let the QTests run
QTEST_APPLESS_MAIN(test_replacer)

// just needed when class declaration and implementation is in one cpp file:
//#include "tst_test_replacer.moc"
