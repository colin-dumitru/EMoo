#include <QString>
#include <QtTest>

class TestOperation : public QObject
{
    Q_OBJECT
    
public:
    TestOperation();
    
private Q_SLOTS:
    void Operations();
};

TestOperation::TestOperation()
{
}

void TestOperation::Operations()
{
    QVERIFY2(true, "Failure");
}

QTEST_APPLESS_MAIN(TestOperation)

#include "tst_testoperation.moc"
