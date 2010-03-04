#ifndef ANDROID_USB_CAMERA_TEST_BASE_H
#define ANDROID_USB_CAMERA_TEST_BASE_H

#include <QTest>
#include <gmock/gmock.h>

#define GQTEST_MAIN(TestObject) \
int main(int argc, char *argv[]) \
{ \
    QCoreApplication app(argc, argv); \
    TestObject tc; \
    testing::GTEST_FLAG(throw_on_failure) = true; \
    testing::InitGoogleMock(&argc, argv); \
    return QTest::qExec(&tc, argc, argv); \
}

using namespace testing;

#endif
