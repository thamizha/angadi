#include <angadiapp.h>

int main(int argc, char *argv[])
{
    AngadiApp a(argc, argv);
    a.start();
    return a.exec();
}
