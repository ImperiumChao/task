#include "task.h"
#include <QApplication>
#include <QIcon>
#include <QLockFile>
#include <QDir>
#include <QMessageBox>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    a.setWindowIcon(QIcon("icon.png"));

    QLockFile lockFile(QDir::temp().absoluteFilePath("task.lock"));
    if(!lockFile.tryLock(100)) return 1;

    Task w;

    return a.exec();
}
