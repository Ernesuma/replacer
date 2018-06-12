#include <QString>
#include <QtTest>
#include <QDir>

// include subject under test (SUT)
#include "pathhelper.h"


class Test_pathHelperTest : public QObject
{
    Q_OBJECT

public:
    Test_pathHelperTest();

private Q_SLOTS:
    void tc_appendSuffix_withDot();
    void tc_appendSuffix_withoutDot();
    void tc_appendSuffix_emptySuffix();
};

Test_pathHelperTest::Test_pathHelperTest()
{
}

void Test_pathHelperTest::tc_appendSuffix_withDot()
{
    QString file{"fileFoo"};
    QString suffix{".bar"};
    QString result{appendSuffix(file, suffix)};

    QCOMPARE(result, QString("fileFoo.bar"));
}

void Test_pathHelperTest::tc_appendSuffix_withoutDot()
{
    QString file{"fileFoo"};
    QString suffix{"bar"};
    QString result{appendSuffix(file, suffix)};

    QCOMPARE(result, QString("fileFoo.bar"));
}

void Test_pathHelperTest::tc_appendSuffix_emptySuffix()
{
    QString file{"fooBar"};
    QString result{appendSuffix(file, QString(""))};
    QCOMPARE(result, file);
}



QTEST_APPLESS_MAIN(Test_pathHelperTest)

#include "test_pathhelpertest.moc"
