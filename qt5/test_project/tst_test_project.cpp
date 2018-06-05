#include <QString>
#include <QtTest>

// include subject to test
#include "project.h"

class Test_project : public QObject
{
    Q_OBJECT

public:
    Test_project();

private Q_SLOTS:
    void test_isValidName_positive();
    void test_isValidName_negative();
};

Test_project::Test_project()
{
}

void Test_project::test_isValidName_positive()
{
    QList<QString> nameList;
    nameList.append("foo");
    nameList.append("Foo");
    nameList.append("FOO");
    nameList.append("fooBar");
    nameList.append("012_-_foo_bar");
    nameList.append("_3Foo-+bar");
    for(auto name: nameList)
    {
        auto retVal = Project::isValidName(name);
        QCOMPARE(retVal, true);
    }
}

void Test_project::test_isValidName_negative()
{
    QList<QString> nameList;
    nameList.append("");
    nameList.append("+");
    nameList.append("foo#bar");
    nameList.append("foo bar");
    nameList.append("foo/bar");
    nameList.append(" fooBar");
    nameList.append("fooBar ");
    for(auto name: nameList)
    {
        bool retVal = Project::isValidName(name);
        QCOMPARE(retVal, false);
    }
}

QTEST_APPLESS_MAIN(Test_project)

#include "tst_test_project.moc"
